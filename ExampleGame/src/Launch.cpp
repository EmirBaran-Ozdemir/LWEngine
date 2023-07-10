#include <LWEngine.h>

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
		//std::cout << "Give full location of world.png file" << std::endl;
		std::string path = "assets/textures/exampleWorldPlatformer.png";
		//std::cin >> path;
		
		PushLayer(new ExampleGame(path));
	}
	~Sandbox()
	{

	}

};


LWEngine::Application* LWEngine::CreateApplication()
{
	return new Sandbox();
}