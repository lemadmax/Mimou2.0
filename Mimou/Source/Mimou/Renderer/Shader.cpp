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

	ShaderLibrary* ShaderLibrary::s_Instance = new ShaderLibrary();

	ShaderLibrary::ShaderLibrary()
	{

	}

	void ShaderLibrary::InitShaderLib()
	{
		Load("Texture Shader", "Assets/Shaders/Texture.glsl");
		Load("Lambert Shader", "Assets/Shaders/LambertShader.glsl");
		Load("Phong Shader", "Assets/Shaders/PhongShader.glsl");
		Load("Default", "Assets/Shaders/Default.glsl");
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

	std::vector<std::string> ShaderLibrary::GetNames() const
	{
		std::vector<std::string> Names;
		for (auto Pair : m_Shaders)
		{
			Names.push_back(Pair.first);
		}
		return Names;
	}

	bool ShaderLibrary::Exists(const std::string& Name) const
	{
		return m_Shaders.find(Name) != m_Shaders.end();
	}
}