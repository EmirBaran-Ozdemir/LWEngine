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
		//. Triangle
		m_VertexArray.reset(LWEngine::VertexArray::Create());

		float vertices[3 * 3] = {
			-0.5f,	-0.5f,	0.0f,
			0.5f,	-0.5f,	0.0f,
			0.0f,	 0.5f,	0.0f,
		};
		LWEngine::Ref<LWEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(LWEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		LWEngine::BufferLayout layout = {
			{LWEngine::ShaderDataType::Float3, "a_Position"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		LWEngine::Ref<LWEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(LWEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		m_Shader.reset(LWEngine::Shader::Create("assets/shaders/Texture.glsl"));
		
		
		
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



		m_SquareShader.reset(LWEngine::Shader::Create("assets/shaders/SquareTexture.glsl"));

		std::string textureVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec2 v_TexCoord;
			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string textureFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec2 v_TexCoord;

			uniform sampler2D u_Texture2D;

			void main()
			{
				color = texture(u_Texture2D, v_TexCoord);
			}
		)";

		m_TextureShader.reset(LWEngine::Shader::Create(textureVertexSrc, textureFragmentSrc));

		m_Texture2D = LWEngine::Texture2D::Create("assets/textures/awesomeface.png");

		std::dynamic_pointer_cast<LWEngine::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<LWEngine::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture2D", 0);
		
		
		//. TestShader
		
		//m_TestVA.reset(LWEngine::VertexArray::Create());
		//float testVertices[4 * 5] = {
		//	-1.5f,	-1.5f,	0.0f, -0.5f, -0.5f,
		//	 1.5f,	-1.5f,	0.0f,  0.5f, -0.5f,
		//	 1.5f,	 1.5f,	0.0f,  0.5f,  0.5f,
		//	-1.5f,	 1.5f,	0.0f, -0.5f,  0.5f,
		//};
		//LWEngine::Ref<LWEngine::VertexBuffer> testVB;
		//testVB.reset(LWEngine::VertexBuffer::Create(testVertices, sizeof(testVertices)));
		//LWEngine::BufferLayout testLayout = {
		//	{LWEngine::ShaderDataType::Float3, "a_Position"},
		//	{LWEngine::ShaderDataType::Float2, "fragCoord"},
		//};
		//testVB->SetLayout(testLayout);
		//m_TestVA->AddVertexBuffer(testVB);
		//
		//uint32_t testIndices[6] = { 0, 1, 2, 2, 3,0 };
		//
		//LWEngine::Ref<LWEngine::IndexBuffer> testIB;
		//testIB.reset(LWEngine::IndexBuffer::Create(testIndices, sizeof(testIndices) / sizeof(uint32_t)));
		//m_TestVA->SetIndexBuffer(testIB);
		//
		//std::string testVertexSrc = R"(
		//	#version 330 core			
		//
		//	layout(location = 0) in vec3 a_Position;
		//	
		//	uniform mat4 u_Transform;
		//	
		//	void main()
		//	{
		//		gl_Position = u_Transform * vec4(a_Position, 1.0);
		//	}
		//)";
		//
		//std::string testFragmentSrc = R"(
		//	#version 330 core
		//
		//	out vec4 fragColor;
		//
		//	uniform vec2 iResolution;
		//	uniform float iTime;
		//
		//	vec3 palette(float t) {
		//		vec3 a = vec3(0.5, 0.5, 0.5);
		//		vec3 b = vec3(0.5, 0.5, 0.5);
		//		vec3 c = vec3(1.0, 1.0, 1.0);
		//		vec3 d = vec3(0.263, 0.416, 0.557);
		//
		//		return a + b * cos(6.28318 * (c * t + d));
		//	}
		//
		//	void mainImage(out vec4 fragColor, in vec2 fragCoord) {
		//		vec2 uv = (fragCoord * 2.0 - iResolution.xy) / iResolution.y;
		//		vec2 uv0 = uv;
		//		vec3 finalColor = vec3(0.0);
		//
		//		for (float i = 0.0; i < 4.0; i++) {
		//			uv = fract(uv * 1.5) - 0.5;
		//
		//			float d = length(uv) * exp(-length(uv0));
		//
		//			vec3 col = palette(length(uv0) + i * 0.4 + iTime * 0.4);
		//
		//			d = sin(d * 8.0 + iTime) / 8.0;
		//			d = abs(d);
		//
		//			d = pow(0.01 / d, 1.2);
		//
		//			finalColor += col * d;
		//		}
		//
		//		fragColor = vec4(finalColor, 1.0);
		//	}
		//
		//	void main() {
		//		vec2 fragCoord = gl_FragCoord.xy;
		//		mainImage(fragColor, fragCoord);
		//	}
		//)";
		//
		//m_TestShader.reset(LWEngine::Shader::Create(testVertexSrc, testFragmentSrc));
	

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
		
		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f));


		std::dynamic_pointer_cast<LWEngine::OpenGLShader>(m_SquareShader)->Bind();
		std::dynamic_pointer_cast<LWEngine::OpenGLShader>(m_SquareShader)->UploadUniformFloat3("u_Color",m_SquareColor);


		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos + m_ObjectPosition) * scale;
				LWEngine::Renderer::Submit(m_SquareShader, m_SquareVA, transform);
			}
		}

		m_Texture2D->Bind();
		LWEngine::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//std::dynamic_pointer_cast<LWEngine::OpenGLShader>(m_Shader)->Bind();
		//std::dynamic_pointer_cast<LWEngine::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", m_SquareColor);
		//LWEngine::Renderer::Submit(m_Shader, m_VertexArray);
		
		//LWEngine::Renderer::Submit(m_TestShader, m_TestVA);
		//m_TestShader->UploadUniformVec2("iResolution", { LWEngine::m_Window->GetWidth(), LWEngine::m_Window->GetHeight() });
		//m_TestShader->UploadUniformFloat("iTime", LWEngine::elapsedTime);

		LWEngine::Renderer::EndScene();
		
	}
	
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(LWEngine::Event& event) override
	{

	}

private:
	LWEngine::Ref<LWEngine::Shader> m_Shader;
	LWEngine::Ref<LWEngine::VertexArray> m_VertexArray;
	LWEngine::Ref<LWEngine::Shader> m_SquareShader, m_TextureShader;
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