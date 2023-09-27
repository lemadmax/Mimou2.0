#include "mepch.h"
#include "Shader.h"
#include "Mimou/Renderer/Renderer.h"
#include "OpenGL/OpenGLShader.h"


namespace Mimou
{
	Ref<Shader> Shader::Create(const std::string& FilePath)
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
			return CreateRef<OpenGLShader>(FilePath);
		}
		}
		ME_ENGINE_ASSERT(false, "Failed to create renderer API");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& Name, const std::string& VertexSrc, const std::string& FragmentSrc)
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
			return CreateRef<OpenGLShader>(Name, VertexSrc, FragmentSrc);
		}
		}
		ME_ENGINE_ASSERT(false, "Failed to create renderer API");
		return nullptr;
	}

	void ShaderLibrary::Add(const Ref<Shader>& Shader)
	{
		const std::string& Name = Shader->GetName();
		Add(Name, Shader);
	}

	void ShaderLibrary::Add(const std::string& Name, const Ref<Shader>& Shader)
	{
		ME_ENGINE_ASSERT(m_Shaders.find(Name) == m_Shaders.end(), "Shader already exists!");
		m_Shaders[Name] = Shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& FilePath)
	{
		Ref<Shader> Shader = Shader::Create(FilePath);
		Add(Shader);
		return Shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& Name, const std::string& FilePath)
	{
		Ref<Shader> Shader = Shader::Create(FilePath);
		Add(Name, Shader);
		return Shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& Name)
	{
		ME_ENGINE_ASSERT(m_Shaders.find(Name) != m_Shaders.end(), "Shader not found!");
		return m_Shaders[Name];
	}

	bool ShaderLibrary::Exists(const std::string& Name) const
	{
		return m_Shaders.find(Name) != m_Shaders.end();
	}
}