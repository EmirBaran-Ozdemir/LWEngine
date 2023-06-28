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

#ifdef LWE_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
		LWE_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "OPENGL_VERSION_REQUIREMENT::VERSION_SHOULD_BE_AT_LEAST_4_5");
#endif

	}

	void OpenGLContext::SwapBuffers()
	{
		
		glfwSwapBuffers(m_windowHandle);

	}
}
