#include "mepch.h"
#include "Renderer3D.h"

namespace Mimou
{
	Renderer3D::SceneData* Renderer3D::s_SceneData = new Renderer3D::SceneData;

	void Renderer3D::Init()
	{
		RenderCommand::Init();
	}

	void Renderer3D::Shutdown()
	{

	}

	void Renderer3D::BeginScene(SceneCamera& Camera, std::vector<DirectionalLight> DirLights)
	{
		s_SceneData->ProjectionMatrix = Camera.GetProjection();
		s_SceneData->DirLights = DirLights;
	}

	void Renderer3D::EndScene()
	{

	}
	void Renderer3D::DrawMesh(Ref<VertexArray> VA, Ref<Material> Mat, const glm::mat4& Transform)
	{

		ME_PROFILE_SCOPE("Renderer::SubmitArrays");
		Mat->Bind();

		Ref<Shader> Shader = Mat->GetShader();
		Mat->GetShader()->SetInt("u_nl", s_SceneData->DirLights.size());
		for (int i = 0; i < s_SceneData->DirLights.size(); i++)
		{
			s_SceneData->DirLights[i].SetUniform(i, Mat->GetShader());
		}

		glm::mat4 ViewProjectionMatrix = glm::inverse(Transform) * s_SceneData->ProjectionMatrix;
		Shader->SetMat4("u_ViewProjection", ViewProjectionMatrix);
		Shader->SetMat4("u_TransformMatrix", Transform);
		glm::mat4 InverseMatrix = glm::inverse(Transform);
		Shader->SetMat4("u_InverseMatrix", InverseMatrix);

		VA->Bind();

		RenderCommand::DrawArrays(VA);
	}
}