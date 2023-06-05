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
		LWE_CORE_ASSERT(status, "GLAD::INITIALIZATION_FAILED")

	}

	void OpenGLContext::SwapBuffers()
	{
		
		glfwSwapBuffers(m_windowHandle);

	}
}
