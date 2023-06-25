#pragma once

#include "LWEngine/Renderer/RendererAPI.h"

namespace LWEngine {

	class OpenGLRendererAPI: public RendererAPI
	{
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}