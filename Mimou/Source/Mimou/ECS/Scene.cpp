#include "mepch.h"
#include "Scene.h"
#include "Mimou/ECS/Entity/GameObject.h"
#include "Mimou/Renderer/Renderer3D.h"

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

	void Scene::OnUpdateEditor(Timestep Ts, EditorCamera& EditorCamera)
	{
		for (auto GameObject : GameObjects)
		{
			GameObject.second->OnUpdate(Ts);
		}

		Renderer3D::BeginScene(EditorCamera, std::vector<Renderer3D::DirectionalLight>());

		{
			auto View = m_Registry.view<TransformComponent, StaticMeshComponent>();
			for (auto Entity : View)
			{
				auto [Transform, StaticMesh] = View.get<TransformComponent, StaticMeshComponent>(Entity);

				Renderer3D::DrawMesh(StaticMesh.VertexArray, StaticMesh.Mat, Transform.GetTransform());
			}
		}

		Renderer3D::EndScene();
	}

	Ref<GameObject> Scene::CreateGameObject(Ref<GameObject> Parent)
	{
		Ref<GameObject> Out = CreateRef<GameObject>(this, Parent);
		if (Parent)
		{
			Parent->AddChild(Out);
		}
		GameObjects.insert({ Out->GetEntityID(), Out });
		return Out;
	}
	bool Scene::DestroyGameObject(Ref<GameObject> GameObject)
	{
		if (GameObject->GetParent())
		{
			GameObject->GetParent()->RemoveChild(GameObject);
		}
		GameObjects.erase(GameObject->GetEntityID());
		return GameObject->OnDestroy();
	}
}