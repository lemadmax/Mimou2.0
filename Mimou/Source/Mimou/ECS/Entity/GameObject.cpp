#include "mepch.h"
#include "GameObject.h"
#include "Mimou/ECS/Component/BasicComponents.h"

namespace Mimou
{
	IMPLEMENT_ME_CLASS(GameObject)
	IMPLEMENT_ME_CLASS(TagComponent)
	IMPLEMENT_ME_CLASS(TransformComponent)
	IMPLEMENT_ME_CLASS(StaticMeshComponent)
	IMPLEMENT_ME_CLASS(CameraComponent)
	IMPLEMENT_ME_CLASS(LightComponent)

	GameObject::GameObject(const Ref<Scene>& OwnedScene, const std::string& Name, Ref<GameObject> Parent)
		: m_Scene(OwnedScene.get()), m_Parent(Parent)
	{
		m_EntityID = OwnedScene->m_Registry.create();
		TransformComponent& Transform = AddComponent<TransformComponent>();
		TagComponent& Tag = AddComponent<TagComponent>(Name);
	}

	GameObject::~GameObject()
	{
		OnDestroy();
	}

	void GameObject::OnCreate()
	{

	}

	void GameObject::OnUpdate(Timestep Ts)
	{

	}

	bool GameObject::OnDestroy()
	{
		if (!(uint32_t)m_EntityID) return false;
		if (!m_Scene->m_Registry.valid(m_EntityID)) return false;
		m_Scene->m_Registry.destroy(m_EntityID);
		m_EntityID = (entt::entity)0;
		return true;
	}

	void GameObject::AttachToScene(Scene* Target)
	{
		m_Scene = Target;
		m_EntityID = m_Scene->m_Registry.create();
		std::set<MEObject*> OldComponents = Components;
		Components.clear();
		for (auto Comp : OldComponents)
		{
			AddComponentGeneric(Comp);
			// Dangerous
			delete Comp;
		}
	}

	void GameObject::AddChild(Ref<GameObject> Child)
	{
		Children.insert(Child);
	}

	void GameObject::RemoveChild(Ref<GameObject> Child)
	{
		if (Children.contains(Child))
		{
			Children.erase(Child);
		}
	}

	glm::mat4 GameObject::GetWorldTransform()
	{
		TransformComponent* TransformComp = TryGetComponent<TransformComponent>();
		ME_ASSERT(TransformComp != nullptr, "Game object has no transform component");

		glm::mat4 Transform = TransformComp->GetTransform();
		if (m_Parent)
		{
			return m_Parent->GetWorldTransform() * Transform;
		}
		return Transform;
	}

	glm::vec3 GameObject::GetWorldTranslation()
	{
		return glm::vec3();
	}

	glm::vec3 GameObject::GetWorldRotation()
	{

		return glm::vec3();
	}

	glm::vec3 GameObject::GetWorldScale()
	{

		return glm::vec3();
	}

	MEObject* GameObject::AddComponentGeneric(MEObject* CompObj)
	{
		if (CompObj->IsA(TagComponent::StaticClass()))
		{
			TagComponent& NewComp = AddComponent<TagComponent>(*(TagComponent*)CompObj);
			return &NewComp;
		}
		else if (CompObj->IsA(TransformComponent::StaticClass()))
		{
			TransformComponent& NewComp = AddComponent<TransformComponent>(*(TransformComponent*)CompObj);
			return &NewComp;
		}
		return nullptr;
	}

}