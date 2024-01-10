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
}