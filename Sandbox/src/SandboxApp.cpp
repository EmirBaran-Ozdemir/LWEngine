#include <LWEngine.h>

class Sandbox :public LWEngine::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};


LWEngine::Application* LWEngine::CreateApplication()
{
	return new Sandbox();
}