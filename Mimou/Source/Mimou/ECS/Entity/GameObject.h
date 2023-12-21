#pragma once
#include "Mimou/Core.h"
#include "Mimou/Timestep.h"
#include "Mimou/ECS/Component/BasicComponents.h"
#include "Mimou/ECS/Scene.h"

#include "entt/entt.hpp"

namespace Mimou
{
	class GameObject
	{
	public:
		GameObject() = delete;
		GameObject(Scene* OwnedScene, const std::string& Name = "Game Object", Ref<GameObject> Parent = nullptr);
		virtual ~GameObject();

		virtual void OnCreate();
		virtual void OnUpdate(Timestep Ts);
		virtual bool OnDestroy();

		void AddChild(Ref<GameObject> Child);
		void RemoveChild(Ref<GameObject> Child);
		
		inline bool HasChildren() const { return !Children.empty(); }

		inline Ref<GameObject> GetParent() const { return m_Parent; }
		inline void SetParent(Ref<GameObject> Parent) { m_Parent = Parent; }
		inline const entt::entity& GetEntityID() const { return m_EntityID; }
		inline std::set<Ref<GameObject>> GetChildren() const { return Children; }

		glm::mat4 GetWorldTransform();
		glm::vec3 GetWorldTranslation();
		glm::vec3 GetWorldRotation();
		glm::vec3 GetWorldScale();

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			T& Component = m_Scene->m_Registry.emplace<T>(m_EntityID, std::forward<Args>(args)...);
			return Component;
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Scene->m_Registry.get<T>(m_EntityID);
		}

		template<typename T>
		T* TryGetComponent()
		{
			return m_Scene->m_Registry.try_get<T>(m_EntityID);
		}

		template<typename T>
		bool RemoveComponent()
		{
			return m_Scene->m_Registry.remove<T>(m_EntityID);
		}

	private:
		entt::entity m_EntityID;

		Scene* m_Scene = nullptr;

		Ref<GameObject> m_Parent = nullptr;
		//std::vector<Ref<GameObject>> Children;
		std::set<Ref<GameObject>> Children;
	};
}