#include "mepch.h"

#include "Buffer.h"
#include "Renderer.h"
#include "OpenGL/OpenGLBuffer.h"

namespace Mimou
{
	Reference<VertexBuffer> VertexBuffer::Create(float* Vertices, uint32_t Size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
		{
			ME_ENGINE_ASSERT(false, "Renderer API not selected (RendererAPI::None)");
			return nullptr;
		}
		case RendererAPI::API::OpenGL:
		{
			return std::make_shared<OpenGLVertexBuffer>(Vertices, Size);
		}
		}
		ME_ENGINE_ASSERT(false, "Failed to create renderer API");
		return nullptr;
	}

	Reference<IndexBuffer> IndexBuffer::Create(uint32_t* Indices, uint32_t Size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
		{
			ME_ENGINE_ASSERT(false, "Renderer API not selected (RendererAPI::None)");
			return nullptr;
		}
		case RendererAPI::API::OpenGL:
		{
			return std::make_shared<OpenGLIndexBuffer>(Indices, Size);
		}
		}
		ME_ENGINE_ASSERT(false, "Failed to create renderer API");
		return nullptr;
	}
}