#pragma once

#include "lwpch.h"
#include <glm/glm.hpp>
#include "LWEngine/Core/KeyCodes.h"
#include "LWEngine/Core/MouseButtonCodes.h"

namespace LWEngine {

	class Input 
	{;
	public:
		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();

		static float GetMouseX();
		static float GetMouseY();
	};
}