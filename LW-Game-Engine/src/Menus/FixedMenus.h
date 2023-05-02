#pragma once

#include "LWEngine/Core.h"
#include "LWEngine/Events/Event.h"

namespace LWEngine {

	class LWE_API FixedMenus {
	public:
		static void TopMenuBar();
		static bool BottomMenuBarImpl();
		static void BottomMenuBar();
		
	};
}