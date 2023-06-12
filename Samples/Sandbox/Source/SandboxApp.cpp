#include <Mimou.h>

#include <EntryPoint.h>

class Sandbox : public Mimou::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}

};

Mimou::Application* CreateApplication()
{
	return new Sandbox();
}