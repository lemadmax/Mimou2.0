#include "mepch.h"
#include "GameObject.h"

namespace Mimou
{
	GameObject::GameObject()
	{

	}

	GameObject::GameObject(const Transform& InTransform)
		: m_Transform(InTransform)
	{

	}

	void GameObject::OnUpdate(Timestep Ts)
	{
		for (Ref<ComponentBase> Component : Components)
		{
			Component->OnUpdate(Ts);
		}
	}

	void GameObject::AddChild(GameObject* Child)
	{
		Children.push_back(Child);
		Child->SetParent(this);
	}

	Transform GameObject::GetWorldTransform()
	{
		if (m_Parent == nullptr)
		{
			return m_Transform;
		}
		Transform WorldTransform;
		WorldTransform.SetTransformMatrix(m_Parent->m_Transform.GetTransformMatrix() * m_Transform.GetTransformMatrix());
		return WorldTransform;
	}

	void GameObject::AddComponent(const Ref<ComponentBase>& Component)
	{
		Components.push_back(Component);
		Component->SetOwner(this);
	}

	Ref<ComponentBase> GameObject::GetComponentByName(const std::string& Name)
	{
		for (auto Comp : Components)
		{
			if (Comp->GetName() == Name)
			{
				return Comp;
			}
		}
		ME_ENGINE_ERROR("Failed to get component {} from game object", Name);
		return nullptr;
	}

}