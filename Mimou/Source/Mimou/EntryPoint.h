#pragma once

#ifdef ME_PLATFORM_WINDOWS

extern Mimou::Application* Mimou::CreateApplication();

int main(int argc, char** argv)
{
	auto App = Mimou::CreateApplication();
	App->Run();
	delete App;
	return 0;
}

#endif