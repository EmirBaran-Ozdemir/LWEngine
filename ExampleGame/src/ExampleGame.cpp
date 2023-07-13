#include "ExampleGame.h"


#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


ExampleGame::ExampleGame(std::string& path)
	: Layer("ExampleGame"), m_CameraController((float)1280 / 720), m_ParticleSystem(100000), m_World(WorldGeneration(path))
{

}

void ExampleGame::OnAttach()
{
	LWE_PROFILE_FUNCTION();

	//. DEFINING NULL & ERROR TEXTURES
	m_TextureNull = LWEngine::Texture2D::Create(1, 1);
	uint32_t NullTextureData = 0x00ffffff;
	m_TextureNull->SetData(&NullTextureData, sizeof(NullTextureData));
	m_SubTextureNull = LWEngine::SubTexture2D::CreateFromCoords(m_TextureNull, { 0,0 }, { 1,1 });
	m_TextureMap[{255.0f, 255.0f, 255.0f, 255.0f}] = m_SubTextureNull;
	m_TextureError = LWEngine::Texture2D::Create("assets/textures/textureError.png");
	m_SubTextureError = LWEngine::SubTexture2D::CreateFromCoords(m_TextureError, { 0,0 }, { 800,800 });

	//. DEFINING BACKGROUNDS & TILEMAPS
	m_Background = LWEngine::Texture2D::Create("assets/textures/backgrounds/backgroundColorFall.png");
	m_IndustrialTilemap = LWEngine::Texture2D::Create("assets/textures/level-components/industrial_tilemap.png");
	m_CubeHead = LWEngine::Texture2D::Create("assets/textures/level-components/awesomeface.png");

	//. DEFINING TILES FROM TILEMAP & BINDING COLOR VALUES
	m_TileDirtTop = LWEngine::SubTexture2D::CreateFromCoords(m_IndustrialTilemap, { 2,5 }, { 18,18 }, 1.0f);
	m_TextureMap[{255.0f, 0.0f, 0.0f, 255.0f}] = m_TileDirtTop;
	m_TileDirtCenter = LWEngine::SubTexture2D::CreateFromCoords(m_IndustrialTilemap, { 2,4 }, { 18,18 }, 1.0f);
	m_TextureMap[{255.0f, 255.0f, 0.0f, 255.0f}] = m_TileDirtCenter;
	m_TileDirtLeftCenter = LWEngine::SubTexture2D::CreateFromCoords(m_IndustrialTilemap, { 1,4 }, { 18,18 }, 1.0f);
	m_TextureMap[{255.0f, 100.0f, 0.0f, 255.0f}] = m_TileDirtLeftCenter;
	m_TileDirtRightCenter = LWEngine::SubTexture2D::CreateFromCoords(m_IndustrialTilemap, { 3,4 }, { 18,18 }, 1.0f);
	m_TextureMap[{255.0f, 0.0f, 100.0f, 255.0f}] = m_TileDirtRightCenter;
	m_TileDirtMid = LWEngine::SubTexture2D::CreateFromCoords(m_IndustrialTilemap, { 0,4 }, { 18,18 }, 1.0f);
	m_TextureMap[{255.0f, 100.0f, 100.0f, 255.0f}] = m_TileDirtMid;

	m_TileWaterTop = LWEngine::SubTexture2D::CreateFromCoords(m_IndustrialTilemap, { 13,5 }, { 18,18 }, 1.0f);
	m_TextureMap[{0.0f, 0.0f, 255.0f, 255.0f}] = m_TileWaterTop;
	m_TileWaterCenter = LWEngine::SubTexture2D::CreateFromCoords(m_IndustrialTilemap, { 13,4 }, { 18,18 }, 1.0f);
	m_TextureMap[{255.0f, 0.0f, 255.0f, 255.0f}] = m_TileWaterCenter;

	m_TileChest = LWEngine::SubTexture2D::CreateFromCoords(m_IndustrialTilemap, { 13,3 }, { 18,18 }, 1.0f);
	m_TextureMap[{0.0f, 255.0f, 255.0f, 255.0f}] = m_TileChest;

	m_Particle.ColorBegin = { 1.0f,0.0f,0.0f,1.0f };
	m_Particle.ColorEnd = { 0.5f,0.5f,0.0f,1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.0f;
	m_Particle.Position = { 0.0f, 0.0f };
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 5.0f,1.0f };

	LWEngine::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_Framebuffer = LWEngine::Framebuffer::Create(fbSpec);

	m_CameraController.SetZoomLevel(10.0f);

}

