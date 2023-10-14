#pragma once
#include "ComponentBase.h"
#include "Mimou/Mesh/StaticMesh.h"

namespace Mimou
{
	class StaticMeshComponent : public ComponentBase
	{
	public:
		StaticMeshComponent(const Ref<StaticMesh>& Mesh);

		virtual void OnUpdate(Timestep Ts) override;

		Ref<StaticMesh> GetStaticMesh() const { return m_Mesh; }

	private:
		Ref<StaticMesh> m_Mesh;
	};
}