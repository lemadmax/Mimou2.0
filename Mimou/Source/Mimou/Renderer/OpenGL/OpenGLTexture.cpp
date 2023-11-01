#include "mepch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

namespace Mimou
{

	OpenGLTexture2D::OpenGLTexture2D(const TextureSpecification& Specification)
	{
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& Path)
	{
		stbi_set_flip_vertically_on_load(true);
		int Width, Height, Channels;
		unsigned char* Data = stbi_load(Path.c_str(), &Width, &Height, &Channels, 0);

		if (Data)
		{
			GLenum InternalFormat, DataFormat;
			if (Channels == 3)
			{
				InternalFormat = GL_RGB8;
				DataFormat = GL_RGB;
			}
			else if (Channels == 4)
			{
				InternalFormat = GL_RGBA8;
				DataFormat = GL_RGBA;
			}
			m_Width = Width;
			m_Height = Height;
			m_InternalFormat = InternalFormat;
			m_DataFormat = DataFormat;
			glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

			glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, Data);

			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(Data);
		}
		else
		{
			ME_ENGINE_ERROR("OpenGLTexture2D::OpenGLTexture2D Failed to load image: {}", Path);
		}
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* Data, uint32_t Size)
	{
	}

	void OpenGLTexture2D::Bind(uint32_t Slot) const
	{
		glBindTextureUnit(Slot, m_RendererID);
	}
}