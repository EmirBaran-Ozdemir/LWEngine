#include "lwpch.h"
#include "LWEngine/Renderer/GraphicsContext.h"

#include "LWEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace LWEngine {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::NONE_RENDERER_IS_NOT_SUPPORTED"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		LWE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}