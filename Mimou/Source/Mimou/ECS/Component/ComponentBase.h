#pragma once
#include "Mimou/Timestep.h"

namespace Mimou
{
	// Forward declaration
	class GameObject;

	class ComponentBase
	{
	public:
		ComponentBase(Ref<GameObject> GameObject, const std::string& Name);

		virtual void OnUpdate(Timestep Ts) = 0;

	private:
		std::string m_Name;
		Ref<GameObject> m_Owner;
	};
}