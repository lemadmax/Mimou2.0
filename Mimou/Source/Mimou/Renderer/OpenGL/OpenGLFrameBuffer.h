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
		virtual uint32_t GetColorAttachmentTexIDByIdx(uint32_t Idx) const override;
		virtual uint32_t GetDepthStencilAttachTexID() const override;

		virtual void Add(const FrameBufferSpecification& Spec) override;

		virtual void OnUpdate(int Idx, uint32_t Width, uint32_t Height) override;
		virtual void Resize(uint32_t Width, uint32_t Height) override;

		virtual int ReadPixelInt(int Idx, uint32_t x, uint32_t y) override;
		virtual void ClearAttachmentInt(int Idx, int Value) override;
		virtual void ClearAttachmentColor(int Idx, glm::vec4 Value) override;

	private:
		void Invalidate();

		void ResizeInternal(int Idx, uint32_t Width, uint32_t Height);

		

		void Delete();

	private:
		uint32_t m_RendererID;

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthStencilAttachTex;
	};
}
