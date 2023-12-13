#include "mepch.h"
#include "Scene.h"
#include "Mimou/ECS/Entity/GameObject.h"
#include "Mimou/Renderer/Renderer3D.h"

namespace Mimou
{

	Scene::Scene()
	{
		Scene("Default Scene");
	}

	Scene::Scene(const std::string& SceneName)
		: m_SceneName(SceneName)
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

		Ref<SceneCamera> PrimaryCamera;
		glm::mat4 CameraTransform;
		{
			auto View = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto Entity : View)
			{
				auto [Transform, Camera] = m_Registry.get<TransformComponent, CameraComponent>(Entity);
				if (Camera.IsPrimary)
				{
					PrimaryCamera = Camera.Camera;
					CameraTransform = Transform.GetTransform();
				}
			}
		}

		Renderer3D::DirLight DirLight[MAX_LIGHT_NUM];
		uint32_t LightCnt = 0;
		{
			auto View = m_Registry.view<TransformComponent, LightComponent>();
			for (auto Entity : View)
			{
				auto [Transform, Light] = m_Registry.get<TransformComponent, LightComponent>(Entity);
				if (Light.IsOn)
				{
					ME_ENGINE_ASSERT(LightCnt + 1 <= MAX_LIGHT_NUM, "Light number exceeds the limits");
					if (Light.IsDirectional)
					{
						DirLight[LightCnt++] = { Light.Color, Transform.GetDirection(), Light.Intensity };
					}
				}
			}
		}

		if (PrimaryCamera)
		{
			Renderer3D::BeginScene(PrimaryCamera, CameraTransform, DirLight, LightCnt);
		}
		else
		{
			Renderer3D::BeginScene(EditorCamera, DirLight, LightCnt);
		}

		RenderScene();

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
		Out->OnCreate();
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

	void Scene::RenderScene()
	{
		{
			auto View = m_Registry.view<TransformComponent, StaticMeshComponent>();
			for (auto Entity : View)
			{
				auto [TransformComp, StaticMesh] = View.get<TransformComponent, StaticMeshComponent>(Entity);
				Ref<GameObject> GB = GameObjects[Entity];
				glm::mat4 Transform = GB->GetWorldTransform();

				Renderer3D::DrawMesh(StaticMesh.VertexArray, StaticMesh.Mat, Transform);
			}
		}
	}
}