#include "lwpch.h"
#include "Platform/Windows/WindowsWindow.h"

#include "LWEngine/Events/ApplicationEvent.h"
#include "LWEngine/Events/KeyEvent.h"
#include "LWEngine/Events/MouseEvent.h"

#include "LWEngine/Core/Input.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace LWEngine {

	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		LWE_CORE_ERROR("ERROR::GLFW_{0}::{1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		LWE_PROFILE_FUNCTION();
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		LWE_PROFILE_FUNCTION();
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		LWE_PROFILE_FUNCTION();
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		LWE_CORE_INFO("Creating window {0}, ({1},{2})", props.Title, props.Width, props.Height);


		//! Check GLFWInitialization
		if (s_GLFWWindowCount == 0)
		{
			LWE_PROFILE_SCOPE("glfwInit");
			int success = glfwInit();
			LWE_CORE_ASSERT(success, "ERROR::GLFW::INITIALIZATION_FAILED");

			//! Set error callback which doesn't setted in glfw
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		//! Set window properties and VSync
		{
			LWE_PROFILE_SCOPE("glfwCreateWindow");

			// Set the GLFW window hints for decoration (x and _) buttons
			glfwWindowHint(GLFW_MAXIMIZED,true);

			m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);

			if (!m_Window) {
				LWE_CORE_ERROR("ERROR::GLFW::WINDOW_CREATION_FAILED");
				glfwTerminate();
				return;
			}

			//GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
			//const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
			//glfwSetWindowMonitor(m_Window, primaryMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);

			++s_GLFWWindowCount;
			m_Context = GraphicsContext::Create(m_Window);
		}

		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);

		//! Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}
			});


		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(keycode);
				data.EventCallback(event);

			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		LWE_PROFILE_FUNCTION();
		glfwDestroyWindow(m_Window);
		s_GLFWWindowCount -= 1;

		if (s_GLFWWindowCount == 0)
		{
			LWE_CORE_INFO("Terminating GLFW");
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate()
	{
		LWE_PROFILE_FUNCTION();
		glfwPollEvents();
	}

	void WindowsWindow::OnRender()
	{
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		LWE_PROFILE_SCOPE("glfwSwapInterval");
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}


}
