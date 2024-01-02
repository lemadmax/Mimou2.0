#include "mepch.h"
#include "MimouSerializer.h"

#include <yaml-cpp/yaml.h>

namespace Mimou
{
    void SerializeMEObject_yaml(YAML::Emitter& Out, Ref<MEObject> Obj)
    {

		ClassDescriptor* ClassDesc = Obj->GetClass();
		if (!ClassDesc)
		{
			return;
		}

        Out << YAML::BeginMap;
		Out << YAML::Key << "ClassType" << YAML::Value << ClassDesc->GetClassType();
		for (auto [PropName, PropType] : ClassDesc->PropertySignitures)
		{
			switch (PropType)
			{
			case MimouValueType::STRING:
			{
				Out << YAML::Key << PropName;
				std::string DataValue;
				if (ClassDesc->SetPropertyValue<std::string>(Obj.get(), PropName, DataValue))
				{
					Out << YAML::Value << DataValue;
				}
				else
				{
					ME_ENGINE_ERROR("Failed to serialize property({}) {} of class {}", TypeStr[(INT32)PropType], PropName, ClassDesc->GetClassType());
					Out << YAML::Value << "None";
				}
				break;
			}
			default:
			{
				ME_ENGINE_WARN("Data type not supported");
				break;
			}
			}
		}

        Out << YAML::EndMap;
    }

	Ref<MEObject> MimouSerializer::LoadMEObject(const std::string& ClassType, const std::string& AssetName)
    {
		YAML::Node RawData = YAML::LoadFile(AssetName);
		if (!RawData)
		{
			ME_ENGINE_ERROR("Failed to load asset: {}", AssetName);
			return nullptr;
		}

		std::string AssetType = RawData["ClassType"].as<std::string>();
		if (AssetType != ClassType)
		{
			ME_ENGINE_ERROR("Failed to load asset(Wrong type): {}, Asset type is {}, but trying to load a {}", AssetName, AssetType, ClassType);
			return nullptr;
		}

		MEObject* OutPtr = MEObjectManager::GetInstance()->CreateObject(AssetType);
		if (!OutPtr)
		{
			ME_ENGINE_ERROR("Failed to create object {}", AssetType);
			return nullptr;
		}

		Ref<MEObject> Out(OutPtr);
		ClassDescriptor* ClassDesc = Out->GetClass();
		for (auto [PropName, PropType] : ClassDesc->PropertySignitures)
		{
			switch (PropType)
			{
			case MimouValueType::STRING:
			{
				std::string Data = RawData[PropName].as<std::string>();
				ClassDesc->SetPropertyValue<std::string>(Out.get(), PropName, Data);
				break;
			}
			default:
			{
				ME_ENGINE_WARN("Data type not supported");
				break;
			}
			}
		}
		return Out;
    }

    void MimouSerializer::SaveMEObject(Ref<MEObject> Obj, const std::string& AssetName)
	{
        YAML::Emitter Out;

        SerializeMEObject_yaml(Out, Obj);

        std::ofstream fout(AssetName);
        fout << Out.c_str();
	}

}

