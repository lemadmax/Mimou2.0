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
	};

	template<typename ClassType>
	Ref<ClassType> LoadObject(const std::string& AssetPath)
	{

	}

	template<typename ClassType>
	void SaveObject(ClassType* Obj, const std::string& AssetPath)
	{
		MESerializer::SaveObject(Obj, AssetPath);
	}
}