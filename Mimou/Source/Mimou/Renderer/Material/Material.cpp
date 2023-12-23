#include "mepch.h"
#include "Material.h"

#include "Mimou/Renderer/Shader.h"

namespace Mimou
{
	Material::Material()
	{
	}

	Material::Material(const std::string& Name, const std::string& ShaderAsset)
		: m_Name(Name), m_ShaderAsset(ShaderAsset)
	{
		
	}

	void Material::Bind()
	{
		Ref<Shader> ShaderInst = ShaderLibrary::GetInstance()->Get(m_ShaderAsset);
		if (ShaderInst == nullptr)
		{
			ME_ENGINE_ERROR("Material::Bind: Shader is null");
			return;
		}
		ShaderInst->Bind();
		ShaderInst->SetFloat4("u_Ambient", m_Ambient);
		ShaderInst->SetFloat4("u_Diffuse", m_Diffuse);
		ShaderInst->SetFloat4("u_Specular", m_Specular);
		ShaderInst->SetFloat("u_Transparency", m_Transparency);
		ShaderInst->SetFloat("u_IrradiPerp", 1.0f);
		if (m_Texture)
		{
			m_Texture->Bind(); 
			ShaderInst->SetInt("u_Texture", 0);
		}
	}

	MaterialLibrary* MaterialLibrary::s_Instance = nullptr;

	void MaterialLibrary::Init()
	{
		LoadMaterialInstances();
	}

	void MaterialLibrary::LoadMaterialInstances()
	{
		CachedMats.emplace("PhongMat", CreateRef<Material>("PhongMat", "Phong Shader"));
		CachedMats.emplace("LambertMat", CreateRef<Material>("LambertMat", "Lambert Shader"));
		CachedMats.emplace("TextureMat", CreateRef<Material>("TextureMat", "Texture Shader"));
		CachedMats.emplace("DefaultMat", CreateRef<Material>("DefaultMat", "Default"));
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