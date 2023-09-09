#include "mepch.h"
#include "WindowsWindow.h"
#include "Mimou/Event/AppEvent.h"
#include "Mimou/Event/KeyEvent.h"
#include "Mimou/Event/MouseEvent.h"
#include "Mimou/Renderer/OpenGL/OpenGLContext.h"

namespace Mimou
{
	static bool bIsGLFWInitialized = false;
	static void GLFWErrorCallback(int Error, const char* Desc)
	{
		ME_ERROR("GLFW Error ({0}): {1}", Error, Desc);
	}

	Window* Window::Create(const WindowProps& Props)
	{
		return new WindowsWindow(Props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& Props)
	{
		Init(Props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		m_Context->SwapBuffers();
		glfwPollEvents();
	}

	void WindowsWindow::SetVSync(bool Enabled)
	{
		if (Enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
		m_Data.bVSync = Enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.bVSync;
	}

	void WindowsWindow::Init(const WindowProps& Props)
	{
		m_Data.Title = Props.Title;
		m_Data.Width = Props.Width;
		m_Data.Height = Props.Height;

		ME_LOG("Creating Windows window {0}, ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		if (!bIsGLFWInitialized)
		{
			int Success = glfwInit();
			ME_ENGINE_ASSERT(Success, "Could not initialize GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
			bIsGLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
		//glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LEQUAL);
		//glClearDepth(-1);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* Window, INT32 Width, INT32 Height)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);
				Data.Width = Width;
				Data.Height = Height;

				WindowResizeEvent Event(Data.Title, Width, Height);
				Data.EventCallback(Event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* Window)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);
			
				WindowCloseEvent Event(Data.Title);
				Data.EventCallback(Event);
			});

		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* Window, INT32 Focused)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);
				WindowFocusEvent Event(Data.Title, Focused);
				Data.EventCallback(Event);
			});

		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* Window, INT32 PosX, INT32 PosY)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);
				WindowMoveEvent Event(Data.Title, PosX, PosY);
				Data.EventCallback(Event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* Window, INT32 KeyCode, INT32 ScanCode, INT32 Action, INT32 Mods)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);
				switch (Action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent Event(KeyCode, 0);
						Data.EventCallback(Event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent Event(KeyCode, 1);
						Data.EventCallback(Event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent Event(KeyCode);
						Data.EventCallback(Event);
						break;
					}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* Window, UINT32 KeyCode)
			{
				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);
				KeyTypedEvent Event(KeyCode);
				Data.EventCallback(Event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* Window, INT32 Button, INT32 Action, INT32 Mods)
			{



				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);
				switch (Action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent Event(Button);
						Data.EventCallback(Event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent Event(Button);
						Data.EventCallback(Event);
						break;
					}
				}
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* Window, double xPos, double yPos)
			{

				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);
				MouseMoveEvent Event(xPos, yPos);
				Data.EventCallback(Event);
			});
		
		glfwSetScrollCallback(m_Window, [](GLFWwindow* Window, double xOffset, double yOffset)
			{

				WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(Window);
				MouseScrollEvent Event(xOffset, yOffset);
				Data.EventCallback(Event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

}
