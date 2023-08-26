#pragma once
#include "Mimou/Renderer/VertexArray.h"

namespace Mimou
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Reference<VertexBuffer>& VertexBuffer) override;
		virtual void AddIndexBuffer(const Reference<IndexBuffer>& IndexBuffer) override;

		virtual const std::vector<Reference<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		virtual const Reference<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
	private:
		std::vector<Reference<VertexBuffer>> m_VertexBuffers;
		Reference<IndexBuffer> m_IndexBuffer;

		uint32_t m_RendererID;
	};
}