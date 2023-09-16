#include "mepch.h"
#include "OpenGLShader.h"
#include "Mimou/Utils/FileUtils/FileHelper.h"

#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace Mimou
{
	static GLenum ShaderTypeFromString(const std::string& Type)
	{
		if (Type == "vertex") return GL_VERTEX_SHADER;
		if (Type == "fragment" || Type == "pixel") return GL_FRAGMENT_SHADER;

		ME_ENGINE_ASSERT(false, "Unknown shader type");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& FilePath)
	{
		std::string Source = FileHelper::Get()->ReadFile(FilePath);
		std::unordered_map<GLenum, std::string> ShaderSources = Preprocess(Source);
		Compile(ShaderSources);

		m_Name = FileHelper::Get()->GetFileNameFromPath(FilePath);
	}

	OpenGLShader::OpenGLShader(const std::string& Name, const std::string& VertexSrc, const std::string& FragmentSrc)
		: m_Name(Name)
	{
		std::unordered_map<GLenum, std::string> Sources;
		Sources[GL_VERTEX_SHADER] = VertexSrc;
		Sources[GL_FRAGMENT_SHADER] = FragmentSrc;
		Compile(Sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& Name, int Value)
	{
		UploadUniformInt(Name, Value);
	}

	void OpenGLShader::SetFloat(const std::string& Name, float Value)
	{
		UploadUniformFloat(Name, Value);
	}

	void OpenGLShader::SetFloat3(const std::string& Name, const glm::vec3& Value)
	{
		UploadUniformFloat3(Name, Value);
	}

	void OpenGLShader::SetFloat4(const std::string& Name, const glm::vec4& Value)
	{
		UploadUniformFloat4(Name, Value);
	}

	void OpenGLShader::SetMat4(const std::string& Name, const glm::mat4& Value)
	{
		UploadUniformMat4(Name, Value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& Name, int Value)
	{
		GLint Location = glGetUniformLocation(m_RendererID, Name.c_str());
		glUniform1i(Location, Value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& Name, float Value)
	{
		GLint Location = glGetUniformLocation(m_RendererID, Name.c_str());
		glUniform1f(Location, Value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& Name, const glm::vec2& Value)
	{
		GLint Location = glGetUniformLocation(m_RendererID, Name.c_str());
		glUniform2f(Location, Value.x, Value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& Name, const glm::vec3& Value)
	{
		GLint Location = glGetUniformLocation(m_RendererID, Name.c_str());
		glUniform3f(Location, Value.x, Value.y, Value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& Name, const glm::vec4& Value)
	{
		GLint Location = glGetUniformLocation(m_RendererID, Name.c_str());
		glUniform4f(Location, Value.x, Value.y, Value.z, Value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& Name, const glm::mat3& Value)
	{
		GLint Location = glGetUniformLocation(m_RendererID, Name.c_str());
		glUniformMatrix3fv(Location, 1, GL_FALSE, glm::value_ptr(Value));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& Name, const glm::mat4& Matrix)
	{
		GLint Location = glGetUniformLocation(m_RendererID, Name.c_str());
		glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(Matrix));
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(const std::string& Source)
	{
		std::unordered_map<GLenum, std::string> ShaderSources;

		const char* TypeToken = "#type";
		size_t TypeTokenLen = strlen(TypeToken);
		size_t Pos = Source.find(TypeToken, 0);
		while (Pos != std::string::npos)
		{
			size_t EOL = Source.find_first_of("\r\n", Pos);
			ME_ENGINE_ASSERT(EOL != std::string::npos, "OpenGLSHader::Preprocess: Syntax error");
			size_t Begin = Pos + TypeTokenLen + 1;
			std::string Type = Source.substr(Begin, EOL - Begin);
			ME_ENGINE_ASSERT(ShaderTypeFromString(Type), "OpenGLShader::Preprocess: Invalid shader type specified");
			
			size_t NextLinePos = Source.find_first_not_of("\r\n", EOL);
			Pos = Source.find(TypeToken, NextLinePos);
			ShaderSources[ShaderTypeFromString(Type)] = Source.substr(NextLinePos, Pos - (NextLinePos == std::string::npos ? Source.size() - 1 : NextLinePos));
		}

		return ShaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& ShaderSources)
	{
		GLuint Program = glCreateProgram();
		
		std::array<GLenum, 2> GLShaderIDs;
		int GLShaderIDIndex = 0;
		for (auto& kv : ShaderSources)
		{
			GLenum Type = kv.first;
			const std::string& Source = kv.second;

			GLuint Shader = glCreateShader(Type);

			const GLchar* SourceCStr = (const GLchar*)Source.c_str();
			glShaderSource(Shader, 1, &SourceCStr, NULL);
			glCompileShader(Shader);

			int Success;
			glGetShaderiv(Shader, GL_COMPILE_STATUS, &Success);
			if (!Success)
			{
				GLint Length = 0;
				glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &Length);

				// The maxLength includes the NULL character
				std::vector<GLchar> InfoLog(Length);
				glGetShaderInfoLog(Shader, Length, &Length, &InfoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(Shader);

				// Use the infoLog as you see fit.
				ME_ENGINE_ERROR("OpenGLShader::Compile {}", InfoLog.data());
				ME_ENGINE_ASSERT(false, "Shader compilation failure!");
				return;
			}
			glAttachShader(Program, Shader);
			GLShaderIDs[GLShaderIDIndex++] = Shader;
		}

		glLinkProgram(Program);

		GLint isLinked = 0;
		glGetProgramiv(Program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint Length = 0;
			glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &Length);

			std::vector<GLchar> InfoLog(Length);
			glGetProgramInfoLog(Program, Length, &Length, &InfoLog[0]);

			glDeleteProgram(Program);
			// Don't leak shaders.
			for (auto id : GLShaderIDs)
				glDeleteShader(id);

			ME_ENGINE_ERROR("{0}", InfoLog.data());
			ME_ENGINE_ASSERT(false, "Link program failure!");
			return;
		}

		// Always detach shaders after a successful link.
		for (auto id : GLShaderIDs)
			glDeleteShader(id);

		m_RendererID = Program;
	}
}