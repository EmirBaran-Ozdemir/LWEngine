#pragma once

#include <memory>

#ifdef _WIN32
	#ifdef _WIN64
		#define LWE_PLATFORM_WINDOWS
	#else
#error 'ERROR::BUILD::x64_IS_NOT_SUPPORTED'
	#endif
#endif

//. DLL support
#ifdef LWE_PLATFORM_WINDOWS
	#if LWE_DYNAMIC_LINK
		#ifdef LWE_BUILD_DLL
			#define LWE_API __declspec(dllexport)
		#else		
			#define LWE_API __declspec(dllimport)
		#endif
	#else
		#define LWE_API
#endif

#else
	#error LWEngine only supports Windows
#endif

#ifdef LWE_DEBUG
	#define LWE_ENABLE_ASSERTS
#endif

#ifdef LWE_ENABLE_ASSERTS
	#define LWE_ASSERT(x, ...) {if (!(x)) {LWE_ERROR("ERROR::ASSERTION_FAILED:{0}", __VA_ARGS__); __debugbreak(); } }
	#define LWE_CORE_ASSERT(x, ...) {if (!(x)) {LWE_CORE_ERROR("ERROR::ASSERTION_FAILED:{0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LWE_ASSERT(x, ...)
	#define LWE_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1<<x)


#define LWE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


namespace LWEngine {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using WeakRef = std::weak_ptr<T>;

}