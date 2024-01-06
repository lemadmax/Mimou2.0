#include "mepch.h"
#include "Renderer3D.h"
#include "Mimou/Mesh/StaticMesh.h"

namespace Mimou
{
	Renderer3D::SceneData* Renderer3D::s_SceneData = new Renderer3D::SceneData;

	void Renderer3D::Init()
	{
		RenderCommand::Init();
		StaticMeshLibrary::Init();

		// Shader must be initialized before material
		ShaderLibrary::GetInstance()->InitShaderLib();
		MaterialLibrary::Get()->Init();
		s_SceneData->DefaultMat = CreateRef<Material>();
	}

	void Renderer3D::Shutdown()
	{

	}

	void Renderer3D::OnWindowResized(uint32_t Width, uint32_t Height)
	{
		RenderCommand::SetViewport(0, 0, Width, Height);
	}

	void Renderer3D::BeginScene(const Ref<SceneCamera>& Camera, const glm::mat4& Transform, const DirLight* DirLights, uint32_t LightCnt)
	{
		s_SceneData->ViewProjectionMatrix = Camera->GetProjection() * glm::inverse(Transform);
		s_SceneData->LightCnt = LightCnt;
		s_SceneData->ViewPos = glm::vec3(Transform[3][0], Transform[3][1], Transform[3][2]);
		memcpy(s_SceneData->DirLights, DirLights, sizeof(Renderer3D::DirLight) * LightCnt);
	}

	void Renderer3D::BeginScene(EditorCamera& Camera, const DirLight* DirLights, uint32_t LightCnt)
	{
		s_SceneData->ViewProjectionMatrix = Camera.GetViewProjection();
		s_SceneData->LightCnt = LightCnt;
		s_SceneData->ViewPos = Camera.GetPosition();
		memcpy(s_SceneData->DirLights, DirLights, sizeof(Renderer3D::DirLight) * LightCnt);
	}

	void Renderer3D::EndScene()
	{
		s_SceneData->LightCnt = 0;
	}

	void Renderer3D::DrawMesh(Ref<VertexArray> VA, Ref<Material> Mat, const glm::mat4& Transform)
	{
		ME_PROFILE_SCOPE("Renderer3D::DrawMesh");

		Mat->Bind();

		Ref<Shader> Shader = Mat->GetShader();
		Mat->GetShader()->SetInt("u_nl", s_SceneData->LightCnt);
		for (int i = 0; i < s_SceneData->LightCnt; i++)
		{
			s_SceneData->DirLights[i].SetUniform(i, Mat->GetShader());
		}

		glm::mat4 ViewProjectionMatrix = s_SceneData->ViewProjectionMatrix;
		Shader->SetMat4("u_ViewProjection", ViewProjectionMatrix);
		Shader->SetMat4("u_TransformMatrix", Transform);
		glm::mat4 InverseMatrix = glm::inverse(Transform);
		Shader->SetMat4("u_InverseMatrix", InverseMatrix);
		Shader->SetFloat3("ViewPos", s_SceneData->ViewPos);
		

		VA->Bind();

		if (VA->GetIndexBuffer())
		{
			RenderCommand::DrawIndexed(VA);
		}
		else
		{
			RenderCommand::DrawArrays(VA);
		}
	}

	void Renderer3D::DrawMesh(Ref<VertexArray> VA, std::vector<std::string> Mats, const glm::mat4& Transform)
	{
		if (Mats.size() == 0)
		{
			DrawMesh(VA, s_SceneData->DefaultMat, Transform);
		}
		else
		{
			for (std::string Mat : Mats)
			{
				DrawMesh(VA, MaterialLibrary::Get()->GetMaterial(Mat), Transform);
			}
		}
	}
}