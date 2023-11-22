#pragma once
#include "Mimou/Core.h"
#include "Mimou/Timestep.h"
#include "Mimou/ECS/Entity/GameObject.h"

#include "entt/entt.hpp"

namespace Mimou
{
	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void OnUpdate(Timestep Ts);

	public:
		Ref<GameObject> CreateGameObject(Ref<GameObject> Parent = nullptr);
		bool DestroyGameObject(Ref<GameObject> GameObject);

	private:
		entt::registry m_Registry;

		std::map<entt::entity, Ref<GameObject>> GameObjects;

		friend class GameObject;
	};
}