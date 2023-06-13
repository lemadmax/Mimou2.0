#include <Mimou.h>

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

Mimou::Application* Mimou::CreateApplication()
{
	return new Sandbox();
}