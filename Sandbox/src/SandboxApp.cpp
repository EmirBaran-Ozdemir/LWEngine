#include <LWEngine.h>


class ExampleLayer : public LWEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.0f, 1.0f, -1.0f, 1.0f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(LWEngine::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f,	-0.5f,	0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f,	-0.5f,	0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,	 0.5f,	0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		};
		std::shared_ptr<LWEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(LWEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		LWEngine::BufferLayout layout = {
			{LWEngine::ShaderDataType::Float3, "a_Position"},
			{LWEngine::ShaderDataType::Float4, "a_Color"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<LWEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(LWEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(new LWEngine::Shader(vertexSrc, fragmentSrc));

		m_SquareVA.reset(LWEngine::VertexArray::Create());
		float squareVertices[4 * 3] = {
			-0.2f,	-0.2f,	0.4f,
			 0.2f,	-0.2f,	0.4f,
			 0.2f,	 0.2f,	0.4f,
			-0.2f,	 0.2f,	0.4f,
		};
		std::shared_ptr<LWEngine::VertexBuffer> squareVB;
		squareVB.reset(LWEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		LWEngine::BufferLayout squareLayout = {
			{LWEngine::ShaderDataType::Float3, "a_Position"},
		};
		squareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3,0 };

		std::shared_ptr<LWEngine::IndexBuffer> squareIB;
		squareIB.reset((LWEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t))));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string squareVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string squareFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			
			void main()
			{
				color = vec4(v_Position / 0.5 + 0.5, 1.0);
			}
		)";

		m_SquareShader.reset(new LWEngine::Shader(squareVertexSrc, squareFragmentSrc));

		m_TestVA.reset(LWEngine::VertexArray::Create());
		float testVertices[4 * 5] = {
			-1.5f,	-1.5f,	0.0f, -0.5f, -0.5f,
			 1.5f,	-1.5f,	0.0f,  0.5f, -0.5f,
			 1.5f,	 1.5f,	0.0f,  0.5f,  0.5f,
			-1.5f,	 1.5f,	0.0f, -0.5f,  0.5f,
		};
		std::shared_ptr<LWEngine::VertexBuffer> testVB;
		testVB.reset(LWEngine::VertexBuffer::Create(testVertices, sizeof(testVertices)));
		LWEngine::BufferLayout testLayout = {
			{LWEngine::ShaderDataType::Float3, "a_Position"},
			{LWEngine::ShaderDataType::Float2, "fragCoord"},
		};
		testVB->SetLayout(testLayout);
		m_TestVA->AddVertexBuffer(testVB);

		uint32_t testIndices[6] = { 0, 1, 2, 2, 3,0 };

		std::shared_ptr<LWEngine::IndexBuffer> testIB;
		testIB.reset(LWEngine::IndexBuffer::Create(testIndices, sizeof(testIndices) / sizeof(uint32_t)));
		m_TestVA->SetIndexBuffer(testIB);

		std::string testVertexSrc = R"(
			#version 330 core			

			layout(location = 0) in vec3 a_Position;
			
			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string testFragmentSrc = R"(
			#version 330 core

			out vec4 fragColor;

			uniform vec2 iResolution;
			uniform float iTime;

			vec3 palette(float t) {
				vec3 a = vec3(0.5, 0.5, 0.5);
				vec3 b = vec3(0.5, 0.5, 0.5);
				vec3 c = vec3(1.0, 1.0, 1.0);
				vec3 d = vec3(0.263, 0.416, 0.557);

				return a + b * cos(6.28318 * (c * t + d));
			}

			void mainImage(out vec4 fragColor, in vec2 fragCoord) {
				vec2 uv = (fragCoord * 2.0 - iResolution.xy) / iResolution.y;
				vec2 uv0 = uv;
				vec3 finalColor = vec3(0.0);

				for (float i = 0.0; i < 4.0; i++) {
					uv = fract(uv * 1.5) - 0.5;

					float d = length(uv) * exp(-length(uv0));

					vec3 col = palette(length(uv0) + i * 0.4 + iTime * 0.4);

					d = sin(d * 8.0 + iTime) / 8.0;
					d = abs(d);

					d = pow(0.01 / d, 1.2);

					finalColor += col * d;
				}

				fragColor = vec4(finalColor, 1.0);
			}

			void main() {
				vec2 fragCoord = gl_FragCoord.xy;
				mainImage(fragColor, fragCoord);
			}
		)";

		m_TestShader.reset(new LWEngine::Shader(testVertexSrc, testFragmentSrc));
	}
	void OnUpdate(LWEngine::Timestep ts) override
	{
		LWE_CLIENT_TRACE("DeltaTime: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMiliseconds());

		float time = ts;

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

		
		if (LWEngine::Input::IsKeyPressed(LWE_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * time;
		if (LWEngine::Input::IsKeyPressed(LWE_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * time;


		LWEngine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f, 1 });
		LWEngine::RenderCommand::Clear();
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		
		LWEngine::Renderer::BeginScene(m_Camera);
		LWEngine::Renderer::Submit(m_Shader, m_VertexArray);
		LWEngine::Renderer::Submit(m_SquareShader, m_SquareVA);
		//Renderer::Submit(m_TestShader, m_TestVA);
		//m_TestShader->UploadUniformVec2("iResolution", { m_Window->GetWidth(), m_Window->GetHeight() });
		//m_TestShader->UploadUniformFloat("iTime", elapsedTime);
		LWEngine::Renderer::EndScene();
		
	}
	
	void OnEvent(LWEngine::Event& event) override
	{

	}

private:
	std::shared_ptr<LWEngine::Shader> m_Shader;
	std::shared_ptr<LWEngine::VertexArray> m_VertexArray;
	std::shared_ptr<LWEngine::Shader> m_SquareShader;
	std::shared_ptr<LWEngine::VertexArray> m_SquareVA;
	std::shared_ptr<LWEngine::Shader> m_TestShader;
	std::shared_ptr<LWEngine::VertexArray> m_TestVA;
	LWEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMovementSpeed = 5.0f;
	float m_CameraAcceleration = 0.01f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 60.0f;
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