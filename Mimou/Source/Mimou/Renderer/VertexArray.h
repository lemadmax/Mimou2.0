#pragma once

#include "Buffer.h"

namespace Mimou
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Reference<VertexBuffer>& VertexBuffer) = 0;
		virtual void AddIndexBuffer(const Reference<IndexBuffer>& IndexBuffer) = 0;

		virtual const std::vector<Reference<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Reference<IndexBuffer>& GetIndexBuffer() const = 0;

		static Reference<VertexArray> Create();
	};
}