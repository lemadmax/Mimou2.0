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
		//RenderCommand::ClearDepth();
		m_SceneData->ViewProjectionMatrix = Camera.GetViewProjectionMatrix();
	}

	void Renderer::AddLight(Ref<Light> Light)
	{
		m_SceneData->Lights.push_back(Light);
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<VertexArray>& VertexArray, const Ref<Shader>& Shader, const glm::mat4& Transfrom)
	{
		Shader->Bind();
		Shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		Shader->SetMat4("u_TransformMatrix", Transfrom);
		VertexArray->Bind();

		RenderCommand::DrawIndexed(VertexArray);
	}

	void Renderer::SubmitArrays(const Ref<VertexArray>& VertexArray, const Ref<Material>& Material, const glm::mat4& Transform)
	{
		ME_PROFILE_SCOPE("Renderer::SubmitArrays");
		Material->Bind();
		for (int i = 0; i < m_SceneData->Lights.size(); i++)
		{
			Material->ApplyLighting(i, m_SceneData->Lights[i]);
		}
		Material->GetShader()->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		Material->GetShader()->SetMat4("u_TransformMatrix", Transform);
		glm::mat4 InverseMatrix = glm::inverse(Transform);
		Material->GetShader()->SetMat4("u_InverseMatrix", InverseMatrix);
		VertexArray->Bind();
		RenderCommand::DrawArrays(VertexArray);
	}

	void Renderer::SubmitArrays(const Ref<VertexArray>& VertexArray, const Ref<Shader>& Shader, const glm::mat4& Transform)
	{
		Shader->Bind();
		Shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		Shader->SetMat4("u_TransformMatrix", Transform);
		Shader->SetMat4("u_InverseMatrix", glm::inverse(Transform));
		VertexArray->Bind();

		RenderCommand::DrawArrays(VertexArray);
	}

	void Renderer::SubmitArrays(const Ref<VertexArray>& VertexArray, const Ref<Material>& Material, const Ref<Light>& Light)
	{
		Material->Bind();
		Material->ApplyLighting(0, Light);
		Material->GetShader()->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		Material->GetShader()->SetMat4("u_TransformMatrix", glm::mat4(1.0f));
		Material->GetShader()->SetMat4("u_InverseMatrix", glm::inverse(glm::mat4(1.0f)));

		VertexArray->Bind();
		RenderCommand::DrawArrays(VertexArray);
	}
}