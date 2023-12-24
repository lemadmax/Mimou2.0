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
		Material(const std::string& Name, const std::string& ShaderAsset);
		Material(const Material& Other) = default;

		virtual ~Material() = default;
		

		virtual void Bind();

		inline void SetTexture(Ref<Texture> Texture) { m_Texture = Texture; }
		inline Ref<Shader> GetShader() const { return ShaderLibrary::GetInstance()->Get(m_ShaderAsset); }
		inline const std::string& GetName() const { return m_Name; }

	public:

		glm::vec4 m_Ambient = { 0.2f, 0.3f, 0.4f, 1.0f };
		glm::vec4 m_Diffuse = { 0.2f, 0.3f, 0.4f, 1.0f };
		glm::vec4 m_Specular = { 0.9f, 0.8f, 0.9f, 10.0f };
		float m_Transparency = 1.0f;
		float m_IrradiPerp = 1.0f;

	private:
		std::string m_Name;
		std::string m_ShaderAsset = "Default";

		Ref<Texture> m_Texture;
		// TODO: Multiple texture slots
		std::vector<Ref<Texture>> m_Textures;
	};

	class MaterialLibrary
	{
	private:
		MaterialLibrary() = default;

	public:
		static MaterialLibrary* Get()
		{
			if (!s_Instance)
			{
				s_Instance = new MaterialLibrary();
			}
			return s_Instance;
		}

		void Init();
		void LoadMaterialInstances();

		Ref<Material> GetMaterial(const std::string& AssetName);
		std::vector<std::string> GetNames();
		std::vector<std::string> GetNames(const std::string& AssetName, int& Idx);

	private:
		std::map<std::string, Ref<Material>> CachedMats;

		static MaterialLibrary* s_Instance;
	};
}