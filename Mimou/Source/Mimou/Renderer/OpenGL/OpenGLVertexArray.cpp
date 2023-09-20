#include "mepch.h"

#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Mimou
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
		case Mimou::ShaderDataType::Float:		return GL_FLOAT;
		case Mimou::ShaderDataType::Float2:		return GL_FLOAT;
		case Mimou::ShaderDataType::Float3:		return GL_FLOAT;
		case Mimou::ShaderDataType::Float4:		return GL_FLOAT;
		case Mimou::ShaderDataType::Mat3:		return GL_FLOAT;
		case Mimou::ShaderDataType::Mat4:		return GL_FLOAT;
		case Mimou::ShaderDataType::Int:		return GL_INT;
		case Mimou::ShaderDataType::Int2:		return GL_INT;
		case Mimou::ShaderDataType::Int3:		return GL_INT;
		case Mimou::ShaderDataType::Int4:		return GL_INT;
		case Mimou::ShaderDataType::Bool:		return GL_BOOL;
		}
		ME_ENGINE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& VertexBuffer)
	{
		ME_ENGINE_ASSERT(VertexBuffer->GetLayout().GetElements().size(), "Vertex buffer is empty!");
		glBindVertexArray(m_RendererID);
		VertexBuffer->Bind();
		uint32_t Index = 0;
		const BufferLayout& Layout = VertexBuffer->GetLayout();
		for (const BufferElement& Element : Layout)
		{
			glEnableVertexAttribArray(Index);
			glVertexAttribPointer(
				Index, 
				Element.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(Element.Type),
				Element.Normalized ? GL_TRUE : GL_FALSE, 
				Layout.GetStride(), 
				(const void*)Element.Offset
			);
			Index++;
		}
		m_VertexBuffers.push_back(VertexBuffer);
	}

	void OpenGLVertexArray::AddIndexBuffer(const Ref<IndexBuffer>& IndexBuffer)
	{
		glBindVertexArray(m_RendererID);
		IndexBuffer->Bind();
		m_IndexBuffer = IndexBuffer;
	}
}