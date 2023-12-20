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
        Out << YAML::BeginMap;
        Out << YAML::Key << "Scene" << YAML::Value << Scene->GetName();

        Out << YAML::Key << "GameObjects";
        for (auto Pair : Scene->GameObjects)
        {
            Out << YAML::BeginSeq;
            SerializeGameObjects(Out, Pair.second);
            Out << YAML::EndSeq;
        }

        Out << YAML::EndMap;

        std::ofstream fout(AssetPath);
        fout << Out.c_str();
    }

    Ref<Scene> SceneSerializer::DeserializeScene(const std::string& AssetPath)
    {
        YAML::Node RawData = YAML::LoadFile(AssetPath);

        std::string SceneName = RawData["Scene"].as<std::string>();
        Ref<Scene> Out = CreateRef<Scene>(SceneName);

        YAML::Node RawGBs = RawData["GameObjects"];
        for (size_t i = 0; i < RawGBs.size(); i++)
        {
            YAML::Node RawGB = RawGBs[i];
            Ref<GameObject> GB = DeserializeGameObject(Out, RawGB);
        }

        return Out;
    }

    YAML::Emitter& operator << (YAML::Emitter& Out, const glm::vec3& v)
    {
        Out << YAML::Flow;
        Out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
        return Out;
    }

    void SceneSerializer::SerializeGameObjects(YAML::Emitter& Out, const Ref<GameObject>& GB)
    {
        entt::entity EntityID = GB->GetEntityID();
        Out << YAML::BeginMap;
        Out << YAML::Key << "EntityID" << YAML::Value << std::to_string((uint32_t)EntityID);

        TagComponent* TagComp = GB->TryGetComponent<TagComponent>();
        if (TagComp)
        {
            Out << YAML::Key << "TagComponent";
            Out << YAML::BeginMap;

            Out << YAML::Key << "Tag" << YAML::Value << TagComp->Tag;

            Out << YAML::EndMap;
        }

        TransformComponent* TransformComp = GB->TryGetComponent<TransformComponent>();
        if (TransformComp)
        {
            Out << YAML::Key << "TransformComponent";
            Out << YAML::BeginMap;

            Out << YAML::Key << "Translation";
            Out << YAML::Value << TransformComp->Translation;

            Out << YAML::Key << "Rotation";
            Out << YAML::Value << TransformComp->Rotation;

            Out << YAML::Key << "Scale";
            Out << YAML::Value << TransformComp->Scale;

            Out << YAML::EndMap;
        }

        StaticMeshComponent* SMComp = GB->TryGetComponent<StaticMeshComponent>();
        if (SMComp)
        {
            Out << YAML::Key << "StaticMeshComponent";
            Out << YAML::BeginMap;
            
            Out << YAML::Key << "AssetName";
            Out << YAML::Value << SMComp->AssetName;

            std::vector<std::string> MaterialPaths;
            for (Ref<Material> Mat : SMComp->MaterialSlots)
            {
                MaterialPaths.emplace_back(Mat->GetName());
            }
            Out << YAML::Key << "MaterialSlots";
            Out << YAML::Value << MaterialPaths;

            Out << YAML::EndMap;
        }

        CameraComponent* CameraComp = GB->TryGetComponent<CameraComponent>();
        if (CameraComp)
        {
            Out << YAML::Key << "CameraComponent";
            Out << YAML::BeginMap;

            Ref<SceneCamera> Camera = CameraComp->Camera;
            Out << YAML::Key << "FOV";
            Out << YAML::Value << YAML::Flow << Camera->GetFOV();

            Out << YAML::Key << "Aspect";
            Out << YAML::Value << YAML::Flow << Camera->GetAspect();

            Out << YAML::Key << "zNear";
            Out << YAML::Value << YAML::Flow << Camera->GetZNear();

            Out << YAML::Key << "zFar";
            Out << YAML::Value << YAML::Flow << Camera->GetZFar();

            Out << YAML::Key << "IsPrimary";
            Out << YAML::Value << YAML::Flow << CameraComp->IsPrimary;

            Out << YAML::EndMap;
        }

        LightComponent* LightComp = GB->TryGetComponent<LightComponent>();
        if (LightComp)
        {
            Out << YAML::Key << "LightComponent";
            Out << YAML::BeginMap;

            Out << YAML::Key << "Intensity";
            Out << YAML::Value << YAML::Flow << LightComp->Intensity;

            Out << YAML::Key << "IsDirectional";
            Out << YAML::Value << YAML::Flow << LightComp->IsDirectional;

            Out << YAML::Key << "IsOn";
            Out << YAML::Value << YAML::Flow << LightComp->IsOn;

            Out << YAML::EndMap;
        }

        Out << YAML::EndMap;
    }

    Ref<GameObject> SceneSerializer::DeserializeGameObject(const Ref<Scene>& Scene, YAML::Node& Node)
    {
        
        return Ref<GameObject>();
    }
}