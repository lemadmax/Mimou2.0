#pragma once
#include "RenderCommand.h"

namespace Mimou
{
	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();
		static void BeginScene();
		static void EndScene();
	};
}