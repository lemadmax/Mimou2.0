#include "mepch.h"
#include "MESerializer.h"
#include "MEObject.h"

#include "yaml-cpp/yaml.h"

namespace Mimou
{

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
			case MEPropType::STRING:
			{
				std::string Value = Property->GetString(Obj);
				Out << YAML::Value << Value;
				break;
			}
			case MEPropType::INT:
			{
				int Value = Property->GetInt(Obj);
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

	MEObject* MESerializer::LoadObject(const std::string& ClassName, const std::string& AssetPath)
	{
		return nullptr;
	}

	void MESerializer::SaveObject(MEObject* Obj, const std::string& AssetPath)
	{
		YAML::Emitter Out;
		SerializeObject_yaml(Out, Obj);

		std::ofstream fout(AssetPath);
		fout << Out.c_str();
	}
}