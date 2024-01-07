#pragma once
#include "Mimou/Core.h"
#include "Mimou/Timestep.h"
#include "Mimou/ECS/Component/BasicComponents.h"
#include "Mimou/ECS/Scene.h"
#include "Mimou/ECS/MEObject.h"

#include "entt/entt.hpp"

namespace Mimou
{
	class GameObject : public MEObject
	{
		DECLARE_ME_CLASS(GameObject)
	public:
		GameObject() = default;
		GameObject(const Ref<Scene>& OwnedScene, const std::string& Name = "Game Object", Ref<GameObject> Parent = nullptr);
		virtual ~GameObject();

		virtual void OnCreate();
		virtual void OnUpdate(Timestep Ts);
		virtual bool OnDestroy();

		void AttachToScene(Scene* Target);

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

		Scene* GetOwnedScene() const { return m_Scene; }

		MEObject* AddComponentGeneric(MEObject* CompObj);

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if (HasComponent<T>())
			{
				ME_ENGINE_WARN("Failed to add component {}: Already exists", T::StaticClass());
				return GetComponent<T>();
			}
			T& Component = m_Scene->m_Registry.emplace<T>(m_EntityID, std::forward<Args>(args)...);
			Components.insert((MEObject*)&Component);
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
		bool HasComponent()
		{
			return m_Scene->m_Registry.all_of<T>(m_EntityID);
		}

		template<typename T>
		bool RemoveComponent()
		{
			T* Comp = m_Scene->m_Registry.try_get<T>(m_EntityID);
			if (Comp)
			{
				Components.erase((MEObject*)Comp);
			}
			return m_Scene->m_Registry.remove<T>(m_EntityID);
		}

	private:
		ME_PROPERTY(m_EntityID, MEPropType::INT)
		entt::entity m_EntityID;

		// unsafe, should only be used for serialization
		ME_PROPERTY(Components, MEPropType::COMP_SET)
		std::set<MEObject*> Components;

		Scene* m_Scene = nullptr;

		Ref<GameObject> m_Parent = nullptr;
		//std::vector<Ref<GameObject>> Children;
		std::set<Ref<GameObject>> Children;
	};
}