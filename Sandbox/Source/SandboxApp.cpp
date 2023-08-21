#include <Mimou.h>

#include "glm/vec3.hpp"

class ExampleLayer : public Mimou::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	~ExampleLayer()
	{

	}

	virtual void OnAttach() override
	{

	}

	virtual void OnDetach() override
	{

	}

	virtual void OnUpdate(Mimou::Timestep Ts) override
	{
	}

	virtual void OnImGUIRender() override
	{

	}

	virtual void OnEvent(Mimou::EventBase& Event) override
	{

	}
};

class Sandbox : public Mimou::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

Mimou::Application* Mimou::CreateApplication()
{
	return new Sandbox();
}