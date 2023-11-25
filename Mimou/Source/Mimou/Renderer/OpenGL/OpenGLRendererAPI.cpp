#include "mepch.h"

#include "OpenGLRendererAPI.h"

#include "glad/glad.h"

namespace Mimou
{
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height)
	{
		glViewport(X, Y, Width, Height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& Color)
	{
		glClearColor(Color.r, Color.g, Color.b, Color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::EnableDepthTest()
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
	}

	void OpenGLRendererAPI::ClearDepth()
	{
		glClearDepth(1);
	}

	void OpenGLRendererAPI::EnableBlend()
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& VertexArray)
	{
		glDrawElements(GL_TRIANGLES, VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLRendererAPI::DrawArrays(const Ref<VertexArray>& VertexArray)
	{
		uint32_t VertexCnt = VertexArray->GetVertexBuffers()[0]->GetSize() / sizeof(float);
		uint32_t VertexSize = VertexArray->GetVertexBuffers()[0]->GetLayout().GetStride() / sizeof(float);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, VertexCnt / VertexSize);
	}
}