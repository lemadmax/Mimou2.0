#pragma once
#include "RenderCommand.h"
#include "Camera/SceneCamera.h"
#include "Camera/EditorCamera.h"
#include "Mimou/Renderer/Material/Material.h"
#include "Mimou/Renderer/Shader.h"

namespace Mimou
{
	class Renderer3D
	{
	public:

		struct DirectionalLight
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

		static void BeginScene(SceneCamera& Camera, const glm::mat4& Transform, std::vector<DirectionalLight> DirLights);

		static void BeginScene(EditorCamera& Camera, std::vector<DirectionalLight> DirLights);

		static void EndScene();

		static void DrawMesh(Ref<VertexArray> VA, Ref<Material> Mat, const glm::mat4& Transform);

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
			std::vector<DirectionalLight> DirLights;
		};

		static SceneData* s_SceneData;
	};
}