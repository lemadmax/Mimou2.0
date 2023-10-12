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

	void GameObject::Update(Timestep Ts)
	{
		for (Ref<ComponentBase> Component : Components)
		{

		}
	}

}