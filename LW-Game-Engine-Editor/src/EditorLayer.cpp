#include "EditorLayer.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace LWEngine {
	EditorLayer::EditorLayer(std::string& path)
		: Layer("EditorLayer"), m_CameraController((float)1280 / 720), m_ParticleSystem(100000), m_World(WorldGeneration(path))
	{

	}

	void EditorLayer::OnAttach()
	{
		LWE_PROFILE_FUNCTION();


		//. DEFINING NULL & ERROR TEXTURES
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


		m_Particle.ColorBegin = { 1.0f,0.0f,0.0f,1.0f };
		m_Particle.ColorEnd = { 0.5f,0.5f,0.0f,1.0f };
		m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
		m_Particle.LifeTime = 1.0f;
		m_Particle.Position = { 0.0f, 0.0f };
		m_Particle.Velocity = { 0.0f, 0.0f };
		m_Particle.VelocityVariation = { 5.0f,1.0f };

		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);

		m_CameraController.SetZoomLevel(10.0f);

		m_ActiveScene = CreateRef<Scene>();
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

				if (Input::IsKeyPressed(KeyCode::A))
					position.x -= 2.0f * ts;
				if (Input::IsKeyPressed(KeyCode::D))
					position.x += 2.0f * ts;
				if (Input::IsKeyPressed(KeyCode::W))
					position.y += 2.0f * ts;
				if (Input::IsKeyPressed(KeyCode::S))
					position.y -= 2.0f * ts;
			}
			void OnDestroy()
			{
			}
		};
		m_SecondCameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
		m_ScHiPanel.SetContext(m_ActiveScene);
		m_WindowPanel.SetContext(m_ActiveScene);
		//SceneSerializer serializer(m_ActiveScene);
		//serializer.Serialize("assets/scenes/Empty.lwe");
		//serializer.Deserialize("assets/scenes/Example.lwe");
	}

	void EditorLayer::OnDetach()
	{
		LWE_PROFILE_FUNCTION();

	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		LWE_PROFILE_FUNCTION();
		FramebufferSpecification spec = m_Framebuffer->GetSpecification();
		//! Resize
		if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.Resize(m_ViewportSize.x, m_ViewportSize.y);

			m_ActiveScene->OnResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		//! Update
		if (m_ViewPortFocused)
		{
			m_CameraController.OnUpdate(ts);
			m_Player.OnUpdate(ts);
		}

		Renderer2D::ResetStats();

		{
			LWE_PROFILE_SCOPE("Renderer Prep");
			m_Framebuffer->Bind();
			RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f, 1.0f });
			RenderCommand::Clear();
		}


		m_ActiveScene->OnUpdate(ts);

		Renderer2D::BeginScene(m_CameraController.GetCamera());
		//auto playerPos = m_Player.GetPlayerPos();
		//Renderer2D::DrawQuad({ playerPos.x, playerPos.y, playerPos.z }, { 1.0f,1.0f }, m_CubeHead);

		//Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 64.0f,36.0f }, m_Background);
		//for (int x = 0; x < m_World.GetWidth(); x++)
		//{
		//	for (int y = 0; y < m_World.GetHeight(); y++)
		//	{
		//		glm::vec4 tileType = m_World.GetTiles()[x * m_World.GetHeight() + y];
		//		Ref<SubTexture2D> texture;
		//		if (m_TextureMap.find(tileType) != m_TextureMap.end())
		//		{
		//			texture = m_TextureMap[tileType];
		//		}
		//		else
		//			texture = m_SubTextureError;
		//		Renderer2D::DrawQuad({ x - m_World.GetWidth() / 2.0f, y - m_World.GetHeight() / 2.0f,0.1f }, { 1.0f,1.0f }, texture, { 1.0f,1.0f,1.0f,1.0f });
		//	}
		//}
		//Renderer2D::EndScene();

		//Renderer2D::BeginScene(m_CameraController.GetCamera()); //? PARTICLES
		//if (Input::IsMouseButtonPressed(MouseCode::Button0))
		//{
		//	auto [x, y] = Input::GetMousePosition();
		//	auto width = m_ActiveScene.get()->GetWidth();
		//	auto height = m_ActiveScene.get()->GetHeight();

		//	auto bounds = m_CameraController.GetBounds();
		//	auto pos = m_CameraController.GetCamera().GetPosition();
		//	x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		//	y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		//	m_Particle.Position = { x + pos.x, y + pos.y };
		//	for (int i = 0; i < 5; i++)
		//		m_ParticleSystem.Emit(m_Particle);
		//}
		//m_ParticleSystem.OnUpdate(ts);
		//m_ParticleSystem.OnRender(m_CameraController.GetCamera());
		//Renderer2D::EndScene();

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
		m_WindowPanel.TopMenuBar(ts);

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
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
		ImGui::Begin("Viewport");
		m_ViewPortFocused = ImGui::IsWindowFocused();
		m_ViewPortHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewPortFocused && !m_ViewPortHovered);

		m_WindowPanel.BottomMenuBar();

		ImVec2 availContentRegion = ImGui::GetContentRegionAvail();
		m_ViewportSize = { availContentRegion.x, availContentRegion.y };

		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, { m_ViewportSize.x,m_ViewportSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });
		ImGui::End();
		ImGui::PopStyleVar();
		ImGui::End(); // Dockwindow end
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_CameraController.OnEvent(e);
	}
}