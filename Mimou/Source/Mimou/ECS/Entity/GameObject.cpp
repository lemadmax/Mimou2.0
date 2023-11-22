#include "mepch.h"
#include "GameObject.h"

namespace Mimou
{

	GameObject::GameObject(Scene* OwnedScene, Ref<GameObject> Parent)
		: m_Scene(OwnedScene), m_Parent(Parent)
	{

	}

	GameObject::~GameObject()
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
		Children.push_back(Child);
	}

}