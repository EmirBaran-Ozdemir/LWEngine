#include "lwpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace LWEngine {
	
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		LWE_CORE_ASSERT(windowHandle, "Window handle is null")
	}

	void OpenGLContext::Init()
	{
		LWE_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_windowHandle);
		//! Glad initialization
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LWE_CORE_ASSERT(status, "GLAD::INITIALIZATION_FAILED");
		const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
		const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
		const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));

		LWE_CORE_INFO("OpenGL Info:");
		LWE_CORE_INFO("   Vendor: {0}",vendor);
		LWE_CORE_INFO("   Renderer: {0}",renderer);
		LWE_CORE_INFO("   Version: {0}",version);

		//LWE_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "ERROR::OPENGL_VERSION::VERSION_SHOULD_BE_AT_LEAST_4_5");

	}

	void OpenGLContext::SwapBuffers()
	{
		LWE_PROFILE_FUNCTION();
		glfwSwapBuffers(m_windowHandle);

	}
}
