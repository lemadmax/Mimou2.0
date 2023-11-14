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

		virtual void OnUpdate(uint32_t Width, uint32_t Height) override;
		virtual void Resize(uint32_t Width, uint32_t Height) override;

	private:
		void Invalidate();

		void ResizeInternal(uint32_t Width, uint32_t Height);

	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachmentTex;

		FrameBufferSpecification m_Spec;
	};
}
