#include "lwpch.h"
#include "LWEngine/Renderer/Shader.h"
#include "LWEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace LWEngine {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::NONE_RENDERER_IS_NOT_SUPPORTED"); return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLShader>(filepath);
		case RendererAPI::API::Direct3D:	LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::DIRECT3D_RENDERER_IS_NOT_SUPPORTED"); return nullptr;
		case RendererAPI::API::Vulkan:		LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::VULKAN_RENDERER_IS_NOT_SUPPORTED"); return nullptr;
		}

		LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::UNKNOWN_API");
		return nullptr;
	}
	
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::NONE_RENDERER_IS_NOT_SUPPORTED"); return nullptr;
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
			case RendererAPI::API::Direct3D:	LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::DIRECT3D_RENDERER_IS_NOT_SUPPORTED"); return nullptr;
			case RendererAPI::API::Vulkan:		LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::VULKAN_RENDERER_IS_NOT_SUPPORTED"); return nullptr;
		}
		
		LWE_CORE_ASSERT(false, "RENDERER_API_ERROR::UNKNOWN_API");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		LWE_CORE_ASSERT(!Exists(name), "SHADER_LIBRARY_ERROR::SHADER_ALREADY_EXISTS");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{

		auto shader = Shader::Create( filepath);
		Add(name, shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		LWE_CORE_ASSERT(Exists(name), "SHADER_LIBRARY_ERROR::SHADER_DOESN'T_EXIST");
		return m_Shaders[name];
	}
	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}