//? Put these ptahs into your .h file
#include <LWEngine.h>
//? -----------------------------------

//. ----------Entry Point----------
#include <LWEngine/Core/EntryPoint.h>
//. -------------------------------
#include "Sandbox2D.h"

 
//? Put these paths into your .cpp file
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLTexture.h"


#define IMGUI_DEFINE_MATH_OPERATORS
#include  <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//? -----------------------------------

extern "C" { _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }
extern "C" {__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1; }



class ExampleLayer : public LWEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController((float)1280/720), m_ObjectPosition(0.0f)
	{
		////. Triangle
		//m_VertexArray.reset(LWEngine::VertexArray::Create());
		//float vertices[3 * 3] = {
		//	-0.5f,	-0.5f,	0.0f,
		//	0.5f,	-0.5f,	0.0f,
		//	0.0f,	 0.5f,	0.0f,
		//};
		//LWEngine::Ref<LWEngine::VertexBuffer> vertexBuffer;
		//vertexBuffer.reset(LWEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		//LWEngine::BufferLayout layout = {
		//	{LWEngine::ShaderDataType::Float3, "a_Position"},
		//};
		//vertexBuffer->SetLayout(layout);
		//m_VertexArray->AddVertexBuffer(vertexBuffer);
		//uint32_t indices[3] = { 0, 1, 2 };
		//LWEngine::Ref<LWEngine::IndexBuffer> indexBuffer;
		//indexBuffer.reset(LWEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		//m_VertexArray->SetIndexBuffer(indexBuffer);
		//m_Shader = LWEngine::Shader::Create("assets/shaders/Texture.glsl");


		m_SquareVA = LWEngine::VertexArray::Create();
		float squareVertices[5 * 4] = {
			-0.2f,	-0.2f,	0.0f,  0.0f, 0.0f,
			 0.2f,	-0.2f,	0.0f,  1.0f, 0.0f,
			 0.2f,	 0.2f,	0.0f,  1.0f, 1.0f,
			-0.2f,	 0.2f,	0.0f,  0.0f, 1.0f,
		};
		LWEngine::Ref<LWEngine::VertexBuffer> squareVB;
		squareVB = LWEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		LWEngine::BufferLayout squareLayout = {
			{LWEngine::ShaderDataType::Float3, "a_Position"},
			{LWEngine::ShaderDataType::Float2, "a_TexCoord"},
		};
		squareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3,0 };

		LWEngine::Ref<LWEngine::IndexBuffer> squareIB;
		squareIB = (LWEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);
		auto squareShader = m_ShaderLib.Load("assets/shaders/SquareShader.glsl");


		auto textureShader = m_ShaderLib.Load("assets/shaders/Texture.glsl");
		m_Texture2D = LWEngine::Texture2D::Create("assets/textures/awesomeface.png");
		textureShader->Bind();
		textureShader->SetInt("u_Texture2D", 0);


		m_TestVA = LWEngine::VertexArray::Create();
		float testVertices[4 * 5] = {
			-1.5f,	-1.5f,	0.0f, -0.5f, -0.5f,
			 1.5f,	-1.5f,	0.0f,  0.5f, -0.5f,
			 1.5f,	 1.5f,	0.0f,  0.5f,  0.5f,
			-1.5f,	 1.5f,	0.0f, -0.5f,  0.5f,
		};
		LWEngine::Ref<LWEngine::VertexBuffer> testVB;
		testVB = LWEngine::VertexBuffer::Create(testVertices, sizeof(testVertices));
		LWEngine::BufferLayout testLayout = {
			{LWEngine::ShaderDataType::Float3, "a_Position"},
			{LWEngine::ShaderDataType::Float2, "fragCoord"},
		};
		testVB->SetLayout(testLayout);
		m_TestVA->AddVertexBuffer(testVB);

		uint32_t testIndices[6] = { 0, 1, 2, 2, 3,0 };

		LWEngine::Ref<LWEngine::IndexBuffer> testIB;
		testIB = LWEngine::IndexBuffer::Create(testIndices, sizeof(testIndices) / sizeof(uint32_t));
		m_TestVA->SetIndexBuffer(testIB);

		m_TestShader = LWEngine::Shader::Create("assets/shaders/TestShader.glsl");


	}
	void OnUpdate(LWEngine::Timestep ts) override
	{
		//LWE_CLIENT_TRACE("DeltaTime: {0}s ({1})", ts.GetSeconds(), 1000 / ts.GetMiliseconds());
		m_CameraController.OnUpdate(ts);

		LWEngine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f, 1 });
		LWEngine::RenderCommand::Clear();



		LWEngine::Renderer::BeginScene(m_CameraController.GetCamera());

		m_Texture2D->Bind();

		auto squareShader = m_ShaderLib.Get("SquareShader");
		
		squareShader->Bind();
		squareShader->SetFloat3("u_Color", m_SquareColor);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f));
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos + m_ObjectPosition) * scale;
				LWEngine::Renderer::Submit(squareShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLib.Get("Texture");
		LWEngine::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		LWEngine::Application& app = LWEngine::Application::Get();

		m_Window = &app.GetWindow();


		//std::dynamic_pointer_cast<LWEngine::OpenGLShader>(m_Shader)->Bind();
		//std::dynamic_pointer_cast<LWEngine::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", m_SquareColor);
		//LWEngine::Renderer::Submit(m_Shader, m_VertexArray);
		//LWEngine::Renderer::Submit(m_TestShader, m_TestVA);
		//std::dynamic_pointer_cast<LWEngine::OpenGLShader>(m_TestShader)->UploadUniformVec2("iResolution",
		//	{ m_Window->GetWidth() , m_Window->GetHeight()});
		//
		//std::dynamic_pointer_cast<LWEngine::OpenGLShader>(m_TestShader)->UploadUniformFloat("iTime", ts.GetElapsedTime());

		LWEngine::Renderer::EndScene();

		//. OBJECT MOVEMENTS
		if (LWEngine::Input::IsKeyPressed(LWE_KEY_J))
			m_ObjectPosition.x -= (m_ObjectMovementSpeed + m_ObjectAcceleration) * ts;
		else if (LWEngine::Input::IsKeyPressed(LWE_KEY_L))
			m_ObjectPosition.x += (m_ObjectMovementSpeed + m_ObjectAcceleration) * ts;
		if (LWEngine::Input::IsKeyPressed(LWE_KEY_I))
			m_ObjectPosition.y += (m_ObjectMovementSpeed + m_ObjectAcceleration) * ts;
		else if (LWEngine::Input::IsKeyPressed(LWE_KEY_K))
			m_ObjectPosition.y -= (m_ObjectMovementSpeed + m_ObjectAcceleration) * ts;

	}

	virtual void OnImGuiRender(LWEngine::Timestep ts) override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(LWEngine::Event& e) override
	{
		m_CameraController.OnEvent(e);

	}

