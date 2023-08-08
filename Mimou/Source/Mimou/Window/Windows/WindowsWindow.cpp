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
	}

	bool WindowsWindow::IsVSync() const
	{
		return false;
	}

	void WindowsWindow::Init(const WindowProps& Props)
	{
		m_Data.Title = Props.Title;
		m_Data.Width = Props.Width;
		m_Data.Height = Props.Height;

		ME_LOG("Creating Windows window {0}, ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		if (!bIsGLFWInitialized)
		{

		}
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

}
