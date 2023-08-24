#include "mepch.h"

#include "Renderer.h"

namespace Mimou
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::OnWindowResize(uint32_t Width, uint32_t Height)
	{
		RenderCommand::SetViewport(0, 0, Width, Height);
	}

	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Reference<VertexArray>& VertexArray, const glm::mat4& Transfrom)
	{
		VertexArray->Bind();
		RenderCommand::DrawIndexed(VertexArray);
	}
}