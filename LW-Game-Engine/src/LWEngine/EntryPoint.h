#pragma once

#ifdef LWE_PLATFORM_WINDOWS

extern LWEngine::Application* LWEngine::CreateApplication();

	int main(int argc, char** argv)
	{
		auto app = LWEngine::CreateApplication();
		app->Run();
		delete app;
	}

#endif