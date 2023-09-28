#pragma once
#include "Mimou/Transform/Transform.h"

namespace Mimou
{
	class GameObject
	{
	public:
		GameObject();
		//virtual ~GameObject();

		GameObject(const Transform& InTransform);

		inline void SetTransform(const Transform& InTransform) { m_Transform = InTransform; }
		inline const Transform& GetTransform() const { return m_Transform; }

	public:
		Transform m_Transform;
	};
}