#include "mepch.h"
#include "MimouSerializer.h"

#include <yaml-cpp/yaml.h>

namespace Mimou
{
    void SerializeMEObject_yaml(YAML::Emitter& Out, MEObject* Obj)
    {
        Out << YAML::BeginMap;
        Out << YAML::Key << "Scene" << YAML::Value << "Scene->GetName()";

        Out << YAML::Key << "GameObjects";
        Out << YAML::BeginSeq;

        Out << YAML::EndSeq;

        Out << YAML::EndMap;
    }

	void MimouSerializer::SaveMEObject(MEObject* Obj, const std::string& AssetName)
	{
        YAML::Emitter Out;

        SerializeMEObject_yaml(Out, Obj);

        std::ofstream fout(AssetName);
        fout << Out.c_str();
	}

}

