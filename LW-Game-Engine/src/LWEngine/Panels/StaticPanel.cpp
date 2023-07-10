#include "lwpch.h"
#include "LWEngine\Panels\StaticPanel.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include <direct.h>
#include <imgui_internal.h>

namespace LWEngine {


	void StaticPanel::TopMenuBar(LWEngine::Timestep ts)
	{
		ImGuiViewportP* viewport = (ImGuiViewportP*)(void*)ImGui::GetMainViewport();
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
		float height = ImGui::GetFrameHeight();

		//! First menu bar
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open", "CTRL+O")) {/*! OPEN FILE*/ }
				if (ImGui::MenuItem("New", "CTRL+N")) {/*! NEW FILE*/ }
				ImGui::Separator();
				if (ImGui::MenuItem("Save", "CTRL+S")) { LWE_CLIENT_TRACE("File saved"); }
				if (ImGui::MenuItem("Exit", NULL, false)) LWEngine::Application::Get().Close();

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				if (ImGui::MenuItem("Redo", "CTRL+SHIFT+Z", false, false)) {}  // Disabled item
				ImGui::Separator();
				if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				if (ImGui::MenuItem("Paste", "CTRL+V")) {}
				ImGui::EndMenu();
			}

			ImGui::Text("%f fps", 1000 / ts.GetMiliseconds());


			bool showDebug = false;
			if (ImGui::BeginMenu("Demo Window"))
			{
				if (ImGui::MenuItem("Show ImGui Demo Window", NULL, &showDebug))
				{
					showDebug = !showDebug;
				}

				ImGui::EndMenu();
			}

			if (showDebug)
			{
				ImGui::ShowDemoWindow();
			}

			ImGui::EndMainMenuBar();
		}
#ifdef LWE_TEST
		//! Tool menu window
		if (ImGui::BeginViewportSideBar("##ToolMenuBar", viewport, ImGuiDir_Up, height, window_flags)) {
			if (ImGui::BeginMenuBar())
			{
				ImGui::Text("ToolMenuBar");
				ImGui::EndMenuBar();
			}
			ImGui::End();
		}

		//! Open tabs menu 
		if (ImGui::BeginViewportSideBar("##OpenTabsMenuBar", viewport, ImGuiDir_Up, height, window_flags)) {
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
				{
					if (ImGui::BeginTabItem("Description"))
					{
						ImGui::Begin("Window for test docking");
						if (ImGui::BeginMenu("Dock Window"))
						{
							ImGui::Text("Hope");
							ImGui::EndMenu();
						}
						ImGuiID dockspace_id = ImGui::GetID("Window for test docking");
						ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
						ImGui::End();
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("Details"))
					{
						ImGui::Text("ID: 0123456789");

						ImGui::Begin("Second window for test docking");
						if (ImGui::BeginMenu("Second Dock Window"))
						{
							ImGui::Text("Hope");
							ImGui::EndMenu();
						}
						ImGui::End();
						ImGui::EndTabItem();
					}
					ImGui::EndTabBar();
				}
				ImGui::EndMenuBar();
			}
			ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
			ImGuiID dockspace_id = ImGui::GetID("##OpenTabsMenuBar");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
			ImGui::End();
		}
#endif // _DEBUG	
		

	}

	void StaticPanel::BottomMenuBar()
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

#ifdef LWE_TEST
	void StaticPanel::TabMenuBar()
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		if (ImGui::BeginTabBar("MyTabBar"))
		{
			if (ImGui::Button("openPopUP"))
				ImGui::OpenPopup("TEEST");
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("It is a surprise");
			if (ImGui::BeginPopup("MyHelpMenu"))
			{
				ImGui::Selectable("Hello!");
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

				ImGui::EndPopup();
			}
			ImGui::EndTabBar();
		}
	}
#endif
	void StaticPanel::RightMenuBar()
	{

		
	}

}
