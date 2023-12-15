#pragma once

#ifdef ME_PLATFORM_WINDOWS

extern Mimou::Application* Mimou::CreateApplication();

int main(int argc, char** argv)
{
	Mimou::Logging::Init();

	ME_PROFILE_BEGIN_SESSION("Startup", "MimouProfile-Startup.json");
	ME_ENGINE_LOG("Engine Start");
	auto App = Mimou::CreateApplication();
	ME_PROFILE_END_SESSION();

	ME_PROFILE_BEGIN_SESSION("Runtime", "MimouProfile-Runtime.json");
	App->Run();
	ME_PROFILE_END_SESSION();

	ME_PROFILE_BEGIN_SESSION("Shutdown", "MimouProfile-Shutdown.json");
	delete App;
	ME_PROFILE_END_SESSION();

	Mimou::Logging::Uninit();
	return 0;
}

#endif