void ExampleGame::OnDetach()
{
	LWE_PROFILE_FUNCTION();

}

void ExampleGame::OnUpdate(LWEngine::Timestep ts)
{
	LWE_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);
	m_Player.OnUpdate(ts);
	LWEngine::Renderer2D::ResetStats();

	{
		LWE_PROFILE_SCOPE("Renderer Prep");
		m_Framebuffer->Bind();
		LWEngine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f, 1.0f });
		LWEngine::RenderCommand::Clear();
	}

	LWEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());

	auto playerPos = m_Player.GetPlayerPos();
	LWEngine::Renderer2D::DrawQuad({ playerPos.x, playerPos.y, playerPos.z }, { 1.0f,1.0f }, m_CubeHead);
	
	LWEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 64.0f,36.0f }, m_Background);
	for (int x = 0; x < m_World.GetWidth(); x++)
	{
		for (int y = 0; y < m_World.GetHeight(); y++)
		{
			glm::vec4 tileType = m_World.GetTiles()[x * m_World.GetHeight() + y];
			LWEngine::Ref<LWEngine::SubTexture2D> texture;
			if (m_TextureMap.find(tileType) != m_TextureMap.end())
			{
				texture = m_TextureMap[tileType];
			}
			else
				texture = m_SubTextureError;
			LWEngine::Renderer2D::DrawQuad({ x - m_World.GetWidth() / 2.0f, y - m_World.GetHeight() / 2.0f,0.1f }, { 1.0f,1.0f }, texture, { 1.0f,1.0f,1.0f,1.0f });
		}
	}
	LWEngine::Renderer2D::EndScene();

	LWEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	if (LWEngine::Input::IsMouseButtonPressed(LWEngine::MouseCode::Button0))
	{
		auto [x, y] = LWEngine::Input::GetMousePosition();
		auto width = LWEngine::Application::Get().GetWindow().GetWidth();
		auto height = LWEngine::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			m_ParticleSystem.Emit(m_Particle);
	}
	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());
	LWEngine::Renderer2D::EndScene();
	m_Framebuffer->Unbind();
}

void ExampleGame::OnImGuiRender(LWEngine::Timestep ts)
{
	LWE_PROFILE_FUNCTION();

	static bool dockspaceEnabled = true;
	static bool opt_fullscreen = true;
	static bool opt_padding = true;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None ;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking ;
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

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	ImGui::Begin("Settings");
	ImGui::Text("%f", LWEngine::Random::Float());
	ImGui::End();
	ImGui::Begin("Color Edit");
	ImGui::ColorEdit4("Birth Color", glm::value_ptr(m_Particle.ColorBegin));
	ImGui::ColorEdit4("Death Color", glm::value_ptr(m_Particle.ColorEnd));
	ImGui::DragFloat("Life Time", &m_Particle.LifeTime, 0.1f, 0.1f, 10.0f);
	ImGui::DragFloat("SizeBegin", &m_Particle.SizeBegin, 0.1f, 0.2f, 5.0f);
	ImGui::DragFloat("SizeEnd (Max = SizeBegin/2)", &m_Particle.SizeEnd, 0.01f, 0.1f, m_Particle.SizeBegin / 2);
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	//for (auto &pair : m_TextureMap)
	//{
	//	LWEngine::Ref<LWEngine::SubTexture2D> texture = pair.second;
	//	ImTextureID imguiTextureID = (ImTextureID)(intptr_t)texture->GetTexture()->GetRendererID();
	//	if(ImGui::ImageButton(imguiTextureID, ImVec2(100, 100))) LWEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f ,2.0f}, { 1.0f,1.0f }, texture->GetTexture(), {1.0f,1.0f,1.0f,1.0f});
	//}
	uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
	ImGui::Image((void*)textureID, ImVec2{ 1280,720}, ImVec2{ 0,1 }, ImVec2{ 1,0 });

	ImGui::End();

	ImGui::End(); // Dockwindow end
}

void ExampleGame::OnEvent(LWEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
