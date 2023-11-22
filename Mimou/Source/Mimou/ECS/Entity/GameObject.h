#pragma once
#include "Mimou/Transform/Transform.h"
#include "Mimou/Timestep.h"
#include "Mimou/ECS/Component/BasicComponents.h"
#include "Mimou/ECS/Scene.h"

#include "entt/entt.hpp"

namespace Mimou
{
	class GameObject
	{
	public:
		GameObject() = default;
		GameObject(Scene* OwnedScene, Ref<GameObject> Parent = nullptr);
		virtual ~GameObject();

		virtual void OnUpdate(Timestep Ts);
		virtual bool OnDestroy();

		void AddChild(Ref<GameObject> Child);

		inline void SetParent(Ref<GameObject> Parent) { m_Parent = Parent; }
		inline const entt::entity& GetEntityID() const { return m_EntityID; }

		//template<typename T, typename... Args>
		//T& AddComponent(Args&&... args)
		//{
		//	T& Component = m_Scene->m_Registry.emplace<T>(m_EntityID, std::forward<Args>(args)...);
		//	return Component;
		//}

		//template<typename T>
		//T& GetComponent()
		//{
		//	return m_Scene->m_Registry.get<T>(m_EntityID);
		//}

	private:
		entt::entity m_EntityID;

		Scene* m_Scene = nullptr;

		Ref<GameObject> m_Parent = nullptr;
		std::vector<Ref<GameObject>> Children;
	};
}