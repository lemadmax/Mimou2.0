#include "mepch.h"
#include "MEClass.h"
#include "MEObject.h"
#include "Entity/GameObject.h"

namespace Mimou
{
	MEClass::MEClass(const std::string& ClassName, InstantiateFn InstFn) : m_ClassName(ClassName), m_InstFn(InstFn)
	{
		MEClassManager::GetInstance()->RegisterMEClass(this);
	}

	void MEClass::RegisterProperty(const std::string& PropName, MEProperty* Prop)
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


	MEProperty::MEProperty(MEObject* ObjPtr, const std::string& PropName, void* PropPtr, MEPropType PropType)
		: m_PropName(PropName), m_PropType(PropType)
	{
		MEClass* Class = ObjPtr->GetClass();
		m_Offset = (char*)PropPtr - (char*)ObjPtr;
		Class->RegisterProperty(PropName, this);
	}

	std::string MEProperty::GetString(const void* Obj)
	{
		if (m_PropType != MEPropType::STRING)
			return std::string();
		char* Dest = (char*)Obj + m_Offset;
		return *(std::string*)Dest;
	}

	int MEProperty::GetInt(const void* Obj)
	{
		if (m_PropType != MEPropType::INT)
		{
			return 0;
		}
		char* Dest = (char*)Obj + m_Offset;
		return *(int*)Dest;
	}

	std::map<uint32_t, Ref<GameObject>> MEProperty::GetObjMap(const void* Obj)
	{
		if (m_PropType != MEPropType::OBJ_MAP)
		{
			return std::map<uint32_t, Ref<GameObject>>();
		}
		char* Dest = (char*)Obj + m_Offset;
		return *(std::map<uint32_t, Ref<GameObject>>*)(Dest);
	}
}