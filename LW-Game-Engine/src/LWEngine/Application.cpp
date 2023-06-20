#include "lwpch.h"
#include "Application.h"

#include "LWEngine/Log.h"
#include "glad/glad.h"
#include "LWEngine/Renderer/Renderer.h"
#include "LWEngine/Renderer/GraphicsSettings.h"

#include <GLFW/glfw3.h>

namespace LWEngine {

	Application::Application()
	{
		
		LWE_CORE_ASSERT(!s_Instance, "WARNING::APPLICATION_ALREADY_EXISTS!")
			s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(LWE_BIND_EVENT_FN(Application::OnEvent));
		m_Window->SetVSync(false);
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
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
		auto startTime = std::chrono::high_resolution_clock::now();
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			//auto currentTime = std::chrono::high_resolution_clock::now();
			//float elapsedTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

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