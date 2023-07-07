#include <LWEngine.h>


//. ----------Entry Point----------
#include <LWEngine/Core/EntryPoint.h>
//. -------------------------------
#include "Sandbox2D.h"


extern "C" { _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }
extern "C" {__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0x00000001; }


class Sandbox :public LWEngine::Application
{
public:
	Sandbox()
		: Application()
	{
		// PushLayer(new ExampleLayer());
		
		PushLayer(new Sandbox2D());
	}
	~Sandbox()
	{

	}

};


LWEngine::Application* LWEngine::CreateApplication()
{
	return new Sandbox();
}