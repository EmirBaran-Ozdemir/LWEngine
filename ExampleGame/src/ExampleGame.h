#pragma once

#include "LWEngine.h"

#include "Systems/ParticleSystem.h"

class ExampleGame : public LWEngine::Layer
{
public:
	ExampleGame();
	virtual ~ExampleGame() = default;

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
	LWEngine::Ref<LWEngine::Texture2D>  m_Background, m_FarmSpriteSheet;
	LWEngine::Ref<LWEngine::SubTexture2D>  m_TopFarmTilemap;
	const float sizeMultiplier = 0.01;
	//? Temp

	LWEngine::OrthographicCameraController m_CameraController;
	glm::vec4 m_SquareColor = { 0.2f,0.3f,0.7f,1.0f };
	glm::vec3 m_PlayerPos = { 0.0f,10.0f,0.0f };



	ParticleSystem m_ParticleSystem;
	ParticleProperties m_Particle;
};