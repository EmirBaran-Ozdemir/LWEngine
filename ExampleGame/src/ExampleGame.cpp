#include "ExampleGame.h"
#include <Platform/OpenGL/OpenGLShader.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


ExampleGame::ExampleGame()
	: Layer("ExampleGame"), m_CameraController((float)1280 / 720), m_ParticleSystem(100000)
{

}

void ExampleGame::OnAttach()
{
	LWE_PROFILE_FUNCTION();

	m_Background = LWEngine::Texture2D::Create("assets/textures/backgrounds/backgroundColorDesert.png");
	m_FarmSpriteSheet = LWEngine::Texture2D::Create("assets/textures/level-components/industrial_tilemap.png");
	
	m_TopFarmTilemap = LWEngine::SubTexture2D::CreateFromCoords(m_FarmSpriteSheet, { 2,5 }, { 18,18 }, 1.0f);

	m_Particle.ColorBegin = { 1.0f,0.0f,0.0f,1.0f };
	m_Particle.ColorEnd = { 0.5f,0.5f,0.0f,1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.0f;
	m_Particle.Position = { 0.0f, 0.0f };
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 5.0f,1.0f };

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
	for (float i = -18.0f*5; i <= 18.0f*10; i += 18.0f)
	{
		
		LWEngine::Renderer2D::DrawQuad({ 0.0f + i, 0.0f, 0.1f }, { 3.0f,3.0f }, m_TopFarmTilemap, { 1.0f,1.0f,1.0f,1.0f });
	}
	
	LWEngine::Renderer2D::EndScene();
}

void ExampleGame::OnImGuiRender(LWEngine::Timestep ts)
{
	LWE_PROFILE_FUNCTION();

	auto stats = LWEngine::Renderer2D::GetStats();

	ImGui::Begin("Settings");

	ImGui::End();
}

void ExampleGame::OnEvent(LWEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
