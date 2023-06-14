#include <Mimou.h>

class Sandbox : public Mimou::Application
{
public:
	Sandbox()
	{
		std::string Name = "Sandbox";
		int Num = 26;
		ME_LOG("Sandbox Created {}", Name);
		ME_WARN("WARNING TEST {} {}", Name, Num);
		ME_ERROR("ERROR TEST {} {}", Num, Name);
		ME_TRACE("TRACE_TEST");
	}
	~Sandbox()
	{

	}
};

Mimou::Application* Mimou::CreateApplication()
{
	return new Sandbox();
}