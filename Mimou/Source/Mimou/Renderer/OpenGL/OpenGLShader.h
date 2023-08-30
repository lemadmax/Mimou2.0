#pragma once
#include "Mimou/Renderer/Shader.h"
#include "glad/glad.h"

namespace Mimou
{
	class ME_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& FilePath);
		OpenGLShader(const std::string& Name, const std::string& VertexSrc, const std::string& FragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& Name, int Value) override;
		virtual void SetFloat3(const std::string& Name, const glm::vec3& Value) override;
		virtual void SetFloat4(const std::string& Name, const glm::vec4& Value) override;
		virtual void SetMat4(const std::string& Name, const glm::mat4& Value) override;

		virtual const std::string& GetName() const override { return m_Name; }

		void UploadUniformInt(const std::string& Name, int Value);

		void UploadUniformFloat(const std::string& Name, float Value);
		void UploadUniformFloat2(const std::string& Name, const glm::vec2& Value);
		void UploadUniformFloat3(const std::string& Name, const glm::vec3& Value);
		void UploadUniformFloat4(const std::string& Name, const glm::vec4& Value);

		void UploadUniformMat3(const std::string& Name, const glm::mat3& Value);
		void UploadUniformMat4(const std::string& Name, const glm::mat4& Matrix);
	private:
		std::unordered_map<GLenum, std::string> Preprocess(const std::string& Source);
		void Compile(const std::unordered_map<GLenum, std::string>& ShaderSources);
	private:
		uint32_t m_RendererID = 0;
		std::string m_Name;
	};
}