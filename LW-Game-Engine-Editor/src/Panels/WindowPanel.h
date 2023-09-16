#pragma once

#include "LWEngine.h"

namespace LWEngine {

	class StaticPanel {
	public:
		static void TopMenuBar(LWEngine::Timestep ts);
		static void BottomMenuBar();
		static void TabMenuBar();
		static void RightMenuBar();
	};
}