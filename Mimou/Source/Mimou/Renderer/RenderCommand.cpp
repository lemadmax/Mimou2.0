#include "mepch.h"

#include "RenderCommand.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLRendererAPI.h"

namespace Mimou
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}