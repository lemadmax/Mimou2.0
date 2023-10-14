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

		virtual void OnUpdate(Timestep Ts);

		void AddChild(GameObject* Child);

		Transform GetWorldTransform();
		inline void SetParent(GameObject* Parent) { m_Parent = Parent; }

		void AddComponent(const Ref<ComponentBase>& Component);
		Ref<ComponentBase> GetComponentByName(const std::string& Name);

	public:
		Transform m_Transform;

	private:
		GameObject* m_Parent = nullptr;
		std::vector<GameObject*> Children;

		std::vector<Ref<ComponentBase>> Components;
	};
}