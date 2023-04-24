#pragma once

#include "Core.h"
#include "Window.h"
#include "LWEngine/LayerStack.h"

#include "LWEngine/Events/Event.h"
#include "LWEngine/Events/ApplicationEvent.h"


namespace LWEngine{
	class LWE_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		//! Main application
		void Run();
		
		//! Events
		void OnEvent(Event& e);
		
		//! Layers
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//. Functions
	// To be defined in client
	Application* CreateApplication();
}
