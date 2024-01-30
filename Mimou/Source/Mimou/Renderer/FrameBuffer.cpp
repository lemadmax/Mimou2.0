#include "mepch.h"

#include "FrameBuffer.h"
#include "Renderer.h" 
#include "OpenGL/OpenGLFrameBuffer.h"

namespace Mimou
{

	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& Spec)
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
			return CreateRef<OpenGLFrameBuffer>(Spec);
		}
		}
		ME_ENGINE_ASSERT(false, "Failed to create renderer API");
		return nullptr;
	}

	void FrameBuffer::Add(const FBAttachmentSpecification& Spec)
	{
		m_Spec.Attachments.emplace_back(Spec);
	}
}