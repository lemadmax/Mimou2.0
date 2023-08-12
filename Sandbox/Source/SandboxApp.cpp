#include <Mimou.h>

#include "glm/vec3.hpp"

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

		glm::vec3 Vector1(1.0, 2.0, 3.0);
		glm::vec3 Vector2(3.0, 2.0, 1.0);
		glm::vec3 res = Vector1 + Vector2;
		ME_LOG("(1.0, 2.0, 3.0) + (3.0, 2.0, 1.0) = ({}, {}, {})", res.x, res.y, res.z);
	}
	~Sandbox()
	{

	}
};

Mimou::Application* Mimou::CreateApplication()
{
	return new Sandbox();
}