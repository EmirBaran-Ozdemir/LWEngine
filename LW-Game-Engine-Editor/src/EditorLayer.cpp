#include "EditorLayer.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ImGuizmo.h"

namespace LWEngine {
	EditorLayer::EditorLayer(std::string& path)
		: Layer("EditorLayer"), m_CameraController((float)1280 / 720), m_ParticleSystem(100000), m_World(WorldGeneration(path))
	{

	}

	void EditorLayer::OnAttach()
	{
		LWE_PROFILE_FUNCTION();


		//. DEFINING NULL & ERROR TEXTURES
	#ifdef LWE_TEST
		m_TextureNull = Texture2D::Create(1, 1);
		uint32_t NullTextureData = 0x00ffffff;
		m_TextureNull->SetData(&NullTextureData, sizeof(NullTextureData));
		m_SubTextureNull = SubTexture2D::CreateFromCoords(m_TextureNull, { 0,0 }, { 1,1 });
		m_TextureMap[{255.0f, 255.0f, 255.0f, 255.0f}] = m_SubTextureNull;
		m_TextureError = Texture2D::Create("assets/textures/textureError.png");
		m_SubTextureError = SubTexture2D::CreateFromCoords(m_TextureError, { 0,0 }, { 800,800 });

		//. DEFINING BACKGROUNDS & TILEMAPS
		m_Background = Texture2D::Create("assets/textures/backgrounds/backgroundColorFall.png");
		m_IndustrialTilemap = Texture2D::Create("assets/textures/level-components/industrial_tilemap.png");
		m_CubeHead = Texture2D::Create("assets/textures/level-components/awesomeface.png");

		//. DEFINING TILES FROM TILEMAP & BINDING COLOR VALUES

		m_TileDirtTop = SubTexture2D::CreateFromCoords(m_IndustrialTilemap, { 2,5 }, { 18,18 }, 1.0f);
		m_TextureMap[{255.0f, 0.0f, 0.0f, 255.0f}] = m_TileDirtTop;
		m_TileDirtCenter = SubTexture2D::CreateFromCoords(m_IndustrialTilemap, { 2,4 }, { 18,18 }, 1.0f);
		m_TextureMap[{255.0f, 255.0f, 0.0f, 255.0f}] = m_TileDirtCenter;
		m_TileDirtLeftCenter = SubTexture2D::CreateFromCoords(m_IndustrialTilemap, { 1,4 }, { 18,18 }, 1.0f);
		m_TextureMap[{255.0f, 100.0f, 0.0f, 255.0f}] = m_TileDirtLeftCenter;
		m_TileDirtRightCenter = SubTexture2D::CreateFromCoords(m_IndustrialTilemap, { 3,4 }, { 18,18 }, 1.0f);
		m_TextureMap[{255.0f, 0.0f, 100.0f, 255.0f}] = m_TileDirtRightCenter;
		m_TileDirtMid = SubTexture2D::CreateFromCoords(m_IndustrialTilemap, { 0,4 }, { 18,18 }, 1.0f);
		m_TextureMap[{255.0f, 100.0f, 100.0f, 255.0f}] = m_TileDirtMid;

		m_TileWaterTop = SubTexture2D::CreateFromCoords(m_IndustrialTilemap, { 13,5 }, { 18,18 }, 1.0f);
		m_TextureMap[{0.0f, 0.0f, 255.0f, 255.0f}] = m_TileWaterTop;
		m_TileWaterCenter = SubTexture2D::CreateFromCoords(m_IndustrialTilemap, { 13,4 }, { 18,18 }, 1.0f);
		m_TextureMap[{255.0f, 0.0f, 255.0f, 255.0f}] = m_TileWaterCenter;

		m_TileChest = SubTexture2D::CreateFromCoords(m_IndustrialTilemap, { 13,3 }, { 18,18 }, 1.0f);
		m_TextureMap[{0.0f, 255.0f, 255.0f, 255.0f}] = m_TileChest;




		m_CameraController.SetZoomLevel(10.0f);

		auto square = m_ActiveScene->CreateEntity("Square");
		square.AddComponent<SpriteRendererComponent>(glm::vec4{0.0f, 1.0f, 0.0f, 1.0f});
		square.AddComponent<TransformComponent>(glm::vec3{0.0f, 0.0f, -3.0f});

		auto redSq = m_ActiveScene->CreateEntity("Red Square");
		redSq.AddComponent<SpriteRendererComponent>(glm::vec4{1.0f, 0.0f, 0.0f, 1.0f});
		m_SquareEntity = square;

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera");
		auto& camComponent = m_CameraEntity.AddComponent<CameraComponent>();
		m_CameraEntity.AddComponent<TransformComponent>();
		camComponent.Primary = true;

		m_SecondCameraEntity = m_ActiveScene->CreateEntity("SecondCamera");
		m_SecondCameraEntity.AddComponent<TransformComponent>();
		m_SecondCameraEntity.AddComponent<CameraComponent>();

		class CameraController : public ScriptableEntity
		{
		public:
			void OnCreate()
			{
				if (!HasComponent<TransformComponent>())
				{
					AddComponent<TransformComponent>();
				}
				auto& position = GetComponent<TransformComponent>().Position;
				position.x = rand() % 10 - 5.0f;
				position.y = rand() % 10 - 5.0f;
			}
			void OnUpdate(Timestep ts)
			{
				auto& position = GetComponent<TransformComponent>().Position;

				if (Input::IsKeyPressed(Key::A))
					position.x -= 2.0f * ts;
				if (Input::IsKeyPressed(Key::D))
					position.x += 2.0f * ts;
				if (Input::IsKeyPressed(Key::W))
					position.y += 2.0f * ts;
				if (Input::IsKeyPressed(Key::S))
					position.y -= 2.0f * ts;
			}
			void OnDestroy()
			{
			}
		};
		m_SecondCameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();

		SceneSerializer serializer(m_ActiveScene);
		//serializer.Serialize("assets/scenes/Empty.lwe");
		//serializer.Deserialize("assets/scenes/Example.lwe");
	#endif

		FbufferSpec fbSpec;
		fbSpec.Attachments = { FbufferTexFormat::RGBA8,FbufferTexFormat::RED_INT, FbufferTexFormat::Depth };
		fbSpec.Width = 1780;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);
		m_ActiveScene = CreateRef<Scene>();
		auto commandLineArgs = Application::Get().GetCommandLineArgs();
		if (commandLineArgs.Count > 1)
		{
			auto sceneFilePath = commandLineArgs[1];
			SceneSerializer serializer(m_ActiveScene);
			serializer.Deserialize(sceneFilePath);
		}
		m_ScHiPanel.SetContext(m_ActiveScene);
		m_WindowPanel.SetContext(m_ActiveScene);
		m_EditorCamera = EditorCamera(30.0f, 16.0f / 9.0f, 0.1f, 1000.0f);

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera");
		auto& camComponent = m_CameraEntity.AddComponent<CameraComponent>();
		m_CameraEntity.AddComponent<TransformComponent>();
		camComponent.Primary = true;

