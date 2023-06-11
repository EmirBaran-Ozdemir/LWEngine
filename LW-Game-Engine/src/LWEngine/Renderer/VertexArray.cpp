#include "lwpch.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace LWEngine {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:			LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::NONE_RENDERER_IS_NOT_SUPPORTED"); return nullptr;
		case RendererAPI::OpenGL:		return new OpenGLVertexArray();
		}
		LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::UNKNOWN_API");
		return nullptr;
	}
}