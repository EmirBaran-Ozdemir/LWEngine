#include "lwpch.h"
#include "WindowPanel.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>
#include <direct.h>
#include <imgui/imgui_internal.h>

namespace LWEngine {


	WindowPanel::WindowPanel()
	{
		m_ThemeMenu.Init();
		m_FontMenu.Init();
	}

	WindowPanel::WindowPanel(const Ref<Scene>& scene)
	{
		m_Scene = scene;
		m_ThemeMenu.Init();
		m_FontMenu.Init();
		if (!m_Serializer.HasScene())
			m_Serializer = SceneSerializer(m_Scene);
	}

	void WindowPanel::SetContext(const Ref<Scene>& scene)
	{
		m_Scene = scene;
		if (!m_Serializer.HasScene())
			m_Serializer = SceneSerializer(m_Scene);
	}

	void WindowPanel::TopMenuBar(Timestep ts)
	{

		
	}

	void WindowPanel::BottomMenuBar()
	{
		ImGuiViewportP* viewport = (ImGuiViewportP*)(void*)ImGui::GetMainViewport();
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
		float height = ImGui::GetFrameHeightWithSpacing();


		//! First footer
		if (ImGui::BeginViewportSideBar("##FirstFooter", viewport, ImGuiDir_Down, height, window_flags)) {
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Logging"))
				{
					if (ImGui::MenuItem("Log.txt")) {
						//TODO Add browse file
						std::ifstream LogFile("../Test.txt");
						if (LogFile)
						{
							std::string log;
							while (std::getline(LogFile, log)) {
								// Output the text from the file
								std::cout << log << "\n";
							}
							LogFile.close();
						}
						else
							LWE_CLIENT_ERROR("Log file does not found");
					}

					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Performance profiling"))
				{
					static bool enableProfile = false;
					if (ImGui::Button("Start code profile"))
						enableProfile = !enableProfile;
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}
			ImGui::End();
		}

		//! Secondary footer
		if (ImGui::BeginViewportSideBar("##SecondaryFooter", viewport, ImGuiDir_Down, height, window_flags)) {
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("SecondaryLogging"))
				{
					if (ImGui::MenuItem("SecondaryLog.txt")) {
						//TODO Add browse file
						std::ifstream LogFile("../Test.txt");
						if (LogFile)
						{
							std::string log;
							while (std::getline(LogFile, log)) {
								// Output the text from the file
								std::cout << log << "\n";
							}
							LogFile.close();
						}
						else
							LWE_CLIENT_ERROR("Log file does not found");

					}
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}
			ImGui::End();
		}
	}
}
