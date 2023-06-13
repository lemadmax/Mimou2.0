#pragma once

#ifdef ME_PLATFORM_WINDOWS

//extern Mimou::Application* Mimou::CreateApplication();
extern int test_main();

int main(int argc, char* argv[])
{
	/*auto App = Mimou::CreateApplication();
	App->Run();
	delete App;*/
	test_main();
	return 0;
}

#endif