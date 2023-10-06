#include <LWEngine.h>

//. ----------Entry Point----------
#include <LWEngine/Core/EntryPoint.h>
//. -------------------------------
#include "EditorLayer.h"

extern "C" { _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }
extern "C" {__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0x00000001; }

namespace LWEngine {
	class LWEditor :public Application
	{
	public:
		LWEditor(ApplicationCommandLineArgs args)
			: Application("LWEditor",1920,1080)
		{
			//std::cout << "Give full location of world.png file" << std::endl;
			std::string path = "assets/textures/exampleWorldPlatformer.png";
			//std::cin >> path;

			PushLayer(new EditorLayer(path));
		}
		~LWEditor()
		{

		}

	};


	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new LWEditor(args);
	}
}
