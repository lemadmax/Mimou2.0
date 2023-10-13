#include "mepch.h"
#include "StaticMeshSystem.h"

namespace Mimou
{
	StaticMeshSystem* StaticMeshSystem::s_Instance = nullptr;
	StaticMeshSystem* StaticMeshSystem::GetInstance()
	{
		if (!s_Instance)
		{
			s_Instance = new StaticMeshSystem();
		}
		return s_Instance;
	}

	void StaticMeshSystem::React(Ref<GameObject> Entity)
	{

	}

	StaticMeshSystem::StaticMeshSystem()
		: SystemBase("Static Mesh System")
	{

	}
}