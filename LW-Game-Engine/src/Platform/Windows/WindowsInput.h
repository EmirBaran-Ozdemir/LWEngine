#pragma once

#include "LWEngine/Core/Input.h"

namespace LWEngine {

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) override ;
		virtual std::pair<float, float> GetMousePositionImpl() override ;
		virtual bool IsMouseButtonPressedImpl(MouseCode button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}