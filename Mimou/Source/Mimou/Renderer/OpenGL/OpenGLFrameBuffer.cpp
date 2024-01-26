#include "mepch.h"

#include "OpenGLFrameBuffer.h"

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace Mimou
{
	static void GLTextureFormat(FBFormat Format, GLint& ColorCompsFormat, GLenum& PixelDataFormat, GLenum& DataType)
	{
		switch (Format)
		{
		case FBFormat::INT:
		{
			ColorCompsFormat = GL_R32I;
			PixelDataFormat = GL_RED_INTEGER;
			DataType = GL_BYTE;
			break;
		}
		case FBFormat::RGBA:
		{
			ColorCompsFormat = GL_RGBA;
			PixelDataFormat = GL_RGBA;
			DataType = GL_UNSIGNED_BYTE;
			break;
		}
		case FBFormat::DEPTH_STENCIL:
		{
			ColorCompsFormat = GL_DEPTH24_STENCIL8;
			PixelDataFormat = GL_DEPTH_STENCIL;
			DataType = GL_UNSIGNED_INT_24_8;
			break;
		}
		default:
		{
			ME_ENGINE_ASSERT(false, "FBFormat not supported");
			break;
		}
		}
	}

	static GLenum ColorAttachment(int Idx)
	{
		switch (Idx)
		{
		case 0: return GL_COLOR_ATTACHMENT0;
		case 1: return GL_COLOR_ATTACHMENT1;
		}
	}

	static uint32_t CreateTexture(uint32_t Width, uint32_t Height, GLint InternalFormat, GLenum Format, GLenum Type)
	{
		uint32_t Texture;

		glGenTextures(1, &Texture);
		glBindTexture(GL_TEXTURE_2D, Texture);

		glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, Width, Height, 0, Format, Type, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		return Texture;
	}

	static uint32_t CreateColorAttachment(int Idx, const FrameBufferSpecification& Spec)
	{
		GLint InternalFormat;
		GLenum PixelFormat;
		GLenum DataType;
		GLTextureFormat(Spec.Format, InternalFormat, PixelFormat, DataType);
		uint32_t Texture = CreateTexture(Spec.Width, Spec.Height, InternalFormat, PixelFormat, DataType);

		glFramebufferTexture2D(GL_FRAMEBUFFER, ColorAttachment(Idx), GL_TEXTURE_2D, Texture, 0);
		return Texture;
	}

	static uint32_t CreateDepthStencilAttachment(uint32_t Width, uint32_t Height)
	{
		GLint InternalFormat;
		GLenum PixelFormat;
		GLenum DataType;
		GLTextureFormat(FBFormat::DEPTH_STENCIL, InternalFormat, PixelFormat, DataType);
		uint32_t Texture = CreateTexture(Width, Height, InternalFormat, PixelFormat, DataType);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, Texture, 0);
		return Texture;
	}

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& Spec)
	{
		m_Specs.emplace_back(Spec);
		Invalidate();
		m_DepthStencilAttachTex = CreateDepthStencilAttachment(Spec.Width, Spec.Height);
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		Delete();
	}

	void OpenGLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specs[0].Width, m_Specs[0].Height);
	}

	void OpenGLFrameBuffer::UnBind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	uint32_t OpenGLFrameBuffer::GetColorAttachmentTexID() const
	{
		return m_ColorAttachments[0];
	}

	uint32_t OpenGLFrameBuffer::GetColorAttachmentTexIDByIdx(uint32_t Idx) const
	{
		ME_ENGINE_ASSERT(Idx >= m_ColorAttachments.size(), "Get frame buffer failed, attachment not exists")
		return m_ColorAttachments[Idx];
	}

	uint32_t OpenGLFrameBuffer::GetDepthStencilAttachTexID() const
	{
		return m_DepthStencilAttachTex;
	}

	void OpenGLFrameBuffer::Add(const FrameBufferSpecification& Spec)
	{
		m_Specs.emplace_back(Spec);
		uint32_t ColorAttachment = CreateColorAttachment(m_ColorAttachments.size(), Spec);
		m_ColorAttachments.push_back(ColorAttachment);
	}

	void OpenGLFrameBuffer::OnUpdate(int Idx, uint32_t Width, uint32_t Height)
	{
		if (Width > 0 && Height > 0 && m_Specs[Idx].Width != Width && m_Specs[Idx].Height != Height)
		{
			ResizeInternal(Idx, Width, Height);
		}
		if (Idx == 0)
		{
			glDeleteTextures(1, &m_DepthStencilAttachTex);
			m_DepthStencilAttachTex = CreateDepthStencilAttachment(m_Specs[0].Width, m_Specs[0].Height);
		}
	}

	void OpenGLFrameBuffer::Resize(uint32_t Width, uint32_t Height)
	{
		for (int i = 0; i < m_Specs.size(); i++)
		{
			ResizeInternal(i, Width, Height);
		}
	}

	int OpenGLFrameBuffer::ReadPixelInt(int Idx, uint32_t x, uint32_t y)
	{
		uint32_t Texture = m_ColorAttachments[Idx];

		return 0;
	}

	void OpenGLFrameBuffer::Invalidate()
	{
		if (m_RendererID)
		{
			Delete();
		}
		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		for (int i = 0; i < m_Specs.size(); i++)
		{
			FrameBufferSpecification FBSpec = m_Specs[i];
			uint32_t ColorAttachment = CreateColorAttachment(i, FBSpec);
			m_ColorAttachments.push_back(ColorAttachment);
		}
	}

	void OpenGLFrameBuffer::ResizeInternal(int Idx, uint32_t Width, uint32_t Height)
	{
		m_Specs[Idx].Width = Width;
		m_Specs[Idx].Height = Height;
		uint32_t TextureID = m_ColorAttachments[Idx];
		glDeleteTextures(1, &TextureID);
		m_ColorAttachments[Idx] = CreateColorAttachment(Idx, m_Specs[Idx]);
	}

	void OpenGLFrameBuffer::Delete()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		for (uint32_t TexID : m_ColorAttachments)
		{
			glDeleteTextures(1, &TexID);
		}
		glDeleteTextures(1, &m_DepthStencilAttachTex);
		m_ColorAttachments.clear();
		//glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
	}
}