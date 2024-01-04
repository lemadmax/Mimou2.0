#pragma once
#include "MimouObject.h"

namespace Mimou
{
	class MEObject;

	class MimouSerializer
	{
	public:
		static Ref<MEObject> LoadMEObject(const std::string& ClassType, const std::string& AssetName);
		static void SaveMEObject(Ref<MEObject> Obj, const std::string& AssetName);
	};
}