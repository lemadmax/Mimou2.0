#pragma once
#include "MEClass.h"
#include "MESerializer.h"

namespace Mimou
{
	class MEObject
	{
	public:
		MEObject();

		static std::string StaticClass() { return "MEObject"; }

		virtual MEClass* GetClass() { return MEClassManager::GetInstance()->GetClass("MEObject"); };
		virtual bool IsA(const std::string& Class) { return Class == "MEObject"; };

	private:
		std::string m_ObjectName;
	};

	class MEObjectManager
	{
	private:
		MEObjectManager();
		~MEObjectManager();

	public:
		static MEObjectManager* GetInstance()
		{
			static MEObjectManager s_Instance;
			return &s_Instance;
		}

	private:
		std::map<std::string, Ref<MEObject>> MEObjects;
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