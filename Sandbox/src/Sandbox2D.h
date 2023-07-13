#pragma once

#include "LWEngine.h"

#include "Systems/ParticleSystem.h"

class Sandbox2D : public LWEngine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;


	void OnUpdate(LWEngine::Timestep ts) override;
	virtual void OnImGuiRender(LWEngine::Timestep ts) override;
	void OnEvent(LWEngine::Event& e) override;

private:
	//? Temp
	LWEngine::ShaderLibrary m_ShaderLib;
	LWEngine::Ref<LWEngine::Shader> m_Shader;
	LWEngine::Ref<LWEngine::VertexArray> m_SquareVA;
	LWEngine::Ref<LWEngine::Texture2D> m_Texture2D, m_Background;
	LWEngine::Ref<LWEngine::Framebuffer> m_Framebuffer;
	//? Temp

	LWEngine::OrthographicCameraController m_CameraController;
	glm::vec4 m_SquareColor = { 0.2f,0.3f,0.7f,1.0f };
	glm::vec3 m_PlayerPos = { 0.0f,10.0f,0.0f };
	const float sizeMultiplier = 0.01;

	ParticleSystem m_ParticleSystem;
	ParticleProperties m_Particle;
};