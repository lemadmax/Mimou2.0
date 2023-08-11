#include "mepch.h"
#include "WindowsWindow.h"

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

		SetVSync(true);

		//glfwSetWindowSizeCallback(m_Window, )
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

}
