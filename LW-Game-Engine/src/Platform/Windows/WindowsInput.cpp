#include "lwpch.h"
#include "LWEngine/Core/Input.h"

#include "LWEngine/Core/Application.h"
#include <GLFW/glfw3.h>

namespace LWEngine {

	bool Input::IsKeyPressed(KeyCode keycode)
	{

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, static_cast<int32_t>(keycode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	
	std::pair<float, float> Input::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { (float)xPos, (float)yPos };
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));

		return state == GLFW_PRESS;
	}

	float Input::GetMouseX()
	{
		auto [x, _] = GetMousePosition();
		return x;
	}

	float Input::GetMouseY()
	{
		auto [_, y] = GetMousePosition();
		return y;
	}

}