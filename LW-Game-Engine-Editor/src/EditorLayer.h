#pragma once

#include "LWEngine.h"

#include "Systems/ParticleSystem.h"
#include "Systems/WorldGeneration.h"
#include "Systems/Player.h"

namespace LWEngine {
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


	class EditorLayer : public Layer
	{
	public:
		EditorLayer(std::string& path);
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;


		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender(Timestep ts) override;
		void OnEvent(Event& e) override;

	private:
		//? Temp
		ShaderLibrary m_ShaderLib;
		Ref<Shader> m_Shader;
		Ref<VertexArray> m_SquareVA;
		Ref<Texture2D>  m_TextureNull, m_TextureError, m_Background, m_IndustrialTilemap, m_CubeHead;

		Ref<SubTexture2D>  m_SubTextureNull, m_SubTextureError;
		Ref<SubTexture2D>  m_TileDirtTop, m_TileDirtCenter, m_TileDirtLeftCenter, m_TileDirtRightCenter, m_TileDirtMid;
		Ref<SubTexture2D>  m_TileWaterTop, m_TileWaterCenter;
		Ref<SubTexture2D>  m_TileChest;

		Ref<Framebuffer> m_Framebuffer;

		const float sizeMultiplier = 0.01;
		//? Temp

		OrthographicCameraController m_CameraController;
		Player m_Player;

		glm::vec4 m_SquareColor = { 0.2f,0.3f,0.7f,1.0f };
		glm::vec2 m_ViewportSize = { 0.0f,0.0f };

		ParticleSystem m_ParticleSystem;
		ParticleProperties m_Particle;
		WorldGeneration m_World;
		std::unordered_map<glm::vec4, Ref<SubTexture2D>, vec4Hash, vec4Equal> m_TextureMap;
	};
}