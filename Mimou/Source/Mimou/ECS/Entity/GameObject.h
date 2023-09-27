#pragma once
#include "Mimou/Transform/Transform.h"

namespace Mimou
{
	class GameObject
	{
	public:
		GameObject();
		//virtual ~GameObject();

		GameObject(const Transform& Transform);

		inline void SetTransform(const Transform& Transform) { m_Transform = Transform; }
		inline Transform GetTransform() const { return m_Transform; }

	public:
		Transform m_Transform;
	};
}