#pragma once
#include "Mimou/Renderer/RendererAPI.h"

namespace Mimou
{
	class ME_API OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetViewport(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height) override;

		virtual void SetClearColor(const glm::vec4& Color) override;
		virtual void Clear() override;
		virtual void EnableDepthTest() override;
		virtual void ClearDepth() override;
		virtual void EnableBlend() override;

		virtual void DrawIndexed(const Ref<VertexArray>& VertexArray) override;
		virtual void DrawArrays(const Ref<VertexArray>& VertexArray) override;

	};
}