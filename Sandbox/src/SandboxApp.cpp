#include <LWEngine.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"

extern "C" { _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }
extern "C" {__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1; }


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public LWEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.0f, 1.0f, -1.0f, 1.0f), m_CameraPosition(0.0f), m_ObjectPosition(0.0f)
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


		m_SquareVA.reset(LWEngine::VertexArray::Create());
		float squareVertices[5 * 4] = {
			-0.2f,	-0.2f,	0.0f,  0.0f, 0.0f,
			 0.2f,	-0.2f,	0.0f,  1.0f, 0.0f,
			 0.2f,	 0.2f,	0.0f,  1.0f, 1.0f,
			-0.2f,	 0.2f,	0.0f,  0.0f, 1.0f,
		};
		LWEngine::Ref<LWEngine::VertexBuffer> squareVB;
		squareVB.reset(LWEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		LWEngine::BufferLayout squareLayout = {
			{LWEngine::ShaderDataType::Float3, "a_Position"},
			{LWEngine::ShaderDataType::Float2, "a_TexCoord"},
		};
		squareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3,0 };

		LWEngine::Ref<LWEngine::IndexBuffer> squareIB;
		squareIB.reset((LWEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t))));
		m_SquareVA->SetIndexBuffer(squareIB);
		auto squareShader = m_ShaderLib.Load("assets/shaders/SquareShader.glsl");


		auto textureShader = m_ShaderLib.Load("assets/shaders/Texture.glsl");

		m_Texture2D = LWEngine::Texture2D::Create("assets/textures/awesomeface.png");

		std::dynamic_pointer_cast<LWEngine::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<LWEngine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture2D", 0);


		m_TestVA.reset(LWEngine::VertexArray::Create());
		float testVertices[4 * 5] = {
			-1.5f,	-1.5f,	0.0f, -0.5f, -0.5f,
			 1.5f,	-1.5f,	0.0f,  0.5f, -0.5f,
			 1.5f,	 1.5f,	0.0f,  0.5f,  0.5f,
			-1.5f,	 1.5f,	0.0f, -0.5f,  0.5f,
		};
		LWEngine::Ref<LWEngine::VertexBuffer> testVB;
		testVB.reset(LWEngine::VertexBuffer::Create(testVertices, sizeof(testVertices)));
		LWEngine::BufferLayout testLayout = {
			{LWEngine::ShaderDataType::Float3, "a_Position"},
			{LWEngine::ShaderDataType::Float2, "fragCoord"},
		};
		testVB->SetLayout(testLayout);
		m_TestVA->AddVertexBuffer(testVB);

		uint32_t testIndices[6] = { 0, 1, 2, 2, 3,0 };

		LWEngine::Ref<LWEngine::IndexBuffer> testIB;
		testIB.reset(LWEngine::IndexBuffer::Create(testIndices, sizeof(testIndices) / sizeof(uint32_t)));
		m_TestVA->SetIndexBuffer(testIB);

		m_TestShader = LWEngine::Shader::Create("assets/shaders/TestShader.glsl");


	}
	void OnUpdate(LWEngine::Timestep ts) override
	{
		//LWE_CLIENT_TRACE("DeltaTime: {0}s ({1})", ts.GetSeconds(), 1000 / ts.GetMiliseconds());

		float time = ts;

		//. CAMERA MOVEMENTS
		if (LWEngine::Input::IsKeyPressed(LWE_KEY_RIGHT) || LWEngine::Input::IsKeyPressed(LWE_KEY_D))
			m_CameraPosition.x += (m_CameraMovementSpeed + m_CameraAcceleration) * time;
		else if (LWEngine::Input::IsKeyPressed(LWE_KEY_LEFT) || LWEngine::Input::IsKeyPressed(LWE_KEY_A))
			m_CameraPosition.x -= (m_CameraMovementSpeed + m_CameraAcceleration) * time;


		if (LWEngine::Input::IsKeyPressed(LWE_KEY_UP) || LWEngine::Input::IsKeyPressed(LWE_KEY_W))
			m_CameraPosition.z -= (m_CameraMovementSpeed + m_CameraAcceleration) * time;
		else if (LWEngine::Input::IsKeyPressed(LWE_KEY_DOWN) || LWEngine::Input::IsKeyPressed(LWE_KEY_S))
			m_CameraPosition.z += (m_CameraMovementSpeed + m_CameraAcceleration) * time;


		if (LWEngine::Input::IsKeyPressed(LWE_KEY_SPACE))
			m_CameraPosition.y += (m_CameraMovementSpeed + m_CameraAcceleration) * time;
		else if (LWEngine::Input::IsKeyPressed(LWE_KEY_LEFT_SHIFT))
			m_CameraPosition.y -= (m_CameraMovementSpeed + m_CameraAcceleration) * time;

		//. CAMERA ROTATIONS
		if (LWEngine::Input::IsKeyPressed(LWE_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * time;
		if (LWEngine::Input::IsKeyPressed(LWE_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * time;

		//. OBJECT MOVEMENTS
		if (LWEngine::Input::IsKeyPressed(LWE_KEY_J))
			m_ObjectPosition.x -= (m_ObjectMovementSpeed + m_ObjectAcceleration) * time;
		else if (LWEngine::Input::IsKeyPressed(LWE_KEY_L))
			m_ObjectPosition.x += (m_ObjectMovementSpeed + m_ObjectAcceleration) * time;
		if (LWEngine::Input::IsKeyPressed(LWE_KEY_I))
			m_ObjectPosition.y += (m_ObjectMovementSpeed + m_ObjectAcceleration) * time;
		else if (LWEngine::Input::IsKeyPressed(LWE_KEY_K))
			m_ObjectPosition.y -= (m_ObjectMovementSpeed + m_ObjectAcceleration) * time;


		LWEngine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f, 1 });
		LWEngine::RenderCommand::Clear();
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);


		LWEngine::Renderer::BeginScene(m_Camera);

		m_Texture2D->Bind();

		auto squareShader = m_ShaderLib.Get("SquareShader");
		
		std::dynamic_pointer_cast<LWEngine::OpenGLShader>(squareShader)->Bind();
		std::dynamic_pointer_cast<LWEngine::OpenGLShader>(squareShader)->UploadUniformFloat3("u_Color", m_SquareColor);

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

		auto window = &app.GetWindow();


		//std::dynamic_pointer_cast<LWEngine::OpenGLShader>(m_Shader)->Bind();
		//std::dynamic_pointer_cast<LWEngine::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", m_SquareColor);
		//LWEngine::Renderer::Submit(m_Shader, m_VertexArray);
		LWEngine::Renderer::Submit(m_TestShader, m_TestVA);
		std::dynamic_pointer_cast<LWEngine::OpenGLShader>(m_TestShader)->UploadUniformVec2("iResolution",
			{ window->GetWidth() , window->GetHeight()});
		
		std::dynamic_pointer_cast<LWEngine::OpenGLShader>(m_TestShader)->UploadUniformFloat("iTime", ts.GetElapsedTime());

		LWEngine::Renderer::EndScene();

	}

	virtual void OnImGuiRender(LWEngine::Timestep ts) override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(LWEngine::Event& event) override
	{

	}

private:
	LWEngine::ShaderLibrary m_ShaderLib;
	LWEngine::Ref<LWEngine::Shader> m_Shader;
	LWEngine::Ref<LWEngine::VertexArray> m_VertexArray;
	LWEngine::Ref<LWEngine::VertexArray> m_SquareVA;
	LWEngine::Ref<LWEngine::Shader> m_TestShader;
	LWEngine::Ref<LWEngine::VertexArray> m_TestVA;

	LWEngine::Ref<LWEngine::Texture2D> m_Texture2D;
	LWEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMovementSpeed = 5.0f;
	float m_CameraAcceleration = 0.01f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 60.0f;

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
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}

};


LWEngine::Application* LWEngine::CreateApplication()
{
	return new Sandbox();
}