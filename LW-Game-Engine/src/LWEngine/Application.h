#pragma once

#include "Core.h"
#include "Window.h"
#include "LWEngine/LayerStack.h"

#include "LWEngine/Events/Event.h"
#include "LWEngine/Events/ApplicationEvent.h"
#include "LWEngine/ImGui/ImGuiLayer.h"

#include "LWEngine/Renderer/Shader.h"
#include "LWEngine/Renderer/Buffer.h"
#include "LWEngine/Renderer/VertexArray.h"

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
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_SquareShader;

		std::shared_ptr<VertexArray> m_SquareVA;

	private:

		inline static Application* s_Instance = nullptr;
	};

	//. Functions
	// To be defined in client
	Application* CreateApplication();
}
