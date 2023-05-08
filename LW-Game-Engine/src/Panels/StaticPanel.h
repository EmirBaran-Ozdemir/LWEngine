#pragma once

#include "LWEngine/Core.h"
#include "LWEngine/Events/Event.h"

namespace LWEngine {

	class LWE_API StaticPanel {
	public:
		static void TopMenuBar();
		static void BottomMenuBar();
		static void TabMenuBar();
		static void RightMenuBar();
	};
}