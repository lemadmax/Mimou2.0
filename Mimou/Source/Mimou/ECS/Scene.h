#pragma once
#include "Mimou/Core.h"
#include "Mimou/Timestep.h"
#include "Mimou/Renderer/Camera/EditorCamera.h"
#include "MEObject.h"

#include "entt/entt.hpp"


namespace Mimou
{
	class GameObject;
	class Panel;
	class SceneHierarchyPanel;

	class SceneSerializer;

	class Scene : public MEObject
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
		ME_PROPERTY(m_SceneName, MEPropType::STRING)
		std::string m_SceneName = "Default Scene";

		ME_PROPERTY(GameObjects, MEPropType::OBJ_MAP)
		std::map<uint32_t, Ref<GameObject>> GameObjects;
		
	private:
		entt::registry m_Registry;


		friend class GameObject;
		friend class Panel;
		friend class SceneHierarchyPanel;

		friend class SceneSerializer;
	};
}