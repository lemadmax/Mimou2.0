#pragma once
#include "SystemBase.h"

namespace Mimou
{
	class StaticMeshSystem : public SystemBase
	{
	private:
		StaticMeshSystem();
		static StaticMeshSystem* s_Instance;

	public:
		static StaticMeshSystem* GetInstance();

	public:
		virtual void React(Ref<GameObject> Entity) override;

	};
}