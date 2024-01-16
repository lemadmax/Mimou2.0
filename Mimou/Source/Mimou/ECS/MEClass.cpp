#include "mepch.h"
#include "MEClass.h"
#include "MEObject.h"
#include "Entity/GameObject.h"

namespace Mimou
{
	MEClass::MEClass(const std::string& ClassName, InstantiateFn InstFn, InstantiateFnPtr InstFnPtr) : m_ClassName(ClassName), m_InstFn(InstFn), m_InstFnPtr(InstFnPtr)
	{
		MEClassManager::GetInstance()->RegisterMEClass(this);
	}

	void MEClass::RegisterProperty(const std::string& PropName, MEProperty Prop)
	{

		m_Properties.insert({ PropName, Prop });
	}

	void MEClassManager::RegisterMEClass(MEClass* Class)
	{
		ClassMap.insert({ Class->GetName(), Class });
	}

	MEClass* MEClassManager::GetClass(const std::string& ClassName)
	{
		return ClassMap[ClassName];
	}


	MEPropertyCreator::MEPropertyCreator(MEObject* ObjPtr, const std::string& PropName, void* PropPtr, MEPropType PropType)
	{
		MEClass* Class = ObjPtr->GetClass();
		if (!Class->HasProperty(PropName))
		{
			Class->RegisterProperty(PropName, { (uint32_t)((char*)PropPtr - (char*)ObjPtr), PropName, PropType });
		}
	}
}