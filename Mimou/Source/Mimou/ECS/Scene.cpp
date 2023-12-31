#include "mepch.h"
#include "Scene.h"
#include "Mimou/ECS/Entity/GameObject.h"
#include "Mimou/Renderer/Renderer3D.h"
#include "Mimou/Mesh/StaticMesh.h"

namespace Mimou
{
	IMPLEMENT_ME_CLASS(Scene)

	Scene::Scene()
	{
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

	Ref<GameObject> Scene::GetPrimiaryCamera()
	{
		Ref<GameObject> GB = nullptr;
		{
			auto View = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto Entity : View)
			{
				auto Camera = m_Registry.get<CameraComponent>(Entity);
				if (Camera.IsPrimary)
				{
					GB = GameObjects[(uint32_t)Entity];
				}
			}
		}
		return GB;
	}

	Ref<GameObject> Scene::CreateGameObject(const Ref<Scene>& Scene, const std::string& Name, Ref<GameObject> Parent)
	{
		Ref<GameObject> Out = CreateRef<GameObject>(Scene, Name, Parent);
		if (Parent)
		{
			Parent->AddChild(Out);
		}
		Scene->GameObjects.insert({ (uint32_t)Out->GetEntityID(), Out });
		Out->OnCreate();
		return Out;
	}
	bool Scene::DestroyGameObject(const Ref<Scene>& Scene, Ref<GameObject> GameObject)
	{
		if (GameObject->GetParent())
		{
			GameObject->GetParent()->RemoveChild(GameObject);
		}
		Scene->GameObjects.erase((uint32_t)GameObject->GetEntityID());
		return GameObject->OnDestroy();
	}

	bool Scene::DestroyAllGameObjects(const Ref<Scene>& Scene)
	{
		bool res = true;
		for (auto Pair : Scene->GameObjects)
		{
			res &= Pair.second->OnDestroy();
		}
		Scene->GameObjects.clear();
		return res;
	}

	bool Scene::AddGameObject(Scene* Owner, Ref<GameObject> GB)
	{
		GB->AttachToScene(Owner);
		Owner->GameObjects.insert({ (uint32_t)GB->GetEntityID(), GB });
		GB->OnCreate();
		return true;
	}

	void Scene::RenderScene()
	{
		{
			auto View = m_Registry.view<TransformComponent, StaticMeshComponent>();
			for (auto Entity : View)
			{
				auto [TransformComp, StaticMesh] = View.get<TransformComponent, StaticMeshComponent>(Entity);
				Ref<GameObject> GB = GameObjects[(uint32_t)Entity];
				glm::mat4 Transform = GB->GetWorldTransform();

				Ref<VertexArray> VA = StaticMeshLibrary::GetAsset(StaticMesh.AssetName);
				Renderer3D::DrawMesh(VA, StaticMesh.MaterialSlots, Transform);
			}
		}
	}
}