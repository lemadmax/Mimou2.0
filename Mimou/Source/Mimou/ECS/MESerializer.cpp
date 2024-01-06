#include "mepch.h"
#include "MESerializer.h"
#include "MEObject.h"
#include "Entity/GameObject.h"

#include "yaml-cpp/yaml.h"

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
		std::map<std::string, MEProperty*> Properties = Class->GetProperties();
		for (auto Pair : Properties)
		{
			Out << YAML::Key << Pair.first;
			MEProperty* Property = Pair.second;
			switch (Property->m_PropType)
			{
			case MEPropType::BOOL:
			{
				bool Value = Property->GetValue<bool>(Obj);
				Out << YAML::Value << Value;
				break;
			}
			case MEPropType::STRING:
			{
				std::string Value = Property->GetValue<std::string>(Obj);
				Out << YAML::Value << Value;
				break;
			}
			case MEPropType::STRING_VEC:
			{
				std::vector<std::string> Value = Property->GetValue<std::vector<std::string>>(Obj);
				Out << YAML::Value << Value;
				break;
			}
			case MEPropType::INT:
			{
				int Value = Property->GetValue<int>(Obj);
				Out << YAML::Value << Value;
				break;
			}
			case MEPropType::FLOAT:
			{
				float Value = Property->GetValue<float>(Obj);
				Out << YAML::Value << YAML::Flow << Value;
				break;
			}
			case MEPropType::OBJ_REF:
			{
				Ref<MEObject> Value = Property->GetValue<Ref<MEObject>>(Obj);
				Out << YAML::Value;
				SerializeObject_yaml(Out, Value.get());
				break;
			}
			case MEPropType::OBJ_MAP:
			{
				std::map<uint32_t, Ref<GameObject>> Value = Property->GetValue<std::map<uint32_t, Ref<GameObject>>>(Obj);
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
				std::set<MEObject*> Value = Property->GetValue<std::set<MEObject*>>(Obj);
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
				glm::vec3 Value = Property->GetValue<glm::vec3>(Obj);
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

	MEObject* DeserializeObject_yaml(const std::string& ClassName, const std::string& AssetPath)
	{
		
		return nullptr;
	}

	MEObject* MESerializer::LoadObject(const std::string& ClassName, const std::string& AssetPath)
	{
		MEObject* Out = DeserializeObject_yaml(ClassName, AssetPath);
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