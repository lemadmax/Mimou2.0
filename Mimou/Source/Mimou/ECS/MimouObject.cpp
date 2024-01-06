#include "mepch.h"
//#include "MimouObject.h"
//#include "MimouSerializer.h"
//
//namespace Mimou
//{
//
//	const std::string TypeStr[256] =
//	{
//		"None",
//		"String",
//		"Map",
//		"ME_OBJECT"
//	};
//
//	MEObjectManager* MEObjectManager::s_Instance = nullptr;
//
//	void MEObjectManager::RegisterMEClass(const std::string& ClassName, ClassDescriptor* CD)
//	{
//		ClassLibs.emplace(ClassName, CD);
//	}
//
//	MEObject* MEObjectManager::CreateObject(const std::string& ClassName)
//	{
//		if (ClassLibs.contains(ClassName))
//		{
//			ClassDescriptor* CD = ClassLibs[ClassName];
//			return CD->CreateNewObject();
//		}
//		return nullptr;
//	}
//
//}