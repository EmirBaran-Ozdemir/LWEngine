#include "lwpch.h"
#include "Application.h"

#include "LWEngine/Core/Log.h"
#include "glad/glad.h"
#include "LWEngine/Renderer/Renderer.h"
//#include "LWEngine/Renderer/GraphicsSettings.h"

#include <GLFW/glfw3.h>

namespace LWEngine {

	Application::Application()
	{
		
		LWE_CORE_ASSERT(!s_Instance, "WARNING::APPLICATION_ALREADY_EXISTS!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(LWE_BIND_EVENT_FN(Application::OnEvent));
		
		Renderer::Init();

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
		dispatcher.Dispatch<WindowResizeEvent>(LWE_BIND_EVENT_FN(Application::OnWindowResize));

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
			auto currentTime = std::chrono::high_resolution_clock::now();
			m_ElapsedTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
			Timestep timestep(time - m_LastFrameTime, m_ElapsedTime);
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender(timestep);
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

	
}