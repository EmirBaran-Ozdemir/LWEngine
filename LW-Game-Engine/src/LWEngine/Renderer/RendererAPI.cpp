#include "lwpch.h"
#include "LWEngine/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"
namespace LWEngine {
	
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:    LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::NONE_RENDERER_IS_NOT_SUPPORTED"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
		}

		LWE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}