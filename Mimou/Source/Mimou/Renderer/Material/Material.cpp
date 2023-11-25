#include "mepch.h"
#include "Material.h"

namespace Mimou
{
	Material::Material(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec4 Specular, float Transparency, Ref<Shader> Shader)
		: m_Ambient(Ambient), m_Diffuse(Diffuse), m_Specular(Specular), m_Transparency(Transparency), m_Shader(Shader)
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
}