		m_Particle.ColorBegin = { 1.0f,0.0f,0.0f,1.0f };
		m_Particle.ColorEnd = { 0.5f,0.5f,0.0f,1.0f };
		m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
		m_Particle.LifeTime = 1.0f;
		m_Particle.Position = { 0.0f, 0.0f };
		m_Particle.Velocity = { 0.0f, 0.0f };
		m_Particle.VelocityVariation = { 5.0f,1.0f };
	}

	void EditorLayer::OnDetach()
	{
		LWE_PROFILE_FUNCTION();

	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		LWE_PROFILE_FUNCTION();
		FbufferSpec spec = m_Framebuffer->GetSpecification();
		//! Resize
		if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.Resize(m_ViewportSize.x, m_ViewportSize.y);
			m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
			m_ActiveScene->OnResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		//! Update
		m_EditorCamera.OnUpdate(ts);
		m_CameraController.OnUpdate(ts);
		m_Player.OnUpdate(ts);
		Renderer2D::ResetStats();

		{
			LWE_PROFILE_SCOPE("Renderer Prep");
			m_Framebuffer->Bind();
			RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f, 1.0f });
			RenderCommand::Clear();

			m_Framebuffer->ClearColorAttach(1, -1);
		}


		m_ActiveScene->OnUpdateEditor(ts, m_EditorCamera);

		int mouseX, mouseY;
		if (m_ViewportHovered)
		{
			auto [mx, my] = ImGui::GetMousePos();
			mx -= m_ViewportBounds[0].x;
			my -= m_ViewportBounds[0].y;
			my = m_ViewportSize.y - my;
			glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];

			mouseX = (int)mx;
			mouseY = (int)my;

			int pixelData = m_Framebuffer->ReadPixel(1, mouseX, mouseY);
			m_HoveredEntity = pixelData == -1 ? Entity() : Entity({ pixelData,m_ActiveScene.get() });
		}

	#ifdef LWE_TEST
		Renderer2D::BeginScene(m_CameraController.GetCamera());

		auto playerPos = m_Player.GetPlayerPos();
		Renderer2D::DrawQuad({ playerPos.x, playerPos.y, playerPos.z }, { 1.0f,1.0f }, m_CubeHead);

		Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 64.0f,36.0f }, m_Background);
		for (int x = 0; x < m_World.GetWidth(); x++)
		{
			for (int y = 0; y < m_World.GetHeight(); y++)
			{
				glm::vec4 tileType = m_World.GetTiles()[x * m_World.GetHeight() + y];
				Ref<SubTexture2D> texture;
				if (m_TextureMap.find(tileType) != m_TextureMap.end())
				{
					texture = m_TextureMap[tileType];
				}
				else
					texture = m_SubTextureError;
				Renderer2D::DrawQuad({ x - m_World.GetWidth() / 2.0f, y - m_World.GetHeight() / 2.0f,0.1f }, { 1.0f,1.0f }, texture, { 1.0f,1.0f,1.0f,1.0f });
			}
		}
		Renderer2D::EndScene();

		Renderer2D::BeginScene(m_CameraController.GetCamera()); //? PARTICLES
		if (Input::IsMouseButtonPressed(Mouse::ButtonLeft) && m_ViewportFocused)
		{
			auto [mx, my] = ImGui::GetMousePos();
			mx -= m_ViewportBounds[0].x;
			my -= m_ViewportBounds[0].y;
			my = m_ViewportSize.y - my;
			glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];

			mouseX = (int)mx;
			mouseY = (int)my;
			m_Particle.Position = { mouseX, mouseY };
			for (int i = 0; i < 5; i++)
				m_ParticleSystem.Emit(m_Particle);
		}
		m_ParticleSystem.OnUpdate(ts);
		m_ParticleSystem.OnRender(m_CameraController.GetCamera());
		Renderer2D::EndScene();
	#endif

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender(Timestep ts)
	{
		LWE_PROFILE_FUNCTION();

		static bool dockspaceEnabled = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = true;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceEnabled, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		//. Dockspace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minSizeX;

		m_ScHiPanel.OnImGuiRender();
		m_ContBrowPanel.OnImGuiRender();

		//. TOP MENU BAR - TEMPORARY
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
		float height = ImGui::GetFrameHeight();

		//! First menu bar

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "CTRL+N"))
					NewScene();
				if (ImGui::MenuItem("Open", "CTRL+O"))
					OpenScene();
				ImGui::Separator();
				if (ImGui::MenuItem("Save", "CTRL+S"))
					SaveSceneAs();

				if (ImGui::MenuItem("Exit", "Alt+F4", false))
					Application::Get().Close();;

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				if (ImGui::MenuItem("Redo", "CTRL+SHIFT+Z", false, false)) {}  // Disabled item
				ImGui::Separator();
				if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				if (ImGui::MenuItem("Paste", "CTRL+V")) {}
				ImGui::EndMenu();
			}

			if (ImGui::Button("Play"))
			{
				//? Runtime Camera
				auto cameraEntity = m_ActiveScene->GetPrimaryCameraEntity();
				const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
				const glm::mat4& cameraProjection = camera.GetProjection();
				glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());
				m_ActiveScene->OnUpdateRuntime(ts);
			}
			m_WindowPanel.TopMenuBar(ts);

			m_LoopCounter++;
			if (m_LoopCounter == 60) {
				m_FPS = "FPS: " + std::to_string((int)(1000 / ts.GetMiliseconds()));
				m_LoopCounter = 0;
			}
			ImGui::SameLine(ImGui::GetContentRegionMax().x - ImGui::CalcTextSize(m_FPS.c_str()).x - 20.0f);
			ImGui::Text(m_FPS.c_str());
			ImGui::EndMainMenuBar();

		}
		ImGui::SameLine();

	#ifdef LWE_TEST
		ImGui::Begin("Settings");
		ImGui::Text("%f", Random::Float());
		ImGui::End();
		ImGui::Begin("Settings");

		ImGui::ColorEdit4("Birth Color", glm::value_ptr(m_Particle.ColorBegin));
		ImGui::ColorEdit4("Death Color", glm::value_ptr(m_Particle.ColorEnd));
		ImGui::DragFloat("Life Time", &m_Particle.LifeTime, 0.1f, 0.1f, 10.0f);
		ImGui::DragFloat("SizeBegin", &m_Particle.SizeBegin, 0.1f, 0.2f, 5.0f);
		ImGui::DragFloat("SizeEnd (Max = SizeBegin/2)", &m_Particle.SizeEnd, 0.01f, 0.1f, m_Particle.SizeBegin / 2);
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	#endif

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
		ImGui::Begin("Viewport");
		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem);
		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();
		m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);
		m_WindowPanel.BottomMenuBar();

		ImVec2 availContentRegion = ImGui::GetContentRegionAvail();
		m_ViewportSize = { availContentRegion.x, availContentRegion.y };

		uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image(reinterpret_cast<void*>(textureID), { m_ViewportSize.x,m_ViewportSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
			{
				const char* path = (const char*)payload->Data;
				FileType type = m_FSystem.GetFileType(path);
				if (type == FileType::lwe)
					OpenScene(path);
				if (type == FileType::png || type == FileType::jpg)
				{
					if (m_HoveredEntity)
					{
						auto& component = m_HoveredEntity.GetComponent<SpriteRendererComponent>();
						component.Texture = Texture2D::Create(path);
					}
				}
			}
			ImGui::EndDragDropTarget();
		}

		//. ImGuizmo
		Entity selectedEntity = m_ScHiPanel.GetSelectedEntity();

		if (selectedEntity && m_GuizmoType != -1 && !Input::IsKeyPressed(Key::LeftControl))
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();
			ImGuizmo::SetRect(m_ViewportBounds[0].x, m_ViewportBounds[0].y, m_ViewportBounds[1].x - m_ViewportBounds[0].x, m_ViewportBounds[1].y - m_ViewportBounds[0].y);

			//? Editor Camera
			const glm::mat4& cameraProjection = m_EditorCamera.GetProjection();
			glm::mat4 cameraView = m_EditorCamera.GetViewMatrix();

			//? EntityTransform
			if (selectedEntity.HasComponent<TransformComponent>())
			{
				auto& tc = selectedEntity.GetComponent<TransformComponent>();
				glm::mat4 transform = tc.GetTransform();

				bool snap = Input::IsKeyPressed(Key::LeftShift);
				float snapValue = 0.5f + (44.5f * (m_GuizmoType == ImGuizmo::OPERATION::ROTATE));
				float snapValues[3] = { snapValue,snapValue,snapValue };

				ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), (ImGuizmo::OPERATION)m_GuizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform), nullptr, snap ? snapValues : nullptr);

				if (ImGuizmo::IsUsing())
				{
					glm::vec3 translation, rotation, scale;
					Math::DecomposeTransform(transform, translation, rotation, scale);
					glm::vec3 deltaRotation = rotation - tc.Rotation;

					tc.Translation = translation;
					tc.Rotation += deltaRotation;
					tc.Scale = scale;
				}
			}
		}

		ImGui::End(); // Viewport end
		ImGui::PopStyleVar(); // WindowPadding
		ImGui::End(); // Dockwindow end
	}

	void EditorLayer::OnEvent(Event& e)
	{
		if ((ImGuizmo::IsOver() || ImGuizmo::IsUsing()) && !Input::IsKeyPressed(Key::LeftControl))
			return;
		m_CameraController.OnEvent(e);
		m_EditorCamera.OnEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(LWE_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(LWE_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressed));
	}
	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		if (ImGuizmo::IsOver() || ImGuizmo::IsUsing())
			return false;
		if (e.GetRepeatCount() > 0)
			return false;

		//. Shortcuts
		bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
		bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
		bool alt = Input::IsKeyPressed(Key::LeftAlt) || Input::IsKeyPressed(Key::RightAlt);
		switch (e.GetKeyCode())
		{
			case Key::W:
			{
				if (control)
					NewScene();
				break;
			}
			case Key::O:
			{
				if (control)
					OpenScene();
				break;
			}
			case Key::S:
			{
				if (control)
					SaveSceneAs();
				break;
			}
			case Key::F4:
			{
				if (alt)
					Application::Get().Close();
				break;
			}

			//? Guizmo
			case Key::D1:
			{
				if (shift)
					m_GuizmoType = -1;
				break;
			}
			case Key::D2:
			{
				if (shift)
					m_GuizmoType = ImGuizmo::OPERATION::TRANSLATE;
				break;
			}
			case Key::D3:
			{
				if (shift)
					m_GuizmoType = ImGuizmo::OPERATION::ROTATE;
				break;
			}
			case Key::D4:
			{
				if (shift)
					m_GuizmoType = ImGuizmo::OPERATION::SCALE;
				break;
			}

		}
		return false;
	}
	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == Mouse::ButtonLeft)
		{
			if (m_ViewportHovered && !ImGuizmo::IsOver())
				m_ScHiPanel.SetSelectedEntity(m_HoveredEntity);
		}
		return false;
	}
	void EditorLayer::NewScene()
	{
		m_ActiveScene = CreateRef<Scene>();
		m_ActiveScene->OnResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_ScHiPanel.SetContext(m_ActiveScene);
	}
	void EditorLayer::OpenScene()
	{
		std::string filepath = FileDialogs::OpenFile("LWEngine Scene (*.lwe)\0*.lwe\0");
		OpenScene(filepath);
	}
	void EditorLayer::OpenScene(const std::filesystem::path& path)
	{
		if (!path.empty())
		{
			m_ActiveScene = CreateRef<Scene>();
			m_ActiveScene->OnResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);

			m_ScHiPanel.SetContext(m_ActiveScene);
			SceneSerializer serializer(m_ActiveScene);
			serializer.Deserialize(path.string());
		}
	}
	void EditorLayer::SaveSceneAs()
	{
		LWE_CLIENT_INFO("File saved");
		std::string filepath = FileDialogs::SaveFile("LWEngine Scene (*.lwe)\0*.lwe\0");
		if (!filepath.empty())
		{
			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(filepath);
		}
	}
}
