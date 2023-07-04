#pragma once
#include "LWEngine/Core/Core.h"
#ifdef LWE_PLATFORM_WINDOWS

extern LWEngine::Application* LWEngine::CreateApplication();

int main(int argc, char** argv)
{
	LWEngine::Log::Init();

	LWE_PROFILE_BEGIN_SESSION("Startup", "LWEngineProfile-Startup.json");
	auto app = LWEngine::CreateApplication();
	LWE_PROFILE_END_SESSION();
	LWE_PROFILE_BEGIN_SESSION("Runtime", "LWEngineProfile-Runtime.json");
	app->Run();
	LWE_PROFILE_END_SESSION();

	LWE_PROFILE_BEGIN_SESSION("Shutdown", "LWEngineProfile-Shutdown.json");
	delete app;
	LWE_PROFILE_END_SESSION();

}

#endif