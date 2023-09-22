#pragma once

#include "LWEngine.h"
#include "ThemeMenu.h"
#include "FontMenu.h"

namespace LWEngine {

	class WindowPanel
	{
	public:
		WindowPanel();
		WindowPanel(const Ref<Scene>& scene);
		void SetContext(const Ref<Scene>& scene);
		void TopMenuBar(Timestep ts);
		void BottomMenuBar();
	private:
		Ref<Scene> m_Scene;
		ThemeMenu m_ThemeMenu;
		FontMenu m_FontMenu;
		SceneSerializer m_Serializer;
	};
}