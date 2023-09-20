#pragma once
#include <utility>
#include "Theme/IImGuiTheme.h"

namespace LWEngine {

	class ThemeMenu
	{
	public:
		ThemeMenu();
		~ThemeMenu();

		bool AddTheme(IImGuiTheme* theme);
		virtual bool Init();
		virtual bool NeedRender();
		virtual void Render();
		virtual const char* GetMenuName();
		virtual void InitBuildInThemes();

	private:
		void SelectTheme(int index);


	private:
		std::unordered_map< std::string, IImGuiTheme* > m_Themes;
		std::vector<std::pair<bool, IImGuiTheme*>> m_ThemesVector;
		int m_SelectedThemeIndex = -1;

		virtual void Destroy();
	};
}
