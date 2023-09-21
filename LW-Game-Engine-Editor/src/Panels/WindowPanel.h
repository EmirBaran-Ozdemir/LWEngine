#pragma once

#include "LWEngine.h"
#include "ThemeMenu.h"
#include "FontMenu.h"

namespace LWEngine {

	class WindowPanel
	{
	public:
		WindowPanel();
		void TopMenuBar(LWEngine::Timestep ts);
		void BottomMenuBar();
		void TabMenuBar();
		void RightMenuBar();
	private:
		ThemeMenu m_ThemeMenu;
		FontMenu m_FontMenu;
	};
}