//? Put these ptahs into your .h file
#include <LWEngine.h>
//? -----------------------------------

//. ----------Entry Point----------
#include <LWEngine/Core/EntryPoint.h>
//. -------------------------------
#include "ExampleGame.h"


extern "C" { _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }
extern "C" {__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0x00000001; }


class Sandbox :public LWEngine::Application
{
public:
	Sandbox()
		: Application()
	{
		PushLayer(new ExampleGame());
	}
	~Sandbox()
	{

	}

};


LWEngine::Application* LWEngine::CreateApplication()
{
	return new Sandbox();
}