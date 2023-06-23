#pragma once

#include "LWEngine/Renderer/RendererAPI.h"

namespace LWEngine {

	class OpenGLRendererAPI: public RendererAPI
	{
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;
		void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}