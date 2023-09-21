#pragma once

#include "Font/ImGuiFont.h"

namespace LWEngine {

	class FontMenu
	{
	public:
		FontMenu();
		~FontMenu();

		bool AddFont(ImGuiFont* font);
		virtual bool Init();
		virtual void Render();
		virtual const char* GetMenuName();
		virtual void InitBuildInFonts();
		virtual void AddWeights();
	private:
		void SelectFontFamily(ImGuiFontFamily fontFamily);
		void SelectFontWeight(ImGuiFontWeight fontWeight);
		void SelectFont(ImGuiFontFamily fontFamily, ImGuiFontWeight fontWeight);

	private:
		std::unordered_map< int, ImGuiFontFamily> m_FontsFamily;
		std::vector<std::pair<bool, ImGuiFontFamily>> m_FontsFamilyVector;
		int m_SelectedFontsFamilyIndex = 0;

		std::vector<std::pair<bool, ImGuiFontWeight>> m_FontsWeightVector;
		int m_SelectedFontsWeightIndex = 0;

		std::unordered_map<int, ImGuiFont*> m_Fonts;

		ImGuiIO m_IO;
		virtual void Destroy();
	};
}
