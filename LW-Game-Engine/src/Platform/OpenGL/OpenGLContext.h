#pragma once

#include "LWEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace LWEngine {

	class OpenGLContext : public GraphicsContext 
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		
		virtual void Init() override;
		virtual void SwapBuffers() override;
		
	private:
		GLFWwindow* m_windowHandle;
	};

}