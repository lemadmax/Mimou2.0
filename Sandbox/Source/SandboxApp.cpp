#include <Mimou.h>

#include "glm/vec3.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"

class ExampleLayer : public Mimou::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		TestRenderer();
		//TestTriangle();
	}

	~ExampleLayer()
	{

	}

	virtual void OnAttach() override
	{

	}

	virtual void OnDetach() override
	{

	}

	virtual void OnUpdate(Mimou::Timestep Ts) override
	{

		RenderCommand::SetClearColor({ 0.8f, 0.8f, 0.8f, 1 });
		RenderCommand::Clear();
		glUseProgram(Program);
		std::string Name = "u_Transform";
		glm::mat4 Matrix(1.0f);
		GLint location = glGetUniformLocation(Program, Name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(Matrix));
		Renderer::Submit(TriangleVertices, TriangleShader);
	}

	virtual void OnImGUIRender() override
	{

	}

	virtual void OnEvent(Mimou::EventBase& Event) override
	{

	}

	void TestTriangle()
	{
		VertexArray;
		glGenVertexArrays(1, &VertexArray);
		glBindVertexArray(VertexArray);

		float Vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};
		
		uint32_t VBuffers;
		glGenBuffers(1, &VBuffers);
		glBindBuffer(GL_ARRAY_BUFFER, VBuffers);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		std::string VertexSrc = R"(
			#version 330 core
			layout (location = 0) in vec3 aPos;

			void main()
			{
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
			}	
		)";

		uint32_t VertexShader;
		VertexShader = glCreateShader(GL_VERTEX_SHADER);
		const char* VertexSrcCStr = (const char*)VertexSrc.c_str();
		glShaderSource(VertexShader, 1, &VertexSrcCStr, NULL);
		glCompileShader(VertexShader);

		int  success;
		char infoLog[512];
		glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
			ME_LOG("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
		}

		std::string FragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 Color;
			
			in vec4 v_Color;
			
			void main()
			{
				Color = vec4(v_Color);
			}
		)";
		uint32_t FragmentShader;
		FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* FragSrcCStr = (const char*)FragmentSrc.c_str();
		glShaderSource(FragmentShader, 1, &FragSrcCStr, NULL);
		glCompileShader(FragmentShader);

		glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
			ME_LOG("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
		}

		uint32_t ShaderProgram;
		ShaderProgram = glCreateProgram();
		glAttachShader(ShaderProgram, VertexShader);
		glAttachShader(ShaderProgram, FragmentShader);
		glLinkProgram(ShaderProgram);

		glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ShaderProgram, 512, NULL, infoLog);
			ME_LOG("ERROR::SHADER::PROGRAM::LINKERROR\n");
		}

		//glDeleteShader(VertexShader);
		//glDeleteShader(FragmentShader);
		TriangleProgram = ShaderProgram;

	}

	void TestRenderer()
	{
		TriangleVertices = VertexArray::Create();

		float Vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};

		Reference<VertexBuffer> VertexBuffer = VertexBuffer::Create(Vertices, sizeof(Vertices));

		BufferLayout Layout =
		{
			{ "a_Position", ShaderDataType::Float3 },
			{ "a_Color", ShaderDataType::Float4 }
		};
		VertexBuffer->SetLayout(Layout);

		TriangleVertices->AddVertexBuffer(VertexBuffer);

		uint32_t Indices[3] =
		{
			0, 1, 2
		};
		Reference<IndexBuffer> IndexBuffer;
		IndexBuffer = IndexBuffer::Create(Indices, 3);
		TriangleVertices->AddIndexBuffer(IndexBuffer);

		std::string VertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;
				gl_Position = vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
			}	
		)";

		std::string FragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 Color;
			
			in vec4 v_Color;
			
			void main()
			{
				Color = vec4(v_Color);
			}
		)";

		TriangleShader = Shader::Create("TriangleShader", VertexSrc, FragmentSrc);
		//Program = glCreateProgram();
		//GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
		//GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//const GLchar* VertexSrcCStr = (const GLchar*)VertexSrc.c_str();
		//glShaderSource(VertexShader, 1, &VertexSrcCStr, 0);
		//const GLchar* FramentSrcCStr = (const GLchar*)FragmentSrc.c_str();
		//glShaderSource(FragmentShader, 1, &FramentSrcCStr, 0);

		//glCompileShader(VertexShader);
		//glCompileShader(FragmentShader);
		//GLint IsCompiled = 0;
		//glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &IsCompiled);
		//if (IsCompiled == GL_FALSE)
		//{
		//	ME_LOG("Failed to compile vertex shader");
		//	return;
		//}
		//glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &IsCompiled);
		//if (IsCompiled == GL_FALSE)
		//{
		//	ME_LOG("Failed to compile fragment shader");
		//	return;
		//}

		//glAttachShader(Program, VertexShader);
		//glAttachShader(Program, FragmentShader);

		//glDeleteShader(VertexShader);
		//glDeleteShader(FragmentShader);

		//glUseProgram(Program);
	}

private:
	Reference<VertexArray> TriangleVertices;
	GLenum Program = 0;
	GLenum VertexArray = 0;
	GLenum TriangleProgram = 0;

	Reference<Shader> TriangleShader;
};

class Sandbox : public Mimou::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

Mimou::Application* Mimou::CreateApplication()
{
	return new Sandbox();
}