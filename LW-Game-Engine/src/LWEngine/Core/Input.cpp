#include "lwpch.h"
#include "LWEngine/Core/Input.h"

#ifdef LWE_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsInput.h"
#endif

namespace LWEngine {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
#ifdef LWE_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
#else
		LWE_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}