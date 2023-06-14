#pragma once

#ifdef ME_PLATFORM_WINDOWS

extern Mimou::Application* Mimou::CreateApplication();

int main(int argc, char** argv)
{
	Mimou::Logging::Init();
	Mimou::Logging::GetEngineLogger()->info("Engine Start");
	Mimou::Logging::GetClientLogger()->error("Client Test");
	auto App = Mimou::CreateApplication();
	App->Run();
	delete App;
	return 0;
}

#endif