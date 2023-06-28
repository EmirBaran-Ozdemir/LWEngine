#include "Sandbox2D.h"
#include <Platform/OpenGL/OpenGLShader.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController((float)1280 / 720)
{

}

void Sandbox2D::OnAttach()
{
	m_SquareVA = LWEngine::VertexArray::Create();
	float squareVertices[3 * 4] = {
		-0.2f,	-0.2f,	0.0f,
		 0.2f,	-0.2f,	0.0f,
		 0.2f,	 0.2f,	0.0f,
		-0.2f,	 0.2f,	0.0f,
	};
	LWEngine::Ref<LWEngine::VertexBuffer> squareVB;
	squareVB.reset(LWEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	LWEngine::BufferLayout squareLayout = {
		{LWEngine::ShaderDataType::Float3, "a_Position"},
	};
	squareVB->SetLayout(squareLayout);
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3,0 };

	LWEngine::Ref<LWEngine::IndexBuffer> squareIB;
	squareIB.reset((LWEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t))));
	m_SquareVA->SetIndexBuffer(squareIB);
	auto squareShader = m_ShaderLib.Load("assets/shaders/SquareShader.glsl");

}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(LWEngine::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	LWEngine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f, 1 });
	LWEngine::RenderCommand::Clear();


	LWEngine::Renderer::BeginScene(m_CameraController.GetCamera());

	auto squareShader = m_ShaderLib.Get("SquareShader");

	std::dynamic_pointer_cast<LWEngine::OpenGLShader>(squareShader)->Bind();
	std::dynamic_pointer_cast<LWEngine::OpenGLShader>(squareShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	LWEngine::Renderer::Submit(squareShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	LWEngine::Application& app = LWEngine::Application::Get();

	LWEngine::Renderer::EndScene();

}

void Sandbox2D::OnImGuiRender(LWEngine::Timestep ts)
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(LWEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
