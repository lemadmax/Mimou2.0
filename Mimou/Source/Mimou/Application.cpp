#include "mepch.h"

#include "Application.h"

namespace Mimou
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		ME_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (true)
		{

		}
	}

	void Application::OnEvent(EventBase& Event)
	{
	}
}