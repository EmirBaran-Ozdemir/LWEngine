#pragma once

#include "lwpch.h"
#include "LWEngine/Core/Core.h"
#include "LWEngine/Core/KeyCodes.h"
#include "LWEngine/Core/MouseButtonCodes.h"

namespace LWEngine {

	class Input 
	{;
	public:
		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();

		static float GetMouseX();
		static float GetMouseY();
	};
}