#pragma once
#include "Mimou/Renderer/GraphicsContext.h"
#include "Mimou/Core.h"

struct GLFWwindow;

namespace Mimou
{
	class ME_API OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* WindowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}