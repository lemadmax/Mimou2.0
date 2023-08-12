#pragma once
#include "Core.h"
#include "Window/Window.h"
#include "Event/AppEvent.h"

namespace Mimou
{

	class ME_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(EventBase& Event);

	private:
		bool OnWindowResized(WindowResizeEvent& Event);

		bool OnWindowClosed(WindowCloseEvent& Event);

		bool OnWindowFocused(WindowFocusEvent& Event);

		bool OnWindowMoved(WindowMoveEvent& Event);

	private:
		std::unique_ptr<Window> m_Window;

	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();

}