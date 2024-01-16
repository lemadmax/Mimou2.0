#include "mepch.h"
#include "MESerializer.h"
#include "MEObject.h"
#include "Entity/GameObject.h"

#include "yaml-cpp/yaml.h"

#include "SceneSerializer.cpp"

namespace YAML
{
	template<>
	struct convert<std::vector<std::string>>
	{
		static Node encode(const std::vector<std::string>& rhs)
		{
			Node node;
			for (int i = 0; i < rhs.size(); i++)
			{
				node.push_back(rhs[i]);
			}
			return node;
		}

		static bool decode(const Node& node, std::vector<std::string>& rhs)
		{
			if (!node.IsSequence())
			{
				return false;
			}

			for (int i = 0; i < node.size(); i++)
			{
				rhs.push_back(node[i].as<std::string>());
			}
			return true;
		}
	};
}

namespace Mimou
{
	//YAML::Emitter& operator << (YAML::Emitter& Out, const glm::vec3& v)
	//{
	//	Out << YAML::Flow;
	//	Out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
	//	return Out;
	//}
	extern YAML::Emitter& operator << (YAML::Emitter& Out, const glm::vec3& v);
	extern YAML::Emitter& operator << (YAML::Emitter& Out, const std::vector<std::string>& v);

	void SerializeObject_yaml(YAML::Emitter& Out, MEObject* Obj)
	{
		MEClass* Class = Obj->GetClass();
		std::string ClassName = Class->GetName();
		Out << YAML::BeginMap;

		Out << YAML::Key << "ClassName" << YAML::Value << ClassName;
		std::map<std::string, MEProperty> Properties = Class->GetProperties();
		for (auto Pair : Properties)
		{
			Out << YAML::Key << Pair.first;
			MEProperty Property = Pair.second;
			switch (Property.m_PropType)
			{
			case MEPropType::BOOL:
			{
				bool Value = Class->GetValue<bool>(Obj, Property.m_PropName);
				Out << YAML::Value << Value;
				break;
			}
			case MEPropType::STRING:
			{
				std::string Value = Class->GetValue<std::string>(Obj, Property.m_PropName);
				Out << YAML::Value << Value;
				break;
			}
			case MEPropType::STRING_VEC:
			{
				std::vector<std::string> Value = Class->GetValue<std::vector<std::string>>(Obj, Property.m_PropName);
				Out << YAML::Value << Value;
				break;
			}
			case MEPropType::INT:
			{
				int Value = Class->GetValue<int>(Obj, Property.m_PropName);
				Out << YAML::Value << Value;
				break;
			}
			case MEPropType::FLOAT:
			{
				float Value = Class->GetValue<float>(Obj, Property.m_PropName);
				Out << YAML::Value << YAML::Flow << Value;
				break;
			}
			case MEPropType::OBJ_REF:
			{
				Ref<MEObject> Value = Class->GetValue<Ref<MEObject>>(Obj, Property.m_PropName);
				Out << YAML::Value;
				SerializeObject_yaml(Out, Value.get());
				break;
			}
			case MEPropType::GAME_OBJ_REF_MAP:
			{
				std::map<uint32_t, Ref<GameObject>> Value = Class->GetValue<std::map<uint32_t, Ref<GameObject>>>(Obj, Property.m_PropName);
				Out << YAML::Value << YAML::BeginMap;
				for (auto Pair : Value)
				{
					Out << YAML::Key << Pair.first << YAML::Value;
					SerializeObject_yaml(Out, Pair.second.get());
				}
				Out << YAML::EndMap;
				break;
			}
			case MEPropType::COMP_SET:
			{
				std::set<MEObject*> Value = Class->GetValue<std::set<MEObject*>>(Obj, Property.m_PropName);
				Out << YAML::Value << YAML::BeginSeq;
				for (MEObject* Comp : Value)
				{
					SerializeObject_yaml(Out, Comp);
				}
				Out << YAML::EndSeq;
				break;
			}
			case MEPropType::VEC3:
			{
				glm::vec3 Value = Class->GetValue<glm::vec3>(Obj, Property.m_PropName);
				Out << YAML::Value << Value;
				break;
			}
			default:
			{

				break;
			}
			}
		}

		Out << YAML::EndMap;
	}
	MEObject* DeserializeObjectPtr_yaml(YAML::Node& Data);
	Ref<MEObject> DeserializeObject_yaml(YAML::Node& Data);

	template<typename T>
	Ref<T> DeserializeObjectRef_yaml(YAML::Node& Data)
	{
		Ref<MEObject> ObjRef = DeserializeObject_yaml(Data);
		//return CreateRef<T>(static_cast<T*>(ObjPtr));
		return std::static_pointer_cast<T>(ObjRef);
	}

