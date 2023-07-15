#pragma once

#include "LWEngine/Core/Core.h"
#include "LWEngine/Core/Window.h"

#include "LWEngine/Core/LayerStack.h"
#include "LWEngine/Events/Event.h"
#include "LWEngine/Events/ApplicationEvent.h"

#include "LWEngine/Renderer/OrthographicCamera.h"
#include "LWEngine/Core/Timestep.h"
#include "LWEngine/ImGui/ImGuiLayer.h"

namespace LWEngine {
	class Application
	{
	public:
		Application(const std::string& name, uint32_t width, uint32_t height);
		virtual ~Application();

		//! Main application
		void Run();
		void Close();

		//! Events
		void OnEvent(Event& e);

		//! Layers
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true, m_Minimized = false;
		LayerStack m_LayerStack;
		float m_Duration{ 10 };
		float m_LastFrameTime = 0.0f;
		float m_ElapsedTime = 0.0f;
	private:

		inline static Application* s_Instance = nullptr;
	};

	Application* CreateApplication();
}
