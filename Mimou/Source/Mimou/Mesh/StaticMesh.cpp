#include "mepch.h"
#include "StaticMesh.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

namespace Mimou
{
	template<typename... Args>
	std::vector<float> CreateMesh(uint32_t NU, uint32_t NV, std::function<std::vector<float>(float, float, Args...)> Func, Args... Data)
	{
		std::vector<float> Vertices;
		for (float v = 0; v < 1; v += 1 / NV)
		{
			for (float u = 0; u <= 1; u += 1 / NU)
			{
				Vertices.push_back(Func(u, v, Data...));
				Vertices.push_back(Func(u, v + 1 / NV, Data...));
			}
			Vertices.push_back(Func(1, v, Data...));
			Vertices.push_back(Func(0, v + 1 / NV, Data...));
		}
		return Vertices;
	}

	std::vector<float> UVToSphere(float U, float V)
	{
		float Theta = 2 * glm::pi<float>() * U;
		float Phi = glm::pi<float>() * (V - 0.5);
		float X = glm::cos(Theta) * glm::cos(Phi);
		float Y = glm::sin(Theta) * glm::cos(Phi);
		float Z = glm::sin(Phi);
		return { X, Y, Z, X, Y, Z };
	}

	Reference<StaticMesh> StaticMeshLibrary::CreateSphere(uint32_t NU, uint32_t NV)
	{
		std::function<std::vector<float>(float, float)> Fn(UVToSphere);
		return std::make_shared<StaticMesh>(StaticMesh::MeshType::Sphere, CreateMesh<>(NU, NV, Fn));
	}
	Reference<StaticMesh> StaticMeshLibrary::CreateCube(uint32_t NU, uint32_t NV)
	{
		return Reference<StaticMesh>();
	}

	StaticMesh::StaticMesh(MeshType Type, std::vector<float> Vertices)
		: m_Type(Type), m_Vertices(Vertices)
	{

	}

	StaticMesh::~StaticMesh()
	{
	}
}