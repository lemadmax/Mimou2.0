#include "mepch.h"

#include "VertexArray.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLVertexArray.h"

namespace Mimou
{
	Reference<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
		{
			ME_ENGINE_ASSERT(false, "Renderer API not selected (RendererAPI::None)");
			return nullptr;
		}
		case RendererAPI::API::OpenGL:
		{
			return std::make_shared<OpenGLVertexArray>();
		}
		}
		ME_ENGINE_ASSERT(false, "Failed to create renderer API");
		return nullptr;
	}
}