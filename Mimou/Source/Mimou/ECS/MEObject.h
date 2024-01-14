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

		std::string GetName() const { return m_ObjectName; }

	private:
		std::string m_ObjectName;

		friend class MEObjectManager;
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

		std::string RegisterObject(const Ref<MEObject>& Object);

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

	template<typename ClassName>
	Ref<ClassName> NewObject()
	{
		MEClass* Class = MEClassManager::GetInstance()->GetClass(ClassName::StaticClass());
		Ref<ClassName> Out = Class->Instantiate();
		MEObjectManager::GetInstance()->RegisterObject(Out);
		return Out;
	}

	extern Ref<MEObject> NewObjectByClass(MEClass* Class);
}