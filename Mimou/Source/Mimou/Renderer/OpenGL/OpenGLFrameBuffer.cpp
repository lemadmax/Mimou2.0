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

	static void AttachTextureColor(int Idx, uint32_t TextureID, uint32_t Width, uint32_t Height, GLint InternalFormat, GLenum Format, GLenum Type)
	{
		glBindTexture(GL_TEXTURE_2D, TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, Width, Height, 0, Format, Type, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + Idx, GL_TEXTURE_2D, TextureID, 0);
	}

	static void AttachTextureDepth(uint32_t TextureID, uint32_t Width, uint32_t Height)
	{
		glBindTexture(GL_TEXTURE_2D, TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, Width, Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, TextureID, 0);
	}

	static void CreateTextures(uint32_t number, uint32_t Width, uint32_t Height, GLuint* OutTextures)
	{
		glCreateTextures(GL_TEXTURE_2D, number, OutTextures);
	}

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& Spec)
	{
		m_Spec = Spec;
		Invalidate();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		Delete();
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

	void OpenGLFrameBuffer::OnUpdate(uint32_t Width, uint32_t Height)
	{
		if (Width > 0 && Height > 0 && (m_Spec.Width != Width || m_Spec.Height != Height))
		{			
			ResizeInternal(Width, Height);
		}
	}

	void OpenGLFrameBuffer::Resize(uint32_t Width, uint32_t Height)
	{
		ResizeInternal(Width, Height);
	}

	int OpenGLFrameBuffer::ReadPixelInt(int Idx, uint32_t x, uint32_t y)
	{
		//glNamedFramebufferReadBuffer(m_RendererID, GL_COLOR_ATTACHMENT1);

		//glm::vec4 Data;
		//float Data[4] = {};
		//glReadPixels(x, y, 1, 1, GL_RGBA, GL_FLOAT, Data);
		//ME_ENGINE_LOG("Pixel Color: ({},{},{},{})", Data[0], Data[1], Data[2], Data[3]);

		//glNamedFramebufferReadBuffer(m_RendererID, GL_COLOR_ATTACHMENT2);
		//glm::vec4 Data1;
		//glReadPixels(x, y, 1, 1, GL_RGBA, GL_FLOAT, glm::value_ptr(Data1));
		//ME_ENGINE_LOG("Pixel Color2: ({},{},{},{})", Data1.x, Data1.y, Data1.z, Data1.w);
		//glReadBuffer(GL_COLOR_ATTACHMENT1);

		//int IntData = -1;
		//glReadPixels(x, y, 1, 1, GL_RED, GL_INT, &IntData);
		//ME_ENGINE_LOG("Pixel Entity: {}", IntData);
		int EntityIdx = y * m_Spec.Width + x;
		if (EntityIdx >= m_Spec.Height * m_Spec.Width) return -2;

		int* IDImage = new int[m_Spec.Height * m_Spec.Width];
		glGetTextureImage(m_ColorAttachments[Idx], 0, GL_RED_INTEGER, GL_INT, m_Spec.Height * m_Spec.Width * 4, IDImage);
		//ME_ENGINE_LOG("Entity Pixel: ({})", IDImage[EntityIdx]);

		//float* Image = new float[m_Spec.Height * m_Spec.Width * 4];
		//glGetTextureImage(m_ColorAttachments[1], 0, GL_RGBA, GL_FLOAT, m_Spec.Height * m_Spec.Width * 4 * 4, Image);
		//int idx = y * m_Spec.Width * 4 + x * 4;
		//ME_ENGINE_LOG("Image Pixel: ({},{},{},{})", Image[idx], Image[idx+1], Image[idx+2], Image[idx+3]);
		int Out = IDImage[EntityIdx];
		delete[] IDImage;
		//delete Image;
		return Out;
	}

	void OpenGLFrameBuffer::ClearAttachmentInt(int Idx, int Value)
	{
		glClearTexImage(m_ColorAttachments[Idx], 0, GL_RED_INTEGER, GL_INT, &Value);
	}

	void OpenGLFrameBuffer::ClearAttachmentColor(int Idx, glm::vec4 Value)
	{
		glm::u8vec4 ClearColor(Value.r * 255, Value.g * 255, Value.b * 255, Value.a * 255);
		glClearTexImage(m_ColorAttachments[Idx], 0, GL_RGBA, GL_UNSIGNED_BYTE, glm::value_ptr(ClearColor));
	}

	void OpenGLFrameBuffer::Invalidate()
	{
		if (m_RendererID)
		{
			Delete();
		}
		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		m_ColorAttachments.resize(m_Spec.Attachments.size());
		CreateTextures(m_ColorAttachments.size(), m_Spec.Width, m_Spec.Height, m_ColorAttachments.data());
		for (int i = 0; i < m_Spec.Attachments.size(); i++)
		{
			FBAttachmentSpecification FBSpec = m_Spec.Attachments[i];
			GLint InternalFormat;
			GLenum PixelFormat;
			GLenum DataType;
			GLTextureFormat(FBSpec.Format, InternalFormat, PixelFormat, DataType);
			AttachTextureColor(i, m_ColorAttachments[i], m_Spec.Width, m_Spec.Height, InternalFormat, PixelFormat, DataType);
		}
		CreateTextures(1, m_Spec.Width, m_Spec.Height, &m_DepthStencilAttachTex);
		AttachTextureDepth(m_DepthStencilAttachTex, m_Spec.Width, m_Spec.Height);

		if (m_ColorAttachments.size() > 1)
		{
			GLenum Buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(m_ColorAttachments.size(), Buffers);
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::ResizeInternal(uint32_t Width, uint32_t Height)
	{
		m_Spec.Width = Width;
		m_Spec.Height = Height;
		Invalidate();
	}

	void OpenGLFrameBuffer::Delete()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteTextures(1, &m_DepthStencilAttachTex);
		
		m_ColorAttachments.clear();
		m_DepthStencilAttachTex = 0;
	}
}