	void DeserializeObject_yaml_inner(YAML::Node& Data, MEObject* Out)
	{
		MEClass* Class = Out->GetClass();
		std::map<std::string, MEProperty> Properties = Class->GetProperties();
		for (auto Pair : Properties)
		{
			std::string PropName = Pair.first;
			MEProperty Property = Pair.second;
			switch (Property.m_PropType)
			{
			case MEPropType::BOOL:
			{
				bool Value = Data[PropName];
				Class->SetValue<bool>(Out, Property.m_PropName, Value);
				break;
			}
			case MEPropType::STRING:
			{
				std::string Value = Data[PropName].as<std::string>();
				Class->SetValue<std::string>(Out, Property.m_PropName, Value);
				break;
			}
			case MEPropType::STRING_VEC:
			{
				std::vector<std::string> Value = Data[PropName].as<std::vector<std::string>>();
				Class->SetValue<std::vector<std::string>>(Out, Property.m_PropName, Value);
				break;
			}
			case MEPropType::INT:
			{
				int Value = Data[PropName].as<int>();
				Class->SetValue<int>(Out, Property.m_PropName, Value);
				break;
			}
			case MEPropType::FLOAT:
			{
				float Value = Data[PropName].as<float>();
				Class->SetValue<float>(Out, Property.m_PropName, Value);
				break;
			}
			case MEPropType::OBJ_REF:
			{
				YAML::Node ObjNode = Data[PropName];
				Ref<MEObject> ObjRef = DeserializeObject_yaml(ObjNode);
				Class->SetValue<Ref<MEObject>>(Out, Property.m_PropName, ObjRef);
				break;
			}
			case MEPropType::GAME_OBJ_REF_MAP:
			{
				// Handle Scene and GameObject specially
				YAML::Node MapNode = Data[PropName];
				for (YAML::const_iterator it = MapNode.begin(); it != MapNode.end(); ++it)
				{
					YAML::Node ObjNode = it->second;
					Ref<GameObject> ObjRef = DeserializeObjectRef_yaml<GameObject>(ObjNode);
					if (Out->IsA(Scene::StaticClass()))
					{
						Scene::AddGameObject(static_cast<Scene*>(Out), ObjRef);
					}
				}
				break;
			}
			case MEPropType::COMP_SET:
			{
				YAML::Node SetNode = Data[PropName];
				std::set<MEObject*> Value;
				for (int i = 0; i < SetNode.size(); i++)
				{
					YAML::Node ObjNode = SetNode[i];
					MEObject* ObjPtr = DeserializeObjectPtr_yaml(ObjNode);
					Value.insert(ObjPtr);
				}
				Class->SetValue<std::set<MEObject*>>(Out, Property.m_PropName, Value);
				break;
			}
			case MEPropType::VEC3:
			{
				glm::vec3 Value = Data[PropName].as<glm::vec3>();
				Class->SetValue<glm::vec3>(Out, Property.m_PropName, Value);
				break;
			}
			default:
			{

				break;
			}
			}
		}
	}

	MEObject* DeserializeObjectPtr_yaml(YAML::Node& Data)
	{
		std::string ClassName = Data["ClassName"].as<std::string>();
		MEClass* Class = MEClassManager::GetInstance()->GetClass(ClassName);
		MEObject* Out = Class->InstantiatePtr();
		DeserializeObject_yaml_inner(Data, Out);
		return Out;
	}

	Ref<MEObject> DeserializeObject_yaml(YAML::Node& Data)
	{
		std::string ClassName = Data["ClassName"].as<std::string>();
		MEClass* Class = MEClassManager::GetInstance()->GetClass(ClassName);
		Ref<MEObject> Out = NewObjectByClass(Class);
		DeserializeObject_yaml_inner(Data, Out.get());
		return Out;
	}

	Ref<MEObject> MESerializer::LoadObject(const std::string& ClassName, const std::string& AssetPath)
	{
		YAML::Node RawData = YAML::LoadFile(AssetPath);
		if (RawData["ClassName"].as<std::string>() != ClassName)
		{
			return nullptr;
		}
		Ref<MEObject> Out = DeserializeObject_yaml(RawData);
		return Out;
	}

	void MESerializer::SaveObject(MEObject* Obj, const std::string& AssetPath)
	{
		YAML::Emitter Out;
		SerializeObject_yaml(Out, Obj);

		std::ofstream fout(AssetPath);
		fout << Out.c_str();
	}
}