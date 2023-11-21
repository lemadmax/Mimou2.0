#pragma once
#include "Mimou/Timestep.h"
#include "entt/entt.hpp"

namespace Mimou
{
	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void OnUpdate(Timestep Ts);

	private:
		entt::registry m_Regisity;
	};
}