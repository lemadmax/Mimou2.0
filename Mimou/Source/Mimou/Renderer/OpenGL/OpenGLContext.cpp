#include "mepch.h"
#include "OpenGLContext.h"
#include "Mimou/Application.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Mimou
{
	OpenGLContext::OpenGLContext(GLFWwindow* WindowHandle)
		: m_WindowHandle(WindowHandle)
	{
		ME_ENGINE_ASSERT(WindowHandle, "Failed to initialize opengl context: WindowHandle is null");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int Status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ME_ENGINE_ASSERT(Status, "Failed to initialize Glad!");

		ME_ENGINE_LOG("OpenGL graphics context initialized: ");
		ME_ENGINE_LOG("OpenGL vendor: {}", glGetString(GL_VENDOR));
		ME_ENGINE_LOG("OpenGL renderer: {}", glGetString(GL_RENDERER));
		ME_ENGINE_LOG("OpenGL version: {}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
