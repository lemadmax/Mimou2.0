#include "mepch.h"
#include "GameObject.h"
#include "Mimou/ECS/Component/BasicComponents.h"

namespace Mimou
{

	GameObject::GameObject(Scene* OwnedScene, Ref<GameObject> Parent)
		: m_Scene(OwnedScene), m_Parent(Parent)
	{
		m_EntityID = OwnedScene->m_Registry.create();
		TransformComponent& Transform = OwnedScene->m_Registry.emplace<TransformComponent>(m_EntityID);
		TagComponent& Tag = OwnedScene->m_Registry.emplace<TagComponent>(m_EntityID);
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

}