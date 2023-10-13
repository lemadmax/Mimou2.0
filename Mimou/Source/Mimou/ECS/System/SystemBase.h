#pragma once
#include "Mimou/ECS/Entity/GameObject.h"

namespace Mimou
{
	class SystemBase
	{
	protected:
		SystemBase(const std::string& Name);

		virtual void React(Ref<GameObject> Entity) = 0;

	private:
		std::string m_Name;
	};
}