#include "mepch.h"
#include "Material.h"

#include "Mimou/Renderer/Shader.h"

namespace Mimou
{
	Material::Material()
	{
		m_Shader = ShaderLibrary::GetInstance()->Get("Default");
	}

	Material::Material(const std::string& Name, const Ref<Shader>& ShaderInst)
		: m_Name(Name), m_Shader(ShaderInst)
	{
		
	}

	void Material::Bind()
	{
		if (m_Shader == nullptr)
		{
			ME_ENGINE_ERROR("Material::Bind: Shader is null");
			return;
		}
		m_Shader->Bind();
		m_Shader->SetFloat3("u_Ambient", m_Ambient);
		m_Shader->SetFloat3("u_Diffuse", m_Diffuse);
		m_Shader->SetFloat4("u_Specular", m_Specular);
		m_Shader->SetFloat("u_Transparency", m_Transparency);
		m_Shader->SetFloat("u_IrradiPerp", 1.0f);
		if (m_Texture)
		{
			m_Texture->Bind(); 
			m_Shader->SetInt("u_Texture", 0);
		}
	}

	MaterialLibrary* MaterialLibrary::s_Instance = nullptr;

	void MaterialLibrary::Init()
	{
		LoadMaterialInstances();
	}

	void MaterialLibrary::LoadMaterialInstances()
	{
		CachedMats.emplace("PhongMat", CreateRef<Material>("PhongMat", ShaderLibrary::GetInstance()->Get("Phong Shader")));
		CachedMats.emplace("LambertMat", CreateRef<Material>("LambertMat", ShaderLibrary::GetInstance()->Get("Lambert Shader")));
		CachedMats.emplace("TextureMat", CreateRef<Material>("TextureMat", ShaderLibrary::GetInstance()->Get("Texture Shader")));
		CachedMats.emplace("DefaultMat", CreateRef<Material>("DefaultMat", ShaderLibrary::GetInstance()->Get("Default")));
	}

	Ref<Material> MaterialLibrary::GetMaterial(const std::string& AssetName)
	{
		if (CachedMats.contains(AssetName))
		{
			return CachedMats[AssetName];
		}
		return nullptr;
	}

	std::vector<std::string> MaterialLibrary::GetNames()
	{
		std::vector<std::string> Names;
		for (auto Pair : CachedMats)
		{
			Names.push_back(Pair.first);
		}
		return Names;
	}

	std::vector<std::string> MaterialLibrary::GetNames(const std::string& AssetName, int& Idx)
	{
		std::vector<std::string> Names;
		for (auto Pair : CachedMats)
		{
			if (Pair.first == AssetName)
			{
				Idx = Names.size();
			}
			Names.push_back(Pair.first);
		}
		return Names;
	}
}