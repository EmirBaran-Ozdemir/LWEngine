#include "lwpch.h"

#include "ParticleSystem.h"

#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>


ParticleSystem::ParticleSystem(int poolSize)
	:m_PoolIndex(poolSize-1)
{
	m_ParticlePool.resize(poolSize);
}

void ParticleSystem::OnUpdate(LWEngine::Timestep ts)
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		if (particle.LifeRemaining <= 0.0f)
		{
			particle.Active = false;
			continue;
		}

		particle.LifeRemaining -= ts;
		particle.Position += particle.Velocity * (float)ts;
		particle.Rotation += 0.01f * ts;
	}
}

void ParticleSystem::OnRender(LWEngine::OrthographicCamera& camera)
{
	LWEngine::Renderer2D::BeginScene(camera);

	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		float life = particle.LifeRemaining / particle.LifeTime;
		glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);

		float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);
		glm::vec3 position = { particle.Position, 1.0f };
		LWEngine::Renderer2D::DrawQuad(position, { size, size }, color);
	}

	LWEngine::Renderer2D::EndScene();
}

void ParticleSystem::Emit(const ParticleProperties& particleProps)
{
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.Active = true;
	particle.Position = particleProps.Position;
	particle.Rotation = LWEngine::Random::Float() * 2.0f * glm::pi<float>();

	// Velocity
	particle.Velocity = particleProps.Velocity;
	particle.Velocity.x += particleProps.VelocityVariation.x * (LWEngine::Random::Float() - 0.5f);
	particle.Velocity.y += particleProps.VelocityVariation.y * (LWEngine::Random::Float() - 0.5f);

	// Color
	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;

	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;
	particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (LWEngine::Random::Float() - 0.5f);
	particle.SizeEnd = particleProps.SizeEnd;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}