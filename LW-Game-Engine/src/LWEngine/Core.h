#pragma once

#ifdef LWE_PLATFORM_WINDOWS
	#ifdef LWE_BUILD_DLL
		#define LWE_API __declspec(dllexport)
	#else		
		#define LWE_API __declspec(dllimport)
	#endif
#else
	#error LWEngine only supports Windows
#endif

#ifdef LWE_ENABLE_ASSERTS
	#define LWE_ASSERT(x, ...) {if (!(x)) {LWE_ERROR("ASSERTION_FAILED:{0}", __VA_ARGS__); __debugbreak(); } }
	#define LWE_CORE_ASSERT(x, ...) {if (!(x)) {LWE_CORE_ERROR("ASSERTION_FAILED:{0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LWE_ASSERT(x, ...)
	#define LWE_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1<<x)


#define LWE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
