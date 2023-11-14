#include "mepch.h"

#include "OpenGLFrameBuffer.h"

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace Mimou
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& Spec)
		: m_Spec(Spec)
	{
		Invalidate();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachmentTex);
	}

	void OpenGLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Spec.Width, m_Spec.Height);
	}

	void OpenGLFrameBuffer::UnBind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	uint32_t OpenGLFrameBuffer::GetColorAttachmentTexID() const
	{
		return m_ColorAttachmentTex;
	}

	void OpenGLFrameBuffer::OnUpdate(uint32_t Width, uint32_t Height)
	{
		if (Width > 0 && Height > 0 && m_Spec.Width != Width && m_Spec.Height != Height)
		{
			ResizeInternal(Width, Height);
		}
	}

	void OpenGLFrameBuffer::Resize(uint32_t Width, uint32_t Height)
	{
		ResizeInternal(Width, Height);
	}

	void OpenGLFrameBuffer::Invalidate()
	{
		if (m_RendererID)
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(1, &m_ColorAttachmentTex);
		}
		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		glGenTextures(1, &m_ColorAttachmentTex);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentTex);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Spec.Width, m_Spec.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachmentTex, 0);
	}

	void OpenGLFrameBuffer::ResizeInternal(uint32_t Width, uint32_t Height)
	{
		m_Spec.Width = Width;
		m_Spec.Height = Height;
		Invalidate();
	}
}