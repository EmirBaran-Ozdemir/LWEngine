#pragma once

#ifdef LWE_PLATFORM_WINDOWS

extern LWEngine::Application* LWEngine::CreateApplication();

int main(int argc, char** argv)
{
	LWEngine::Log::Init();
	LWE_CORE_WARN("Initialized Log!");
	LWE_CLIENT_INFO("Initialized Client Log!");
	auto app = LWEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif