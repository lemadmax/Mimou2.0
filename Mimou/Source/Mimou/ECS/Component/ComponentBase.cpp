#include "mepch.h"
#include "ComponentBase.h"
#include "Mimou/ECS/Entity/GameObject.h"

namespace Mimou
{
	ComponentBase::ComponentBase(const std::string& Name)
		: m_Name(Name)
	{
		m_Owner = nullptr;
	}
}