#pragma once
#include "Mimou/Core.h"
#include "Mimou/Timestep.h"
#include "Mimou/Renderer/Camera/EditorCamera.h"
#include "MimouObject.h"

#include "entt/entt.hpp"


namespace Mimou
{
	class GameObject;
	class Panel;
	class SceneHierarchyPanel;

	class SceneSerializer;

	ME_CLASS(Scene)
	class Scene
	{
		DECLARE_ME_CLASS(Scene)
	public:
		Scene();
		Scene(const std::string& SceneName);
		virtual ~Scene();

		virtual void OnUpdate(Timestep Ts);
		virtual void OnUpdateEditor(Timestep Ts, EditorCamera& EditorCamera);

		inline const std::string& GetName() const { return m_SceneName; }

		Ref<GameObject> GetPrimiaryCamera();

	public:
		static Ref<GameObject> CreateGameObject(const Ref<Scene>& Scene, const std::string& Name = "Game Object", Ref<GameObject> Parent = nullptr);
		static bool DestroyGameObject(const Ref<Scene>& Scene, Ref<GameObject> GameObject);
		static bool DestroyAllGameObjects(const Ref<Scene>& Scene);

		void RenderScene();

	public:
		std::string m_SceneName;

		std::map<entt::entity, Ref<GameObject>> GameObjects;
		
	private:
		entt::registry m_Registry;


		friend class GameObject;
		friend class Panel;
		friend class SceneHierarchyPanel;

		friend class SceneSerializer;
	};
}