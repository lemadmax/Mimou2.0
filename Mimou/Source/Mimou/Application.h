#pragma once
#include "Core.h"
#include "Window/Window.h"
#include "Event/AppEvent.h"
#include "Mimou/LayerStack.h"
#include "Mimou/ImGUI/ImGUILayer.h"

namespace Mimou
{

	class ME_API Application
	{
	public:
		Application();
		Application(const std::string& AppName);
		virtual ~Application();

		void Run();

		void Close();

	public:
		inline static Application* GetInstance() { return s_Instance; }

		inline Window& GetWindow() { return *m_Window; }

		void PushLayer(Layer* Layer);

		void PushOverlay(Layer* Overlay);

		ImGUILayer* GetImGuiLayer() const { return m_ImGUILayer; }

	private:

		void OnEvent(EventBase& Event);

	private:
		bool OnWindowResized(WindowResizeEvent& Event);

		bool OnWindowClosed(WindowCloseEvent& Event);

		bool OnWindowFocused(WindowFocusEvent& Event);

		bool OnWindowMoved(WindowMoveEvent& Event);

	private:
		std::string m_AppName;
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;

		ImGUILayer* m_ImGUILayer;

		bool bIsRunning = false;

		float m_LastFrameTime = 0.f;

	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();

}