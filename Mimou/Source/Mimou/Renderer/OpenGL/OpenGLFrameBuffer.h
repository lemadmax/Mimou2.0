#pragma once
#include "Mimou/Renderer/FrameBuffer.h"

namespace Mimou
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& Spec);
		virtual ~OpenGLFrameBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual uint32_t GetColorAttachmentTexID() const override;

	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachmentTex;
	};
}
