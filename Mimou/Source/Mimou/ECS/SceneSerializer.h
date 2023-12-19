#pragma once
#include "Scene.h"
#include "Entity/GameObject.h"
#include <yaml-cpp/yaml.h>

namespace Mimou
{
	class SceneSerializer
	{
	private:
		SceneSerializer() = default;

	public:
		static SceneSerializer* Get()
		{
			if (!s_Instance)
			{
				s_Instance = new SceneSerializer();
			}
			return s_Instance;
		}
		
		void SerializeScene(const Ref<Scene>& Scene, const std::string& AssetPath);

		Ref<Scene> DeserializeScene(const std::string& AssetPath);

	private:

		void SerializeGameObjects(YAML::Emitter& Out, const Ref<GameObject>& GB);

	private:
		static SceneSerializer* s_Instance;
	};
}