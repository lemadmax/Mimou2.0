#pragma once
#include "RenderCommand.h"
#include "Camera/SceneCamera.h"
#include "Camera/EditorCamera.h"
#include "Mimou/Renderer/Material/Material.h"
#include "Mimou/Renderer/Shader.h"

#define MAX_LIGHT_NUM 256

namespace Mimou
{
	class Renderer3D
	{
	public:

		struct DirLight
		{
			glm::vec3 Color = { 1.0f, 1.0f, 1.0f };
			glm::vec3 Direction = { 1.0f, 1.0f, 1.0f };
			float Intensity = 1.0f;

			void SetUniform(uint32_t i, Ref<Shader> Shader)
			{
				Shader->SetFloat3("u_Lights[" + std::to_string(i) + "].LightColor", Color);
				Shader->SetFloat3("u_Lights[" + std::to_string(i) + "].LightDir", Direction);
				Shader->SetFloat("u_Lights[" + std::to_string(i) + "].Intensity", Intensity); 
			}
		};

	public:
		static void Init();

		static void Shutdown();

		static void OnWindowResized(uint32_t Width, uint32_t Height);

		static void BeginScene(const Ref<SceneCamera>& Camera, const glm::mat4& Transform, const DirLight* DirLights, uint32_t LightCnt);

		static void BeginScene(EditorCamera& Camera, const DirLight* DirLights, uint32_t LightCnt);

		static void EndScene();

		static void DrawMesh(Ref<VertexArray> VA, Ref<Material> Mat, const glm::mat4& Transform);

		static void DrawMesh(Ref<VertexArray> VA, std::vector<std::string> Mats, const glm::mat4& Transform);

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
			DirLight DirLights[MAX_LIGHT_NUM];
			uint32_t LightCnt;
			Ref<Material> DefaultMat;

			glm::vec3 ViewPos;
		};

		static SceneData* s_SceneData;
	};
}