#include "lwpch.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "FixedMenus.h"
#include <imgui.cpp>
#include <direct.h>

namespace LWEngine {
	
	
	void FixedMenus::TopMenuBar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open", "CTRL+O")) {/*! OPEN FILE*/ }
				if (ImGui::MenuItem("New", "CTRL+N")) {/*! NEW FILE*/ }
				ImGui::Separator();
				if (ImGui::MenuItem("Save", "CTRL+S")) { LWE_CLIENT_TRACE("File saved"); }

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
				ImGui::Separator();
				if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				if (ImGui::MenuItem("Paste", "CTRL+V")) {}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}
	bool FixedMenus::BottomMenuBarImpl()
	{
        ImGuiContext& g = *GImGui;
        ImGuiViewportP* viewport = (ImGuiViewportP*)(void*)ImGui::GetMainViewport();

        ImGui::SetCurrentViewport(NULL, viewport);
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        
        g.NextWindowData.MenuBarOffsetMinVal = ImVec2(g.Style.DisplaySafeAreaPadding.x, ImMax(g.Style.DisplaySafeAreaPadding.y - g.Style.FramePadding.y, 0.0f));
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
        float height = ImGui::GetFrameHeight(); 	

        bool is_open = ImGui::BeginViewportSideBar("##FooterMenuBar", viewport, ImGuiDir_Down, height, window_flags);
        g.NextWindowData.MenuBarOffsetMinVal = ImVec2(0.0f, 0.0f);
        
        if (is_open)
            ImGui::BeginMenuBar();
        else
            ImGui::End();
        return is_open;
        
	}
    void FixedMenus::BottomMenuBar()
    {
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;

        if (BottomMenuBarImpl())
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
                        LWE_CLIENT_ERROR("Log file does not foound");
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }
    
}