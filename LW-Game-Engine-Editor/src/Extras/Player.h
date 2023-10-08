#pragma once
#include "LWEngine.h"

class Player
{
public:
	Player() {}

	~Player(){}

	void OnUpdate(LWEngine::Timestep ts);

	glm::vec3 GetPlayerPos() const { return m_PlayerPosition; }

private:
	glm::vec3 m_PlayerPosition = { 0.0f,0.0f,0.0f };
	float m_PlayerTranslationSpeed = 10.0f;
	float m_PlayerAcceleration = 0.01f;
	float m_PlayerRotation = 0.0f;
	float m_PlayerRotationSpeed = 60.0f;
};
