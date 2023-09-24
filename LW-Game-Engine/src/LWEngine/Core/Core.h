#pragma once

#include <memory>

#include "LWEngine/Core/PlatformDetection.h"

#define LWE_EXPAND_MACRO(x) x
#define LWE_STRINGIFY_MACRO(x) #x

#define BIT(x) (1<<x)


#define LWE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }


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

#include "LWEngine/Core/Log.h"
#include "LWEngine/Core/Assert.h"
