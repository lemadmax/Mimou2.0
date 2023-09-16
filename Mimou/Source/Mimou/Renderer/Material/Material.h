#pragma once
#include "Mimou/Renderer/Shader.h"
#include "glm/glm.hpp"

namespace Mimou
{
	class Material
	{
	public:
		Material(glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec4 Specular, float Transparency, Reference<Shader> Shader);

		virtual void Bind();
		//virtual void ApplyLighting();

		inline void SetAmbient(glm::vec3 Ambient) { m_Ambient = Ambient; }
		inline void SetDiffuse(glm::vec3 Diffuse) { m_Diffuse = Diffuse; }
		inline void SetSpecular(glm::vec4 Specular) { m_Specular = Specular; }
		inline void SetTransparency(float Transparency) { m_Transparency = Transparency; }

		inline glm::vec3 GetAmbient() const { return m_Ambient; }
		inline glm::vec3 GetDiffuse() const { return m_Diffuse; }
		inline glm::vec4 GetSpecular() const { return m_Specular; }
		inline float GetTransparency() const { return m_Transparency; }

	private:
		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec4 m_Specular;
		float m_Transparency;

		Reference<Shader> m_Shader;
	};
}