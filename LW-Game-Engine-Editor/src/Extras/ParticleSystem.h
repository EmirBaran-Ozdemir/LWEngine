#pragma once

#include <LWEngine.h>

#include <glm/gtc/matrix_transform.hpp>


struct ParticleProperties
{
	glm::vec2 Position;
	glm::vec2 Velocity, VelocityVariation;
	glm::vec4 ColorBegin, ColorEnd;
	float LifeTime;
	float SizeBegin, SizeEnd, SizeVariation;
};

class ParticleSystem
{
public:
	ParticleSystem(int poolSize = 10000);

	void OnUpdate(LWEngine::Timestep ts);
	void OnRender(LWEngine::OrthographicCamera& camera);
	void Emit(const ParticleProperties& properites);

private:
	struct Particle
	{
		glm::vec2 Position;
		glm::vec2 Velocity;
		glm::vec4 ColorBegin, ColorEnd;
		float Rotation = 0.0f;
		float SizeBegin, SizeEnd;

		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
	};
	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex;
};
