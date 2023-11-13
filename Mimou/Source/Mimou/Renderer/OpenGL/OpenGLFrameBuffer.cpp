#include "mepch.h"

#include "OpenGLFrameBuffer.h"

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace Mimou
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& Spec)
	{
		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		glGenTextures(1, &m_ColorAttachmentTex);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentTex);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Spec.Width, Spec.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachmentTex, 0);
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachmentTex);
	}

	void OpenGLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		//glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentTex);
	}

	void OpenGLFrameBuffer::UnBind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//glBindTexture(GL_TEXTURE_2D, 0);
	}

	uint32_t OpenGLFrameBuffer::GetColorAttachmentTexID() const
	{
		return m_ColorAttachmentTex;
	}
}