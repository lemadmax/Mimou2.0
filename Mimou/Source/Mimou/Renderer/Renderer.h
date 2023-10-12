#pragma once

#include "RenderCommand.h"

#include "VertexArray.h"
#include "Shader.h"
#include "Mimou/Renderer/Camera/PerspectiveCamera.h"
#include "Mimou/Renderer/Material/Material.h"
#include "Mimou/Renderer/Lighting/Light.h"

#include <glm/glm.hpp>

namespace Mimou
{
	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t Width, uint32_t Height);

		static void BeginScene(PerspectiveCamera& Camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& VertexArray, const Ref<Shader>& Shader, const glm::mat4& Transform = glm::mat4(1.0f));

		static void SubmitArrays(const Ref<VertexArray>& VertexArray, const Ref<Shader>& Shader, const glm::mat4& Transform = glm::mat4(1.0f));

		static void SubmitArrays(const Ref<VertexArray>& VertexArray, const Ref<Material>& Material, const Ref<Light>& Light);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}