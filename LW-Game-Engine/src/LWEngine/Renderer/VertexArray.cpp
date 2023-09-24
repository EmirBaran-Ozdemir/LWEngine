#include "lwpch.h"
#include "LWEngine/Renderer/VertexArray.h"

#include "LWEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace LWEngine {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:			LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::NONE_RENDERER_IS_NOT_SUPPORTED"); return nullptr;
		case RendererAPI::API::OpenGL:			return CreateRef<OpenGLVertexArray>();
		}
		LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::UNKNOWN_API");
		return nullptr;
	}
}
