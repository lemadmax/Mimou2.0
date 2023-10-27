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
		int Width, Height, Channels;
		unsigned char* Data = stbi_load(Path.c_str(), &Width, &Height, &Channels, 0);

		if (Data)
		{
			GLenum InternalFormat, DataFormat;
			if (Channels == 3)
			{
				InternalFormat = GL_RGB;
				DataFormat = GL_RGB;
			}
			else if (Channels == 4)
			{
				InternalFormat = GL_RGBA;
				DataFormat = GL_RGBA;
			}
			m_InternalFormat = InternalFormat;
			m_DataFormat = DataFormat;
			glGenTextures(1, &m_RendererID);
			glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, Width, Height, 0, DataFormat, GL_UNSIGNED_BYTE, Data);
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
	}

	void OpenGLTexture2D::SetData(void* Data, uint32_t Size)
	{
	}

	void OpenGLTexture2D::Bind(uint32_t Slot) const
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
}