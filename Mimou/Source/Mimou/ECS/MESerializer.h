#pragma once

namespace Mimou
{
	class MEObject;

	class MESerializer
	{
	public:
		static Ref<MEObject> LoadObject(const std::string& ClassName, const std::string& AssetPath);
		static void SaveObject(MEObject* Obj, const std::string& AssetPath);
	};
}