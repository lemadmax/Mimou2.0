#include "mepch.h"
#include "ComponentBase.h"
#include "Mimou/ECS/Entity/GameObject.h"

namespace Mimou
{
	ComponentBase::ComponentBase(Ref<GameObject> GameObject, const std::string& Name)
		: m_Name(Name), m_Owner(GameObject)
	{

	}
}