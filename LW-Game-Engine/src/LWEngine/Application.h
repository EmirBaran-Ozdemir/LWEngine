#pragma once

#include "Core.h"
#include "Window.h"
#include "LWEngine/LayerStack.h"

#include "LWEngine/Events/Event.h"
#include "LWEngine/Events/ApplicationEvent.h"
#include "LWEngine/ImGui/ImGuiLayer.h"

#include "LWEngine/Renderer/Shader.h"
#include "LWEngine/Renderer/Buffer.h"

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

		inline static Application& Get() { return *s_Instance; } 
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		//! OpenGL Vars
		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:

		inline static Application* s_Instance = nullptr;
	};

	//. Functions
	// To be defined in client
	Application* CreateApplication();
}
