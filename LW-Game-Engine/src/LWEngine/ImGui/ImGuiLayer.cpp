#include "lwpch.h"
#include "ImGuiLayer.h"


#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "LWEngine/Application.h"

#include "imgui_internal.h"
#include "Panels/StaticPanel.h"

//. TEMPORARY
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#define IMPL_OPENGL_LOADER_CUSTOM

namespace LWEngine {
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		//! Configs
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiBackendFlags_HasMouseCursors;		//io.ConfigFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.ConfigFlags |= ImGuiWindowFlags_NoSavedSettings;
		
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 5.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	//. ---------WINDOW ELEMENTS---------

	void ImGuiLayer::OnImGuiRender(Timestep ts)
	{
		
		static bool show = true;
		ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);
		//// Create the main window
		//ImGui::Begin("Main Window");

		//// Add content to the main window
		//ImGui::Text("This is the main window");

		//ImGui::End(); // End the main window

		//// Create a dockable frame
		//ImGui::SetNextWindowDockID(ImGui::GetID("Dockable Frame"), ImGuiDockNodeFlags_PassthruCentralNode);
		

		
		StaticPanel::TopMenuBar(ts);
		StaticPanel::TabMenuBar();
		StaticPanel::BottomMenuBar();
		StaticPanel::RightMenuBar();
		

#ifdef LWE_DEBUG
		static bool showDebug = false;
		if (ImGui::BeginMenu("Demo Window"))
		{
			if (ImGui::MenuItem("Show ImGui Demo Window", NULL, &showDebug))
			{
				showDebug = -showDebug;	
			}
			
			ImGui::EndMenu();
		}
		
		if (showDebug)
		{
			ImGui::ShowDemoWindow();
			
		}
#endif // _DEBUG		
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		//! Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

}


