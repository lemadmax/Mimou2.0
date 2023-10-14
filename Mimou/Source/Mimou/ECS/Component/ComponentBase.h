#pragma once
#include "Mimou/Timestep.h"

namespace Mimou
{
	// Forward declaration
	class GameObject;

	class ComponentBase
	{
	public:
		ComponentBase(const std::string& Name);

		virtual void OnUpdate(Timestep Ts) = 0;

		inline std::string GetName() const { return m_Name; }
		inline void SetOwner(GameObject* Owner) { m_Owner = Owner; }

	protected:
		std::string m_Name;
		GameObject* m_Owner;
	};
}