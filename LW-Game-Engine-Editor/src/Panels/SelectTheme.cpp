#include "lwpch.h"
#include "SelectTheme.h"
#include <imgui/imgui.h>
#include "Theme/ImGuiFullDarkTheme.h"
#include "Theme/ImGuiBrightDarkTheme.h"
#include "Theme/ImGuiDarkBlueTheme.h"
#include "Theme/ImGuiDarkGreenTheme.h"

namespace LWEngine {

	ThemeMenu::ThemeMenu()
	{
	}
	ThemeMenu::~ThemeMenu()
	{
	}

	bool ThemeMenu::AddTheme(IImGuiTheme* theme)
	{
		std::string themeName = theme->GetThemeName();
		if (auto thm = m_Themes.find(themeName); thm != m_Themes.end())
			return false;

		bool inited = theme->Init();
		if (!inited)
			return false;


		if (!theme->IsValid())
			return false;

		std::string name = theme->GetThemeName();
		m_Themes.emplace(name, theme);
		m_ThemesVector.push_back(std::make_pair(false, theme));

		return true;
	}

	bool ThemeMenu::Init()
	{
		InitBuildInThemes();
		return true;
	}

	bool ThemeMenu::NeedRender()
	{
		return true;
	}

	void ThemeMenu::Render()
	{
		if (ImGui::BeginMenu("Themes"))
		{
			for (int i = 0; i < m_ThemesVector.size(); i++)
			{
				if (ImGui::MenuItem(m_ThemesVector[i].second->GetThemeName(), "", m_ThemesVector[i].first, !m_ThemesVector[i].first))
				{
					SelectTheme(i);
				}
			}
			ImGui::EndMenu();
		}

	}

	const char* ThemeMenu::GetMenuName()
	{
		return "Themes";
	}

	void ThemeMenu::InitBuildInThemes()
	{
		IImGuiTheme* theme = new ImGuiBrightDarkTheme();
		AddTheme(theme);
		SelectTheme(0);
		theme = new ImGuiFullDarkTheme();
		AddTheme(theme);
		theme = new ImGuiDarkBlueTheme();
		AddTheme(theme);
		theme = new ImGuiDarkGreenTheme();
		AddTheme(theme);
	}

	void ThemeMenu::SelectTheme(int index)
	{

		if (m_SelectedThemeIndex != -1)
		{
			m_ThemesVector[m_SelectedThemeIndex].first = false;
		}

		m_SelectedThemeIndex = index;
		m_ThemesVector[m_SelectedThemeIndex].first = true;
		m_ThemesVector[m_SelectedThemeIndex].second->SetImGuiTheme(ImGui::GetStyle());
	}

	void ThemeMenu::Destroy()
	{
		for (int i = 0; i < m_ThemesVector.size(); i++)
		{
			m_ThemesVector[i].second->Destroy();
			delete m_ThemesVector[i].second;
		}
	}
}