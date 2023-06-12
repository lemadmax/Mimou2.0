#pragma once
#include <Application.h>

#ifdef ME_PLATFORM_WINDOWS

extern Mimou::Application* Mimou::CreateApplication();

int main(int argc, int** argv)
{
	//printf("Mimou Engine start");
	auto App = Mimou::CreateApplication();
	App->Run();
	delete App;
}

#endif