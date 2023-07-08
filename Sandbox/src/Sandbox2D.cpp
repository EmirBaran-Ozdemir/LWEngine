#include "Sandbox2D.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController((float)1280 / 720), m_ParticleSystem(100000)
{

}

void Sandbox2D::OnAttach()
{
	LWE_PROFILE_FUNCTION();

	m_Texture2D = LWEngine::Texture2D::Create("assets/textures/awesomeface.png");
	m_Background = LWEngine::Texture2D::Create("assets/textures/Lake.jpg");

	m_Particle.ColorBegin = { 1.0f,0.0f,0.0f,1.0f };
	m_Particle.ColorEnd = { 0.5f,0.5f,0.0f,1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.0f;
	m_Particle.Position = { 0.0f, 0.0f };
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 5.0f,1.0f };

}

void Sandbox2D::OnDetach()
{
	LWE_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(LWEngine::Timestep ts)
{
	LWE_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	constexpr float gravity = -9.8f;
	static float velocity = 0.0f;
	static bool jumped = false;

	if (jumped)
	{
		velocity += gravity * ts;
		if (velocity < -15.0f) velocity = -15.0f;
		m_PlayerPos.y += velocity * ts + 0.5f * gravity * ts * ts;
	}

	if (m_PlayerPos.y <= 0)
	{
		velocity = 0.0f;
		jumped = false;
	}

	if (LWEngine::Input::IsKeyPressed(LWE_KEY_SPACE))
	{
		if (!jumped)
		{
			jumped = true;
			velocity += 5.0f;
		}
	}

	if (LWEngine::Input::IsKeyPressed(LWE_KEY_A))
		m_PlayerPos.x -= 5.0f * ts;
	if (LWEngine::Input::IsKeyPressed(LWE_KEY_D))
		m_PlayerPos.x += 5.0f * ts;

	float rotation = ts.GetElapsedTime() * 50.0f;

	LWEngine::Renderer2D::ResetStats();

	{
		LWE_PROFILE_SCOPE("Renderer Prep");
		LWEngine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f, 1.0f });
		LWEngine::RenderCommand::Clear();
	}

	{
		LWE_PROFILE_SCOPE("Renderer Draw");
		LWEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		LWEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 0.8f, 0.8f }, m_SquareColor);
		LWEngine::Renderer2D::DrawQuad({ 0.5f ,-0.5f }, { 0.5f, 0.75f }, { 1.0f,0.0f,1.0f,1.0f });
		LWEngine::Renderer2D::DrawQuad(
			m_PlayerPos,
			{ 1.0f,1.0f },
			m_Texture2D
		);
		LWEngine::Renderer2D::DrawQuad(
			{ 0.0f , 0.0f , -0.01f },
			{ m_Background->GetWidth() * sizeMultiplier,
			m_Background->GetHeight() * sizeMultiplier },
			m_Background
		);
		LWEngine::Renderer2D::EndScene();

		LWEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.1f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.1f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f ,0.5f };
   				LWEngine::Renderer2D::DrawQuad({ x,y }, { 0.09f,0.09f }, m_Background,{1.0f,1.0f,1.0f,1.0f});

			}
		}
		for (float y = -15.0f; y < -5.0f; y += 0.1f)
		{
			for (float x = -15.0f; x < -5.0f; x += 0.1f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f ,0.5f };
				LWEngine::Renderer2D::DrawQuad({ x,y }, { 0.09f,0.09f }, m_Texture2D, { 1.0f,1.0f,1.0f,1.0f });

			}
		}
		LWEngine::Renderer2D::EndScene();

	}

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

}

void Sandbox2D::OnImGuiRender(LWEngine::Timestep ts)
{
	LWE_PROFILE_FUNCTION();

	auto stats = LWEngine::Renderer2D::GetStats();

	ImGui::Begin("Settings");
	ImGui::Text("Renderer Stats");
	ImGui::Text("Draw Calls %d", stats.DrawCalls);
	ImGui::Text("Quad Count %d", stats.QuadCount);
	ImGui::Text("Vertices %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices %d", stats.GetTotalIndexCount());
	ImGui::End();

	ImGui::Begin("Color Edit");
	ImGui::ColorEdit4("Birth Color", glm::value_ptr(m_Particle.ColorBegin));
	ImGui::ColorEdit4("Death Color", glm::value_ptr(m_Particle.ColorEnd));
	ImGui::DragFloat("Life Time", &m_Particle.LifeTime, 0.1f, 0.1f, 10.0f);
	ImGui::DragFloat("SizeBegin", &m_Particle.SizeBegin, 0.1f, 0.2f, 5.0f);
	ImGui::DragFloat("SizeEnd (Max = SizeBegin/2)", &m_Particle.SizeEnd, 0.01f, 0.1f, m_Particle.SizeBegin/2);
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(LWEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
