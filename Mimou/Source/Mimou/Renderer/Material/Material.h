#pragma once
#include "Mimou/Renderer/Shader.h"
#include "Mimou/Renderer/Texture.h"

#include "glm/glm.hpp"

namespace Mimou
{
	class Material
	{
	public:
		Material();
		Material(const Material& Other) = default;

		virtual ~Material() = default;
		

		virtual void Bind();

		inline void SetTexture(Ref<Texture> Texture) { m_Texture = Texture; }
		inline Ref<Shader> GetShader() const { return m_Shader; }

	public:

		glm::vec3 m_Ambient = {0.2f, 0.3f, 0.4};
		glm::vec3 m_Diffuse = { 0.2f, 0.3f, 0.4 };
		glm::vec4 m_Specular = { 0.9f, 0.8f, 0.9f, 1.0f };
		float m_Transparency = 1.0f;

	private:
		Ref<Shader> m_Shader;

		Ref<Texture> m_Texture;
		// TODO: Multiple texture slots
		std::vector<Ref<Texture>> m_Textures;
	};
}