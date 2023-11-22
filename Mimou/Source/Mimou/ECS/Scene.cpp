#include "mepch.h"
#include "Scene.h"

namespace Mimou
{

	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	void Scene::OnUpdate(Timestep Ts)
	{
		for (auto GameObject : GameObjects)
		{
			GameObject.second->OnUpdate(Ts);
		}
	}

	Ref<GameObject> Scene::CreateGameObject(Ref<GameObject> Parent)
	{
		Ref<GameObject> Out = CreateRef<GameObject>(this, Parent);
		if (Parent)
		{
			Parent->AddChild(Out);
		}
		return Out;
	}
	bool Scene::DestroyGameObject(Ref<GameObject> GameObject)
	{
		return GameObject->OnDestroy();
	}
}