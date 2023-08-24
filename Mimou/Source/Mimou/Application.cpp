#include "mepch.h"

#include "Application.h"
#include "Input.h"

#include "GLFW/glfw3.h"

namespace Mimou
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		ME_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		bIsRunning = true;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		m_Window->SetVSync(1);

		m_ImGUILayer = new ImGUILayer();
		PushOverlay(m_ImGUILayer);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (bIsRunning)
		{
			float Time = (float)glfwGetTime();
			Timestep Timestep = Time - m_LastFrameTime;
			m_LastFrameTime = Time;

			for (Layer* Layer : m_LayerStack)
			{
				Layer->OnUpdate(Timestep);
			}

			m_ImGUILayer->Begin();
			for (Layer* Layer : m_LayerStack)
			{
				Layer->OnImGUIRender();
			}
			m_ImGUILayer->End();
			m_Window->OnUpdate();

			//if (Input::IsKeyPressed(ME_KEY_A))
			//{
			//	ME_LOG("KeyPressed: A");
			//}
			//if (Input::IsMouseButtonPressed(0))
			//{
			//	ME_LOG("MousePressed: Left");
			//}
			//if (Input::IsMouseButtonPressed(1))
			//{
			//	ME_LOG("MousePressed: Right");
			//	std::pair<float, float> MousePosition = Input::GetMousePosition();
			//	ME_LOG("MousePosition: ({},{})", MousePosition.first, MousePosition.second);
			//}
		}
	}

	void Application::PushLayer(Layer* Layer)
	{
		m_LayerStack.PushLayer(Layer);
		Layer->OnAttach();
	}

	void Application::PushOverlay(Layer* Overlay)
	{
		m_LayerStack.PushOverlay(Overlay);
		Overlay->OnAttach();
	}

	void Application::OnEvent(EventBase& Event)
	{
		EventDispatcher Dispatcher(Event);
		Dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResized));
		Dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
		Dispatcher.Dispatch<WindowFocusEvent>(BIND_EVENT_FN(Application::OnWindowFocused));
		Dispatcher.Dispatch<WindowMoveEvent>(BIND_EVENT_FN(Application::OnWindowMoved));

		for (auto It = m_LayerStack.end(); It != m_LayerStack.begin();)
		{
			(*--It)->OnEvent(Event);
			if (Event.bHandled) break;
		}
	}
	bool Application::OnWindowResized(WindowResizeEvent& Event)
	{
		//ME_LOG("Application::OnWindowResized: {}", Event.ToString());
		return false;
	}
	bool Application::OnWindowClosed(WindowCloseEvent& Event)
	{
		//ME_LOG("Application::OnWindowClosed: {}", Event.ToString());
		bIsRunning = false;
		return true;
	}
	bool Application::OnWindowFocused(WindowFocusEvent& Event)
	{
		//ME_LOG("Application::OnWindowFocused: {}", Event.ToString());
		return false;
	}
	bool Application::OnWindowMoved(WindowMoveEvent& Event)
	{
		//ME_LOG("Application::OnWindowMoved: {}", Event.ToString());
		return false;
	}
}