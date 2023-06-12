#pragma once
#include <Core.h>

namespace Mimou
{

	class ME_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}