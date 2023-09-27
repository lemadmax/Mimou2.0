#include "mepch.h"
#include "GameObject.h"

namespace Mimou
{
	GameObject::GameObject()
	{
	}

	//GameObject::~GameObject()
	//{
	//}

	GameObject::GameObject(const Transform& Transform)
		: m_Transform(Transform)
	{
	}
}