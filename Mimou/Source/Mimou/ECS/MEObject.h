#pragma once
#include "MEClass.h"
#include "MESerializer.h"

namespace Mimou
{
	class MEObject
	{
	public:
		MEObject() = default;

		virtual MEClass* GetClass() = 0;
		virtual bool IsA(const std::string& Class) = 0;
	};

	template<typename ClassType>
	Ref<ClassType> LoadObject(const std::string& AssetPath)
	{
		Ref<MEObject> Obj = MESerializer::LoadObject(ClassType::StaticClass(), AssetPath);
		if (Obj)
		{
			Ref<ClassType> Out = std::static_pointer_cast<ClassType>(Obj);
			return Out;
		}
		return nullptr;
	}

	template<typename ClassType>
	void SaveObject(ClassType* Obj, const std::string& AssetPath)
	{
		MESerializer::SaveObject(Obj, AssetPath);
	}
}