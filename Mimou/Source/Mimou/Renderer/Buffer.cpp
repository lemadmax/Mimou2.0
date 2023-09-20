#include "mepch.h"

#include "Buffer.h"
#include "Renderer.h"
#include "OpenGL/OpenGLBuffer.h"

namespace Mimou
{
	Ref<VertexBuffer> VertexBuffer::Create(float* Vertices, uint32_t Size)
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
			return CreateRef<OpenGLVertexBuffer>(Vertices, Size);
		}
		}
		ME_ENGINE_ASSERT(false, "Failed to create renderer API");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* Indices, uint32_t Size)
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
			return CreateRef<OpenGLIndexBuffer>(Indices, Size);
		}
		}
		ME_ENGINE_ASSERT(false, "Failed to create renderer API");
		return nullptr;
	}
}