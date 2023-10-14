#include "mepch.h"
#include "StaticMeshSystem.h"
#include "Mimou/ECS/Component/StaticMeshComponent.h"
#include "Mimou/Renderer/Renderer.h"

namespace Mimou
{
	StaticMeshSystem* StaticMeshSystem::s_Instance = nullptr;
	StaticMeshSystem* StaticMeshSystem::GetInstance()
	{
		if (!s_Instance)
		{
			s_Instance = new StaticMeshSystem();
		}
		return s_Instance;
	}

	void StaticMeshSystem::React(GameObject* Entity)
	{
		Transform WorldTransform = Entity->GetWorldTransform();
		Ref<StaticMeshComponent> Comp = static_pointer_cast<StaticMeshComponent>(Entity->GetComponentByName("Static Mesh"));
		Ref<StaticMesh> StaticMesh = Comp->GetStaticMesh();
		Renderer::SubmitArrays(StaticMesh->GetVertexArray(), StaticMesh->GetMaterial(), WorldTransform.GetTransformMatrix());
	}

	StaticMeshSystem::StaticMeshSystem()
		: SystemBase("Static Mesh System")
	{

	}
}