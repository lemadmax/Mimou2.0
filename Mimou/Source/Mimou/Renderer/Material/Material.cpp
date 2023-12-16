#include "mepch.h"
#include "Material.h"

namespace Mimou
{
	Material::Material()
	{
		m_Shader = ShaderLibrary::GetInstance()->Get("Default");
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
}