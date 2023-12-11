#pragma once
#include "Mimou/Core.h"
#include "Mimou/Timestep.h"
#include "Mimou/Renderer/Camera/EditorCamera.h"

#include "entt/entt.hpp"


namespace Mimou
{
	class GameObject;
	class Panel;
	class SceneHierarchyPanel;

	class Scene
	{
	public:
		Scene();
		Scene(const std::string& SceneName);
		virtual ~Scene();

		virtual void OnUpdate(Timestep Ts);
		virtual void OnUpdateEditor(Timestep Ts, EditorCamera& EditorCamera);

		inline const std::string& GetName() const { return m_SceneName; }

	public:
		Ref<GameObject> CreateGameObject(Ref<GameObject> Parent = nullptr);
		bool DestroyGameObject(Ref<GameObject> GameObject);

	private:
		std::string m_SceneName;
		entt::registry m_Registry;

		std::map<entt::entity, Ref<GameObject>> GameObjects;

		friend class GameObject;
		friend class Panel;
		friend class SceneHierarchyPanel;
	};
}