#include "lwpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace LWEngine {

	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::NONE_RENDERER_IS_NOT_SUPPORTED"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLShader(filepath);
		case RendererAPI::API::Direct3D:	LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::DIRECT3D_RENDERER_IS_NOT_SUPPORTED"); return nullptr;
		case RendererAPI::API::Vulkan:		LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::VULKAN_RENDERER_IS_NOT_SUPPORTED"); return nullptr;
		}

		LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::UNKNOWN_API");
		return nullptr;
	}
	
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::NONE_RENDERER_IS_NOT_SUPPORTED"); return nullptr;
			case RendererAPI::API::OpenGL:		return new OpenGLShader(vertexSrc, fragmentSrc);
			case RendererAPI::API::Direct3D:	LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::DIRECT3D_RENDERER_IS_NOT_SUPPORTED"); return nullptr;
			case RendererAPI::API::Vulkan:		LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::VULKAN_RENDERER_IS_NOT_SUPPORTED"); return nullptr;
		}
		
		LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::UNKNOWN_API");
		return nullptr;
	}
}