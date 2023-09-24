#pragma once

#include "LWEngine/Core/Core.h"
#include "LWEngine/Core/Log.h"
#include <filesystem>

#ifdef LWE_ENABLE_ASSERTS

	#define LWE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { LWE##type##ERROR(msg, __VA_ARGS__); LWE_DEBUGBREAK(); } }
	#define LWE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) LWE_INTERNAL_ASSERT_IMPL(type, check, "ERROR::ASSERTION_FAILED::{0}", __VA_ARGS__)
	#define LWE_INTERNAL_ASSERT_NO_MSG(type, check) LWE_INTERNAL_ASSERT_IMPL(type, check, "ERROR::ASSERTION_'{0}'FAILED_AT{1}:{2}", LWE_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define LWE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define LWE_INTERNAL_ASSERT_GET_MACRO(...) LWE_EXPAND_MACRO( LWE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, LWE_INTERNAL_ASSERT_WITH_MSG, LWE_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define LWE_ASSERT(...) LWE_EXPAND_MACRO( LWE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define LWE_CORE_ASSERT(...) LWE_EXPAND_MACRO( LWE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define LWE_ASSERT(...)
	#define LWE_CORE_ASSERT(...)
#endif
