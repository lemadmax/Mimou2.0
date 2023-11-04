#pragma once

#include "RendererAPI.h"

namespace Mimou
{
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetClearColor(const glm::vec4& Color)
		{
			s_RendererAPI->SetClearColor(Color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void EnableDepthTest()
		{
			s_RendererAPI->EnableDepthTest();
		}

		inline static void ClearDepth()
		{
			s_RendererAPI->ClearDepth();
		}

		inline static void EnableBlend()
		{
			s_RendererAPI->EnableBlend();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& VertexArray)
		{
			s_RendererAPI->DrawIndexed(VertexArray);
		}

		inline static void DrawArrays(const Ref<VertexArray>& VertexArray)
		{
			s_RendererAPI->DrawArrays(VertexArray);
		}

		inline static void SetViewport(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height)
		{
			s_RendererAPI->SetViewport(X, Y, Width, Height);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}