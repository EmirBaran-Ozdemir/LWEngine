#include "lwpch.h"
#include "Application.h"

#include "LWEngine/Events/ApplicationEvent.h"
#include "LWEngine/Log.h"

namespace LWEngine {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());	
	}

	Application::~Application()
	{
	}
	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

}