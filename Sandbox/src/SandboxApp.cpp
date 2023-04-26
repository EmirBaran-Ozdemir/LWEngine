#include <LWEngine.h>

class ExampleLayer : public LWEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}
	void OnUpdate() override
	{
		LWE_CLIENT_INFO("ExampleLayer::Update");
	}
	
	void OnEvent(LWEngine::Event& event) override
	{
		LWE_CLIENT_TRACE("{0}", event);
	}
};

class Sandbox :public LWEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new LWEngine::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};


LWEngine::Application* LWEngine::CreateApplication()
{
	return new Sandbox();
}