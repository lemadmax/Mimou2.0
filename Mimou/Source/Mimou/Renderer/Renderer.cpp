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

	void Renderer::BeginScene(PerspectiveCamera& Camera)
	{
		m_SceneData->ViewProjectionMatrix = Camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<VertexArray>& VertexArray, const Ref<Shader>& Shader, const glm::mat4& Transfrom)
	{
		Shader->Bind();
		Shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		Shader->SetMat4("u_Transform", Transfrom);
		VertexArray->Bind();

		RenderCommand::DrawIndexed(VertexArray);
	}

	void Renderer::SubmitArrays(const Ref<VertexArray>& VertexArray, const Ref<Shader>& Shader, const glm::mat4& Transfrom)
	{
		Shader->Bind();
		Shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		Shader->SetMat4("u_Transform", Transfrom);
		VertexArray->Bind();

		RenderCommand::DrawArrays(VertexArray);
	}

	void Renderer::SubmitArrays(const Ref<VertexArray>& VertexArray, const Ref<Material>& Material, const Ref<Light>& Light)
	{
		Material->Bind();
		Material->ApplyLighting(Light);
		Material->GetShader()->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		Material->GetShader()->SetMat4("u_Transform", glm::mat4(1.0f));

		VertexArray->Bind();
		RenderCommand::DrawArrays(VertexArray);
	}
}