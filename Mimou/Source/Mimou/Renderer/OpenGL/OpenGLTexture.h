#pragma once
#include "Mimou/Renderer/Texture.h"

#include <glad/glad.h>

namespace Mimou
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const TextureSpecification& Specification);
		OpenGLTexture2D(const std::string& Path);
		virtual ~OpenGLTexture2D();

		virtual const TextureSpecification& GetSpecification() const override { return m_Specification; }

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetRendererID() const override { return m_RendererID; }

		virtual const std::string& GetPath() const override { return m_Path; }

		virtual void SetData(void* Data, uint32_t Size) override;

		virtual void Bind(uint32_t Slot = 0) const override;

		virtual bool IsLoaded() const override { return m_IsLoaded; }

		virtual bool operator==(const Texture& Other) const override
		{
			return m_RendererID == Other.GetRendererID();
		}
	private:
		TextureSpecification m_Specification;

		std::string m_Path;
		bool m_IsLoaded = false;
		int m_Width, m_Height, m_Channels;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};
}