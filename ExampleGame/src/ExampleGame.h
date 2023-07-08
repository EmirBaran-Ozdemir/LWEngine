#pragma once

#include "LWEngine.h"

#include "Systems/ParticleSystem.h"
#include "WorldGeneration.h"

struct vec4Hash
{
	std::size_t operator()(const glm::vec4& vec) const
	{
		// Convert the vector to four integers and hash them
		std::size_t h1 = std::hash<float>{}(vec.x);
		std::size_t h2 = std::hash<float>{}(vec.y);
		std::size_t h3 = std::hash<float>{}(vec.z);
		std::size_t h4 = std::hash<float>{}(vec.w);

		// Combine the hashes
		return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
	}
};

struct vec4Equal
{
	bool operator()(const glm::vec4& lhs, const glm::vec4& rhs) const
	{
		// Compare each component of the vectors
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
	}
};


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
	LWEngine::Ref<LWEngine::Texture2D>  m_TextureNull, m_Background, m_IndustrialSpriteSheet;
	LWEngine::Ref<LWEngine::SubTexture2D>  m_SubTextureNull, m_TopDirtTilemap, m_MidWaterTilemap;
	glm::vec4 m_ColTopFarmTilemap = { 255.0f,0.0f,0.0f,1.0f }, m_ColMidWaterTilemap = { 0.0f,0.0f,255.0f,1.0f };
	const float sizeMultiplier = 0.01;
	//? Temp
	
	LWEngine::OrthographicCameraController m_CameraController;
	glm::vec4 m_SquareColor = { 0.2f,0.3f,0.7f,1.0f };
	glm::vec3 m_PlayerPos = { 0.0f,10.0f,0.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProperties m_Particle;
	WorldGeneration m_World;
	std::unordered_map<glm::vec4, LWEngine::Ref<LWEngine::SubTexture2D>, vec4Hash, vec4Equal> m_TextureMap;
};