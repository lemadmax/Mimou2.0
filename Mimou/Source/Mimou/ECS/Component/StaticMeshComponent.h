#pragma once
#include "ComponentBase.h"
#include "Mimou/Mesh/StaticMesh.h"

namespace Mimou
{
	class StaticMeshComponent : public ComponentBase
	{
	public:
		StaticMeshComponent(Ref<GameObject> GameObject, Ref<StaticMesh> Mesh);

		virtual void OnUpdate(Timestep Ts) override;

	private:
		Ref<StaticMesh> m_Mesh;
	};
}