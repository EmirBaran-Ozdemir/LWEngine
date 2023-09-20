#pragma once

#include "LWEngine.h"
#include "SelectTheme.h"

namespace LWEngine {

	class WindowPanel
	{
	public:
		WindowPanel();
		static void TopMenuBar(LWEngine::Timestep ts);
		static void BottomMenuBar();
		static void TabMenuBar();
		static void RightMenuBar();
	private:
		static ThemeMenu m_ThemeMenu;
	
	};
}