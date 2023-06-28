#pragma once


#include "LWEngine/Core/Core.h"
#include "LWEngine/Core/Timestep.h"
namespace LWEngine {

	class LWE_API StaticPanel {
	public:
		static void TopMenuBar(LWEngine::Timestep ts);
		static void BottomMenuBar();
		static void TabMenuBar();
		static void RightMenuBar();
	};
}