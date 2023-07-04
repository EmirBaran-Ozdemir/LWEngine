#pragma once

#include <memory>

#ifdef _WIN32
	#ifdef _WIN64
		#define LWE_PLATFORM_WINDOWS
	#else
#error 'ERROR::BUILD::x64_IS_NOT_SUPPORTED'
	#endif

#elif defined(__APPLE__) || defined(__MACH__)
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "ERROR::BUILD::IOS_SIMULATOR_IS_NOT_SUPPORTED"
	
	#elif TARGET_OS_IPHONE == 1
		#define LWE_PLATFORM_IOS
		#error "ERROR::BUILD::IOS_IS_NOT_SUPPORTED"

	#elif TARGET_OS_MAC == 1
		#define LWE_PLATFORM_MACOS
		#error "ERROR::BUILD::MACOS_IS_NOT_SUPPORTED"

	#else
		#error "ERROR::BUILD::UNKNOWN_APPLE_PLATFORM"
	#endif

#elif defined(__ANDROID__)
	#define LWE_PLATFORM_ANDROID
	#error "ERROR::BUILD::ANDROID_IS_NOT_SUPPORTED"

#elif defined(__linux__)
	#define LWE_PLATFORM_LINUX
	#error "ERROR::BUILD::LINUX_IS_NOT_SUPPORTED"

#else
	#error "ERROR::BUILD::UNKNOWN_PLATFORM"
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
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&&...args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using WeakRef = std::weak_ptr<T>;

}