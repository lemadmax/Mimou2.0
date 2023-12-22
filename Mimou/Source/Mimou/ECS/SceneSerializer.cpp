#include "mepch.h"

#include "SceneSerializer.h"

#include "Component/BasicComponents.h"

#include "entt/entt.hpp"

namespace YAML
{
    template<>
    struct convert<glm::vec3>
    {
        static Node encode(const glm::vec3& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            return node;
        }

        static bool decode(const Node& node, glm::vec3& rhs)
        {
            if (!node.IsSequence() || node.size() != 3)
            {
                return false;
            }

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            return true;
        }
    };
}

namespace Mimou
{
    SceneSerializer* SceneSerializer::s_Instance = nullptr;

    YAML::Emitter& operator << (YAML::Emitter& Out, const glm::vec3& v)
    {
        Out << YAML::Flow;
        Out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
        return Out;
    }

    void SceneSerializer::SerializeScene(const Ref<Scene>& Scene, const std::string& AssetPath)
    {
        YAML::Emitter Out;
        Out << YAML::BeginMap;
        Out << YAML::Key << "Scene" << YAML::Value << Scene->GetName();

        Out << YAML::Key << "GameObjects";
        Out << YAML::BeginSeq;
        for (auto Pair : Scene->GameObjects)
        {
            SerializeGameObjects(Out, Pair.second);
        }
        Out << YAML::EndSeq;

        Out << YAML::EndMap;

        std::ofstream fout(AssetPath);
        fout << Out.c_str();
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

    Ref<GameObject> SceneSerializer::DeserializeGameObject(const Ref<Scene>& Scene, YAML::Node& Node)
    {
        YAML::Node TagCompNode = Node["TagComponent"];
        std::string Tag = TagCompNode["Tag"].as<std::string>();
        Ref<GameObject> GB = Scene::CreateGameObject(Scene, Tag, nullptr);

        if (!GB) return nullptr;

        {
            YAML::Node TransformCompNode = Node["TransformComponent"];
            if (TransformCompNode)
            {
                glm::vec3 Translation = TransformCompNode["Translation"].as<glm::vec3>();
                glm::vec3 Rotation = TransformCompNode["Rotation"].as<glm::vec3>();
                glm::vec3 Scale = TransformCompNode["Scale"].as<glm::vec3>();
                TransformComponent* TransformComp = GB->TryGetComponent<TransformComponent>();
                if (!TransformComp)
                {
                    GB->AddComponent<TransformComponent>(Translation, Rotation, Scale);
                }
                else
                {
                    TransformComp->Translation = Translation;
                    TransformComp->Rotation = Rotation;
                    TransformComp->Scale = Scale;
                }
            }
            else
            {
                GB->RemoveComponent<TransformComponent>();
            }
            
        }

        return GB;
    }
}