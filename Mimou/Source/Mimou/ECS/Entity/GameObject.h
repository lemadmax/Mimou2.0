#pragma once
#include "Mimou/Transform/Transform.h"
#include "Mimou/Timestep.h"
#include "Mimou/ECS/Component/ComponentBase.h"

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

		virtual void Update(Timestep Ts);

	public:
		Transform m_Transform;

	private:
		Ref<GameObject> Parent = nullptr;
		std::vector<Ref<GameObject>> Children;

		std::vector<Ref<ComponentBase>> Components;
	};
}