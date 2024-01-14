#include "mepch.h"
#include "MEObject.h"

namespace Mimou
{
    MEClass* MEClassMEObject = new MEClass("MEObject", []() { return CreateRef<MEObject>(); }, []() { return new MEObject(); });

    MEObject::MEObject()
    {

    }

    MEObjectManager::MEObjectManager()
    {

    }

    MEObjectManager::~MEObjectManager()
    {

    }

    std::string MEObjectManager::RegisterObject(const Ref<MEObject>& Object)
    {
        uint32_t Cnt = 0;
        std::string Prefix = Object->GetClass()->GetName() + "_C_";
        std::string ObjectName = Prefix + std::to_string(Cnt);
        while (MEObjects.contains(ObjectName))
        {
            ObjectName = Prefix + std::to_string(++Cnt);
        }
        MEObjects.emplace(ObjectName, Object);
        Object->m_ObjectName = ObjectName;
        return ObjectName;
    }

    Ref<MEObject> NewObjectByClass(MEClass* Class)
    {
        Ref<MEObject> Out = Class->Instantiate();
        MEObjectManager::GetInstance()->RegisterObject(Out);
        return Out;
    }
}