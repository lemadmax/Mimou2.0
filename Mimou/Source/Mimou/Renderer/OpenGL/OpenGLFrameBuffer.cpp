#include "mepch.h"

#include "OpenGLFrameBuffer.h"

#include "glad/glad.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

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
			DataType = GL_UNSIGNED_BYTE;
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

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + Idx, GL_TEXTURE_2D, Texture, 0);
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
		Invalidate();
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
		//glReadBuffer(GL_COLOR_ATTACHMENT1);
		//glNamedFramebufferReadBuffer(m_RendererID, GL_COLOR_ATTACHMENT0);

		glm::vec4 Data;
		glReadPixels(x, y, 1, 1, GL_RGBA, GL_FLOAT, glm::value_ptr(Data));
		ME_ENGINE_LOG("Pixel Color: ({},{},{},{})", Data.x, Data.y, Data.z, Data.w);

		glReadBuffer(GL_COLOR_ATTACHMENT1);
		int IntData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &IntData);
		ME_ENGINE_LOG("Pixel Entity: {}", IntData);

		return 0;
	}

	void OpenGLFrameBuffer::ClearAttachmentInt(int Idx, int Value)
	{
		glClearTexImage(m_ColorAttachments[1], 0, GL_RED_INTEGER, GL_INT, &Value);
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

		if (m_Specs.size() > 1)
		{
			GLenum Buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(m_ColorAttachments.size(), Buffers);
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
		glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteTextures(1, &m_DepthStencilAttachTex);
		m_ColorAttachments.clear();
	}
}