#pragma once

#include "lwpch.h"
#include "LWEngine/Core/Core.h"
#include "LWEngine/Core/KeyCodes.h"
#include "LWEngine/Core/MouseButtonCodes.h"

namespace LWEngine {

	class Input 
	{
	protected:
		Input() = default;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;
	public:
		static bool IsKeyPressed(KeyCode keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

		static float GetMouseX(MouseCode button) { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY(MouseCode button) { return s_Instance->GetMouseYImpl(); }

		static Scope<Input> Create();
	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) = 0;

		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Scope<Input> s_Instance;
	
	};
}