#include "lwpch.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace LWEngine {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}