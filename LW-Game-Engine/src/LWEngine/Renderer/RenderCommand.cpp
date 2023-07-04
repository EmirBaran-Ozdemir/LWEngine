#include "lwpch.h"

#include "LWEngine/Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace LWEngine {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}