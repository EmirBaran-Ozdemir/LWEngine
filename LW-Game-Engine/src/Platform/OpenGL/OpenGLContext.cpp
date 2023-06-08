#include "lwpch.h"
#include "OpenGLContext.h"

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
	}

	void OpenGLContext::SwapBuffers()
	{
		
		glfwSwapBuffers(m_windowHandle);

	}
}
