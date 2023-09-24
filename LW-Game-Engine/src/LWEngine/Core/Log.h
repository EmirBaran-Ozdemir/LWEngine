#pragma once

#include <memory>

#include "LWEngine/Core/Core.h"

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace LWEngine {
	
	class Log
	{
	public:
		static void Init();
		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};	
}

//. Core log macros
#define LWE_CORE_CRITICAL(...)   ::LWEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define LWE_CORE_ERROR(...)      ::LWEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LWE_CORE_WARN(...)       ::LWEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LWE_CORE_INFO(...)       ::LWEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LWE_CORE_TRACE(...)      ::LWEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)

//. Client log macros
#define LWE_CLIENT_CRITICAL(...)   ::LWEngine::Log::GetClientLogger()->critical(__VA_ARGS__)
#define LWE_CLIENT_ERROR(...)      ::LWEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define LWE_CLIENT_WARN(...)       ::LWEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LWE_CLIENT_INFO(...)       ::LWEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define LWE_CLIENT_TRACE(...)      ::LWEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
