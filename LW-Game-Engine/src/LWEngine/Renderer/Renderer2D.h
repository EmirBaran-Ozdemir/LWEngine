#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"


namespace LWEngine {

	class Renderer2D 
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		//. Primitives
		//. TODO: Cleanup - UniformBuffers

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);	
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint, float tilingFactor = 1.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint, float tilingFactor = 1.0f);
		
		
		static void DrawQuadRotated(const glm::vec2& position, const glm::vec2& size, float rotation,  const Ref<Texture2D>& texture, const glm::vec4& tint, float tilingFactor = 1.0f);																		   
		static void DrawQuadRotated(const glm::vec3& position, const glm::vec2& size, float rotation,  const Ref<Texture2D>& texture, const glm::vec4& tint, float tilingFactor = 1.0f);
	};
}