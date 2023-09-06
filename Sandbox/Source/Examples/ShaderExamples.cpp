#include "ShaderExamples.h"

ShaderEgLayer::ShaderEgLayer()
{
	SunShader = Shader::Create("Assets/Shaders/SunShader.glsl");

	SunVertices = VertexArray::Create();

	float Vertices[3 * 4] =
	{
		-1, 1, 0,
		1, 1, 0,
		-1, -1, 0,
		1, -1, 0
	};
	BufferLayout Layout =
	{
		{ "a_Position", ShaderDataType::Float3 }
	};
	uint32_t Indices[6] =
	{
		0, 1, 2, 2, 3, 1
	};

	Reference<VertexBuffer> VertexBuffer = VertexBuffer::Create(Vertices, sizeof(Vertices));
	VertexBuffer->SetLayout(Layout);

	Reference<IndexBuffer> IndexBuffer = IndexBuffer::Create(Indices, 6);
	SunVertices->AddVertexBuffer(VertexBuffer);

	SunVertices->AddIndexBuffer(IndexBuffer);
}

ShaderEgLayer::~ShaderEgLayer()
{
}

void ShaderEgLayer::OnUpdate(Timestep Ts)
{
	RenderCommand::SetClearColor({ 0.8f, 0.8f, 0.8f, 1 });
	RenderCommand::Clear();
	Renderer::Submit(SunVertices, SunShader);
}

void ShaderEgLayer::OnAttach()
{
}

void ShaderEgLayer::OnDetach()
{
}

void ShaderEgLayer::OnImGUIRender()
{
}

void ShaderEgLayer::OnEvent(EventBase& Event)
{
}
