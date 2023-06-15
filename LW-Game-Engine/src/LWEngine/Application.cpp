#include "lwpch.h"
#include "Application.h"

#include "LWEngine/Log.h"
#include "glad/glad.h"
#include "LWEngine/Renderer/Renderer.h"

#include "Input.h"

namespace LWEngine {

	Application::Application()
	{
		LWE_CORE_ASSERT(!s_Instance, "WARNING::APPLICATION_ALREADY_EXISTS!")
			s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(LWE_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f,	-0.5f,	0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f,	-0.5f,	0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,	 0.5f,	0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		};
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
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

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

		m_SquareVA.reset(VertexArray::Create());
		float squareVertices[4 * 3] = {
			-0.2f,	-0.2f,	0.0f,
			 0.2f,	-0.2f,	0.0f,
			 0.2f,	 0.2f,	0.0f,
			-0.2f,	 0.2f,	0.0f,
		};
		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		BufferLayout squareLayout = {
			{ShaderDataType::Float3, "a_Position"},
		};
		squareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3,0 };

		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset((IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t))));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string squareVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;
			

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
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

		m_SquareShader.reset(new Shader(squareVertexSrc, squareFragmentSrc));

		//m_TestVA.reset(VertexArray::Create());
		//float testVertices[4 * 5] = {
		//	-0.5f,	-0.5f,	0.0f, -0.5f, -0.5f,
		//	 0.5f,	-0.5f,	0.0f,  0.5f, -0.5f,
		//	 0.5f,	 0.5f,	0.0f,  0.5f,  0.5f,
		//	-0.5f,	 0.5f,	0.0f, -0.5f,  0.5f,
		//};
		//std::shared_ptr<VertexBuffer> testVB;
		//testVB.reset(VertexBuffer::Create(testVertices, sizeof(testVertices)));
		//BufferLayout testLayout = {
		//	{ShaderDataType::Float3, "a_Position"},
		//	{ShaderDataType::Float2, "fragCoord"},
		//};
		//testVB->SetLayout(testLayout);
		//m_TestVA->AddVertexBuffer(testVB);

		//uint32_t testIndices[6] = { 0, 1, 2, 2, 3,0 };

		//std::shared_ptr<IndexBuffer> testIB;
		//testIB.reset(IndexBuffer::Create(testIndices, sizeof(testIndices) / sizeof(uint32_t)));
		//m_TestVA->SetIndexBuffer(testIB);

		//std::string testVertexSrc = R"(
		//	#version 330 core			

		//	layout(location = 0) in vec3 a_Position;
		//	
		//	
		//	void main()
		//	{
		//		
		//		gl_Position = vec4(a_Position, 1.0);
		//	}
		//)";

		//std::string testFragmentSrc = R"(
		//	#version 330 core

		//	out vec4 fragColor;

		//	uniform vec2 iResolution;
		//	uniform float iTime;

		//	vec3 palette(float t) {
		//		vec3 a = vec3(0.5, 0.5, 0.5);
		//		vec3 b = vec3(0.5, 0.5, 0.5);
		//		vec3 c = vec3(1.0, 1.0, 1.0);
		//		vec3 d = vec3(0.263, 0.416, 0.557);

		//		return a + b * cos(6.28318 * (c * t + d));
		//	}

		//	void mainImage(out vec4 fragColor, in vec2 fragCoord) {
		//		vec2 uv = (fragCoord * 2.0 - iResolution.xy) / iResolution.y;
		//		vec2 uv0 = uv;
		//		vec3 finalColor = vec3(0.0);

		//		for (float i = 0.0; i < 4.0; i++) {
		//			uv = fract(uv * 1.5) - 0.5;

		//			float d = length(uv) * exp(-length(uv0));

		//			vec3 col = palette(length(uv0) + i * 0.4 + iTime * 0.4);

		//			d = sin(d * 8.0 + iTime) / 8.0;
		//			d = abs(d);

		//			d = pow(0.01 / d, 1.2);

		//			finalColor += col * d;
		//		}

		//		fragColor = vec4(finalColor, 1.0);
		//	}

		//	void main() {
		//		vec2 fragCoord = gl_FragCoord.xy;
		//		mainImage(fragColor, fragCoord);
		//	}
		//)";

		//m_TestShader.reset(new Shader(testVertexSrc, testFragmentSrc));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(LWE_BIND_EVENT_FN(Application::OnWindowClose));

		// LWE_CORE_TRACE("{0}",e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			m_SquareShader->Bind();
			Renderer::Submit(m_SquareVA);

			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}