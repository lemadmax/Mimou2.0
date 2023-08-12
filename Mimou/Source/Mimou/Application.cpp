#include "mepch.h"

#include "Application.h"

namespace Mimou
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		ME_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (true)
		{
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(EventBase& Event)
	{
		EventDispatcher Dispatcher(Event);
		Dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResized));
		Dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
		Dispatcher.Dispatch<WindowFocusEvent>(BIND_EVENT_FN(Application::OnWindowFocused));
		Dispatcher.Dispatch<WindowMoveEvent>(BIND_EVENT_FN(Application::OnWindowMoved));


	}
	bool Application::OnWindowResized(WindowResizeEvent& Event)
	{
		//ME_LOG("Application::OnWindowResized: {}", Event.ToString());
		return false;
	}
	bool Application::OnWindowClosed(WindowCloseEvent& Event)
	{
		//ME_LOG("Application::OnWindowClosed: {}", Event.ToString());
		return false;
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