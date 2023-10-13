#include "mepch.h"
#include "StaticMeshComponent.h"

namespace Mimou
{
	StaticMeshComponent::StaticMeshComponent(Ref<GameObject> GameObject, Ref<StaticMesh> Mesh)
		: m_Mesh(Mesh), ComponentBase(GameObject, "Static Mesh")
	{

	}

	void StaticMeshComponent::OnUpdate(Timestep Ts)
	{

	}
}