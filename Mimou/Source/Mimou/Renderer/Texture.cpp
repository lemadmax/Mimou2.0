#include "mepch.h"
#include "Texture.h"
#include "Mimou/Renderer/Renderer.h"

#include "Mimou/Renderer/OpenGL/OpenGLTexture.h"

namespace Mimou
{

	Ref<Texture2D> Texture2D::Create(const TextureSpecification& Specification)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
		{
			ME_ENGINE_ASSERT(false, "Renderer API not selected (RendererAPI::None)");
			return nullptr;
		}
		case RendererAPI::API::OpenGL:
		{
			return CreateRef<OpenGLTexture2D>(Specification);
		}
		}
		ME_ENGINE_ASSERT(false, "Failed to create renderer API")
		return nullptr;
	}
	Ref<Texture2D> Texture2D::Create(const std::string& Path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
		{
			ME_ENGINE_ASSERT(false, "Renderer API not selected (RendererAPI::None)");
			return nullptr;
		}
		case RendererAPI::API::OpenGL:
		{
			return CreateRef<OpenGLTexture2D>(Path);
		}
		}
		ME_ENGINE_ASSERT(false, "Failed to create renderer API")
			return nullptr;
	}
}