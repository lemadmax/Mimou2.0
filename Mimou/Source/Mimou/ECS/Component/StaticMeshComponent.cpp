#include "mepch.h"
#include "StaticMeshComponent.h"
#include "Mimou/ECS/System/StaticMeshSystem.h"

namespace Mimou
{
	StaticMeshComponent::StaticMeshComponent(const Ref<StaticMesh>& Mesh)
		: m_Mesh(Mesh), ComponentBase("Static Mesh")
	{

	}

	void StaticMeshComponent::OnUpdate(Timestep Ts)
	{
		StaticMeshSystem::GetInstance()->React(m_Owner);
	}
}