#include "Sandbox2D.h"
#include <Platform/OpenGL/OpenGLShader.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController((float)1280 / 720)
{

}

void Sandbox2D::OnAttach()
{
	LWE_PROFILE_FUNCTION();

	m_Texture2D = LWEngine::Texture2D::Create("assets/textures/awesomeface.png");
	m_Background = LWEngine::Texture2D::Create("assets/textures/Lake.jpg");
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

	if(jumped)
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
		LWEngine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f, 1 });
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
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f ,1.0f};
				LWEngine::Renderer2D::DrawQuad({x,y}, { 0.2f,0.2f }, m_Texture2D, color);

			}
		}

		LWEngine::Renderer2D::EndScene();

	}


	//std::dynamic_pointer_cast<LWEngine::OpenGLShader>(squareShader)->Bind();
	//std::dynamic_pointer_cast<LWEngine::OpenGLShader>(squareShader)->UploadUniformFloat4("u_Color", m_SquareColor);
}

void Sandbox2D::OnImGuiRender(LWEngine::Timestep ts)
{
	LWE_PROFILE_FUNCTION();

	auto stats = LWEngine::Renderer2D::GetStats();

	ImGui::Begin("Settings");
	ImGui::Text("Renderer Stats");
	ImGui::Text("Draw Calls %d",stats.DrawCalls);
	ImGui::Text("Quad Count %d",stats.QuadCount);
	ImGui::Text("Vertices %d",stats.GetTotalVertexCount());
	ImGui::Text("Indices %d",stats.GetTotalIndexCount());

	
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(LWEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
