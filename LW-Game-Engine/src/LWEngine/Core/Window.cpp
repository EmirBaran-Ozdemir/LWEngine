#include "lwpch.h"
#include "LWEngine/Core/Window.h"

#ifdef LWE_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace LWEngine {

	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef LWE_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(props);

		#else
			LWE_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}

}