private:
	LWEngine::ShaderLibrary m_ShaderLib;
	LWEngine::Ref<LWEngine::Shader> m_Shader;
	LWEngine::Ref<LWEngine::VertexArray> m_VertexArray;
	LWEngine::Ref<LWEngine::VertexArray> m_SquareVA;
	LWEngine::Ref<LWEngine::Shader> m_TestShader;
	LWEngine::Ref<LWEngine::VertexArray> m_TestVA;

	LWEngine::Ref<LWEngine::Texture2D> m_Texture2D;
	LWEngine::OrthographicCameraController m_CameraController;

	LWEngine::Window* m_Window;

	glm::vec3 m_ObjectPosition;
	float m_ObjectMovementSpeed = 2.0f;
	float m_ObjectAcceleration = 0.01f;
	float m_ObjectRotation = 0.0f;
	float m_ObjectRotationSpeed = 60.0f;

	glm::vec3 m_SquareColor = { 0.2f,0.3f,0.7f };

};

class Sandbox :public LWEngine::Application
{
public:
	Sandbox()
		: Application()
	{
		// PushLayer(new ExampleLayer());
		
		PushLayer(new Sandbox2D());
	}
	~Sandbox()
	{

	}

};


LWEngine::Application* LWEngine::CreateApplication()
{
	return new Sandbox();
}