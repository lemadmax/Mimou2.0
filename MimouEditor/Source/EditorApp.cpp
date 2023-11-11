#include <Mimou.h>
#include "Mimou/EntryPoint.h"

#include "Layer/EditorLayer.h"

class EditorApp : public Mimou::Application
{
public:
	EditorApp(const std::string& AppName)
		: Mimou::Application(AppName)
	{
		PushLayer(new EditorLayer());
	}
	~EditorApp()
	{

	}
};

Mimou::Application* Mimou::CreateApplication()
{
	return new EditorApp("Mimou Editor");
}