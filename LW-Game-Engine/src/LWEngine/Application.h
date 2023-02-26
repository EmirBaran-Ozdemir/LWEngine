#pragma once

#include "Core.h"

namespace LWEngine{
	class LWE_API Application
	{
	private:
	public:
		Application();
		virtual ~Application();
		//. Public Functions
		void Run();
	};

	//. Functions
	// To be defined in client
	Application* CreateApplication();
}
