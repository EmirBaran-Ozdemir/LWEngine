#include "ExampleGame.h"


#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


ExampleGame::ExampleGame()
	: Layer("ExampleGame"), m_CameraController((float)1280 / 720), m_ParticleSystem(100000), m_World(WorldGeneration("assets/textures/exampleWorld.png"))
{

}

void ExampleGame::OnAttach()
{
	LWE_PROFILE_FUNCTION();


	m_TextureNull = LWEngine::Texture2D::Create("assets/textures/textureNull.png");
	m_SubTextureNull = LWEngine::SubTexture2D::CreateFromCoords(m_TextureNull, { 0,0 }, { 800,800 });

	m_Background = LWEngine::Texture2D::Create("assets/textures/backgrounds/backgroundColorDesert.png");
	m_IndustrialSpriteSheet = LWEngine::Texture2D::Create("assets/textures/level-components/industrial_tilemap.png");
	
	m_TopDirtTilemap = LWEngine::SubTexture2D::CreateFromCoords(m_IndustrialSpriteSheet, { 2,5 }, { 18,18 }, 1.0f);
	m_MidWaterTilemap = LWEngine::SubTexture2D::CreateFromCoords(m_IndustrialSpriteSheet, { 13,4 }, { 18,18 }, 1.0f);

	m_TextureMap[m_ColTopFarmTilemap] = m_TopDirtTilemap;
	m_TextureMap[m_ColMidWaterTilemap] = m_MidWaterTilemap;

	m_Particle.ColorBegin = { 1.0f,0.0f,0.0f,1.0f };
	m_Particle.ColorEnd = { 0.5f,0.5f,0.0f,1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.0f;
	m_Particle.Position = { 0.0f, 0.0f };
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 5.0f,1.0f };

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
	LWEngine::Renderer2D::ResetStats();

	{
		LWE_PROFILE_SCOPE("Renderer Prep");
		LWEngine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f, 1.0f });
		LWEngine::RenderCommand::Clear();
	}
	
	LWEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());

	LWEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 10.0f,10.0f }, m_Background);
	for (int x = 0; x< m_World.GetHeight(); x++)
	{
		for (int y = 0; y < m_World.GetWidth(); y++)
		{
			glm::vec4 tileType = m_World.GetTiles()[x * m_World.GetWidth() + y];
			LWEngine::Ref<LWEngine::SubTexture2D> texture;
			if (m_TextureMap.find(tileType) != m_TextureMap.end())
				texture = m_TextureMap[tileType];
			else
				texture = m_SubTextureNull;
			LWEngine::Renderer2D::DrawQuad({ x - m_World.GetWidth() / 2.0f, y - m_World.GetHeight(),0.1f }, {1.0f,1.0f}, texture, {1.0f,1.0f,1.0f,1.0f});
		}
	}

	LWEngine::Renderer2D::EndScene();
}

void ExampleGame::OnImGuiRender(LWEngine::Timestep ts)
{
	LWE_PROFILE_FUNCTION();

	auto stats = LWEngine::Renderer2D::GetStats();

	ImGui::Begin("Settings");
	ImGui::Text("%f", LWEngine::Random::Float());
	ImGui::End();
}

void ExampleGame::OnEvent(LWEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
