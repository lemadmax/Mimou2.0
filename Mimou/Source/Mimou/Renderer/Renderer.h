#pragma once

#include "RenderCommand.h"

#include "VertexArray.h"
#include "Shader.h"
#include "Mimou/Renderer/Camera/PerspectiveCamera.h"

#include <glm/glm.hpp>

namespace Mimou
{
	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t Width, uint32_t Height);

		static void BeginScene(PerspectiveCamera Camera);
		static void EndScene();

		static void Submit(const Reference<VertexArray>& VertexArray, const Reference<Shader>& Shader, const glm::mat4& Transform = glm::mat4(1.0f));

		static void SubmitArrays(const Reference<VertexArray>& VertexArray, const Reference<Shader>& Shader, const glm::mat4& Transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}