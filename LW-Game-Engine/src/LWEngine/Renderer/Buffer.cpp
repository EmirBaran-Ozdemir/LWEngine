#include "lwpch.h"
#include "Buffer.h"


#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace LWEngine {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:			LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::NONE_RENDERER_IS_NOT_SUPPORTED"); return nullptr;
			case RendererAPI::OpenGL:		return new OpenGLVertexBuffer(vertices, size);
		}
		LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::UNKNOWN_API");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:			LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::NONE_RENDERER_IS_NOT_SUPPORTED"); return nullptr;
			case RendererAPI::OpenGL:		return new OpenGLIndexBuffer(indices, size);
		}
		LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::UNKNOWN_API");
		return nullptr;
	}

}