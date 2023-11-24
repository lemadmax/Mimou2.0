#pragma once
#include "glm/glm.hpp"

namespace Mimou
{
	class ME_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& Name, const int Value) = 0;
		virtual void SetFloat(const std::string& Name, const float Value) = 0;
		virtual void SetFloat3(const std::string& Name, const glm::vec3& Value) = 0;
		virtual void SetFloat4(const std::string& Name, const glm::vec4& Value) = 0;
		virtual void SetMat4(const std::string& Name, const glm::mat4& Value) = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& FilePath);
		static Ref<Shader> Create(const std::string& Name, const std::string& VertexSrc, const std::string& FragmentSrc);
	};

	class ShaderLibrary
	{
	private:
		ShaderLibrary();
	public:
		static ShaderLibrary* GetInstance() { return s_Instance; }
		void InitShaderLib();

		void Add(const Ref<Shader>& Shader);
		void Add(const std::string& Name, const Ref<Shader>& Shader);
		Ref<Shader> Load(const std::string& FilePath);
		Ref<Shader> Load(const std::string& Name, const std::string& FilePath);

		Ref<Shader> Get(const std::string& Name);

		bool Exists(const std::string& Name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;

		static ShaderLibrary* s_Instance;
	};
}