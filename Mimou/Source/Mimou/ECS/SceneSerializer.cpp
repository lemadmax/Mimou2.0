#include "mepch.h"

#include "SceneSerializer.h"

#include "Component/BasicComponents.h"

#include "entt/entt.hpp"

namespace Mimou
{
    SceneSerializer* SceneSerializer::s_Instance = nullptr;

    void SceneSerializer::SerializeScene(const Ref<Scene>& Scene, const std::string& AssetPath)
    {
        YAML::Emitter Out;
        Out << Scene->GetName();

        for (auto Pair : Scene->GameObjects)
        {
            SerializeGameObjects(Out, Pair.second);
        }

        std::ofstream fout(AssetPath);
        fout << Out.c_str();
    }

    Ref<Scene> SceneSerializer::DeserializeScene(const std::string& AssetPath)
    {
        return Ref<Scene>();
    }

    void SceneSerializer::SerializeGameObjects(YAML::Emitter& Out, const Ref<GameObject>& GB)
    {
        entt::entity EntityID = GB->GetEntityID();
        Out << YAML::BeginMap;
        Out << YAML::Key << "GameObject" << YAML::Value << std::to_string((uint32_t)EntityID);

        TagComponent* TagComp = GB->TryGetComponent<TagComponent>();
        if (TagComp)
        {
            Out << YAML::Key << "TagComponent";
            Out << YAML::BeginMap;

            Out << YAML::Key << "Tag" << YAML::Value << TagComp->Tag;

            Out << YAML::EndMap;
        }

        Out << YAML::EndMap;
    }
}