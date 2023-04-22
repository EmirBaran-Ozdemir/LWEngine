#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace LWEngine{
	class LWE_API Application
	{
	public:
		Application();
		virtual ~Application();
		//. Public Functions
		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//. Functions
	// To be defined in client
	Application* CreateApplication();
}
