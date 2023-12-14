#include "mepch.h"
#include "StaticMesh.h"
#include "Mimou/Renderer/Buffer.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

namespace Mimou
{
	template<typename... Args>
	std::vector<float> CreateMesh(uint32_t NU, uint32_t NV, std::function<void(std::vector<float>&, float, float, Args...)> Func, Args... Data)
	{
		std::vector<float> Vertices;
		for (float v = 0; v < 1; v += 1.0 / NV)
		{
			for (float u = 0; u <= 1; u += 1.0 / NU)
			{
				Func(Vertices, u, v, Data...);
				Func(Vertices, u, v + 1.0 / NV, Data...);
			}
			Func(Vertices, 1, v, Data...);
			Func(Vertices, 0, v + 1.0 / NV, Data...);
		}

		return Vertices;
	}

	// i: the coordinate where z defines
	// z: the value of the const coordinate
	std::vector<float> CreateSquareMesh(int32_t i, int32_t z)
	{
		const uint32_t N = 8;
		std::vector<float> Vertices(4 * N);
		uint32_t j = z < 0 ? (i + 2) % 3 : (i + 1) % 3; // Right hand rule
		uint32_t k = z < 0 ? (i + 1) % 3 : (i + 2) % 3;

		// (-1, 1) (1, 1) (-1, -1) (1, -1)
		Vertices[i] = Vertices[1 * N + i] = Vertices[2 * N + i] = Vertices[3 * N + i] = z;
		Vertices[j] = Vertices[2 * N + j] = Vertices[2 * N + k] = Vertices[3 * N + k] = -1;
		Vertices[k] = Vertices[1 * N + j] = Vertices[1 * N + k] = Vertices[3 * N + j] = 1;

		Vertices[i + 3] = Vertices[1 * N + i + 3] = Vertices[2 * N + i + 3] = Vertices[3 * N + i + 3] = z < 0 ? -1 : 1;
		Vertices[j + 3] = Vertices[1 * N + j + 3] = Vertices[2 * N + j + 3] = Vertices[3 * N + j + 3] = 0;
		Vertices[k + 3] = Vertices[1 * N + k + 3] = Vertices[2 * N + k + 3] = Vertices[3 * N + k + 3] = 0;

		// Texture coordinates
		Vertices[N - 1] = Vertices[2 * N - 1] = Vertices[2 * N - 2] = Vertices[4 * N - 2] = 1;
		Vertices[N - 2] = Vertices[3 * N - 2] = Vertices[3 * N - 1] = Vertices[4 * N - 1] = 0;

		return Vertices;
	}

	void CreateSquareMeshTex(float* Vertices, int32_t i, int32_t z)
	{
		const uint32_t N = 8;

		uint32_t j = z < 0 ? (i + 2) % 3 : (i + 1) % 3; // Right hand rule
		uint32_t k = z < 0 ? (i + 1) % 3 : (i + 2) % 3;

		// coordinates
		// (-1, 1) (1, 1) (-1, -1) (1, -1)
		Vertices[i] = Vertices[1 * N + i] = Vertices[2 * N + i] = Vertices[3 * N + i] = z;
		Vertices[j] = Vertices[2 * N + j] = Vertices[2 * N + k] = Vertices[3 * N + k] = -1;
		Vertices[k] = Vertices[1 * N + j] = Vertices[1 * N + k] = Vertices[3 * N + j] = 1;

		// normals
		Vertices[i + 3] = Vertices[1 * N + i + 3] = Vertices[2 * N + i + 3] = Vertices[3 * N + i + 3] = z < 0 ? -1 : 1;
		Vertices[j + 3] = Vertices[1 * N + j + 3] = Vertices[2 * N + j + 3] = Vertices[3 * N + j + 3] = 0;
		Vertices[k + 3] = Vertices[1 * N + k + 3] = Vertices[2 * N + k + 3] = Vertices[3 * N + k + 3] = 0;

		// Texture coordinates
		Vertices[N - 1] = Vertices[2 * N - 1] = Vertices[2 * N - 2] = Vertices[4 * N - 2] = 1;
		Vertices[N - 2] = Vertices[3 * N - 2] = Vertices[3 * N - 1] = Vertices[4 * N - 1] = 0;
	}

	std::vector<float> GlueMeshes(const std::vector<float>& MeshA, const std::vector<float>& MeshB, uint32_t VertexSize)
	{
		std::vector<float> NewMesh(MeshA.size() + MeshB.size() + 2 * VertexSize);
		for (int i = 0; i < MeshA.size(); i++)
		{
			NewMesh[i] = MeshA[i];
		}
		for (int i = 0; i < VertexSize; i++)
		{
			NewMesh[MeshA.size() + i] = MeshA[MeshA.size() - VertexSize + i];
		}
		for (int i = 0; i < VertexSize; i++) 
		{
			NewMesh[MeshA.size() + VertexSize + i] = MeshB[i];
		}
		for (int i = 0; i < MeshB.size(); i++)
		{
			NewMesh[MeshA.size() + VertexSize * 2 + i] = MeshB[i];
		}
		return NewMesh;
	}

	std::vector<float> CreateCubeMesh()
	{
		return	GlueMeshes(
					GlueMeshes(CreateSquareMesh(0, -1), CreateSquareMesh(0, 1), 8),
					GlueMeshes(
						GlueMeshes(CreateSquareMesh(1, -1), CreateSquareMesh(1, 1), 8),
						GlueMeshes(CreateSquareMesh(2, -1), CreateSquareMesh(2, 1), 8)
					, 8)
				, 8);
	}

	void UVToSphere(std::vector<float>& Vertices, float U, float V)
	{
		float Theta = 2 * glm::pi<float>() * U;
		float Phi = glm::pi<float>() * (V - 0.5);
		float X = glm::cos(Theta) * glm::cos(Phi);
		float Y = glm::sin(Theta) * glm::cos(Phi);
		float Z = glm::sin(Phi);

		std::vector<float> Points({X, Y, Z, X, Y, Z});
		Vertices.insert(Vertices.end(), Points.begin(), Points.end());
	}

	Ref<StaticMesh> StaticMeshLibrary::CreateSphere(uint32_t NU, uint32_t NV)
	{
		return CreateRef<StaticMesh>(StaticMesh::MeshType::Sphere, NU, NV);
	}
	Ref<StaticMesh> StaticMeshLibrary::CreateCube()
	{
		return CreateRef<StaticMesh>(StaticMesh::MeshType::Cube, 0, 0);
	}

	Ref<StaticMesh> StaticMeshLibrary::CreateSquare(uint32_t i, uint32_t z)
	{
		return CreateRef<StaticMesh>(StaticMesh::MeshType::Square, i, z);
	}

	Ref<VertexArray> StaticMeshLibrary::CreateSquareVA(uint32_t i, uint32_t z)
	{
		Ref<VertexArray> VA = VertexArray::Create();
		
		const uint32_t N = 4 * 8;
		float Data[N];
		CreateSquareMeshTex(Data, i, z);

		Ref<VertexBuffer> VB = VertexBuffer::Create(Data, sizeof(Data));
		VB->SetLayout({
			{ "a_Position", ShaderDataType::Float3 },
			{ "a_Normal", ShaderDataType::Float3 },
			{ "a_TexCoord", ShaderDataType::Float2 }
			});

		VA->AddVertexBuffer(VB);

		return VA;
	}

	Ref<VertexArray> StaticMeshLibrary::CreateTriangle()
	{
		Ref<VertexArray> TriangleVertices = VertexArray::Create();

		float Vertices[3 * 6] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> VertexBuffer = VertexBuffer::Create(Vertices, sizeof(Vertices));

		BufferLayout Layout =
		{
			{ "a_Position", ShaderDataType::Float3 },
			{ "a_Normal", ShaderDataType::Float3 }
		};
		VertexBuffer->SetLayout(Layout);

		TriangleVertices->AddVertexBuffer(VertexBuffer);

		return TriangleVertices;
	}

	Ref<VertexArray> StaticMeshLibrary::CreateCubeVA()
	{
		std::vector<float> Vertices = CreateCubeMesh();
		if (Vertices.empty())
		{
			ME_ENGINE_WARN("CreateMesh: Failed to create square mesh");
			return nullptr;
		}
		float* Data = new float[Vertices.size()];
		memcpy(Data, &Vertices[0], Vertices.size() * sizeof(float));

		Ref<VertexArray> VertexArray = VertexArray::Create();
		BufferLayout Layout =
		{
			{ "a_Position", ShaderDataType::Float3 },
			{ "a_Normal", ShaderDataType::Float3 },
			{ "a_TexCoord", ShaderDataType::Float2 }
		};
		Ref<VertexBuffer> VertexBuffer = VertexBuffer::Create(Data, Vertices.size() * sizeof(float));
		VertexBuffer->SetLayout(Layout);
		VertexArray->AddVertexBuffer(VertexBuffer);
		return VertexArray;
	}

	Ref<VertexArray> StaticMeshLibrary::CreateSphereVA(uint32_t NU, uint32_t NV)
	{
		std::function<void(std::vector<float>&, float, float)> Fn(UVToSphere);
		std::vector<float> Vertices = CreateMesh(NU, NV, Fn);
		if (Vertices.empty())
		{
			ME_ENGINE_WARN("CreateMesh: Failed to create sphere mesh");
			return nullptr;
		}
		float* Data = new float[Vertices.size()];
		memcpy(Data, &Vertices[0], Vertices.size() * sizeof(float));

		Ref<VertexArray> VertexArray = VertexArray::Create();
		BufferLayout Layout =
		{
			{ "a_Position", ShaderDataType::Float3 },
			{ "a_Normal", ShaderDataType::Float3 }
		};
		Ref<VertexBuffer> VertexBuffer = VertexBuffer::Create(Data, Vertices.size() * sizeof(float));
		VertexBuffer->SetLayout(Layout);
		VertexArray->AddVertexBuffer(VertexBuffer);
		return VertexArray;
	}

	StaticMesh::StaticMesh(MeshType Type, uint32_t NU, uint32_t NV)
		: m_Type(Type), m_NU(NU), m_NV(NV)
	{

	}

	StaticMesh::~StaticMesh()
	{
		delete m_Vertices;
	}

	void StaticMesh::Draw()
	{

	}

	void StaticMesh::GenerateVertices()
	{
		switch (m_Type)
		{
		case StaticMesh::MeshType::None:
		{
			ME_ENGINE_WARN("Attemp to generate a None type mesh");
			return;
		}
		case StaticMesh::MeshType::Sphere:
		{
			std::function<void(std::vector<float>&, float, float)> Fn(UVToSphere);
			std::vector<float> Vertices = CreateMesh(m_NU, m_NV, Fn);
			if (Vertices.empty())
			{
				ME_ENGINE_WARN("CreateMesh: Failed to create sphere mesh");
				return;
			}
			m_Vertices = new float[Vertices.size()];
			memcpy(m_Vertices, &Vertices[0], Vertices.size() * sizeof(float));
			Cnt = Vertices.size();

			m_VertexArray = VertexArray::Create();
			BufferLayout Layout =
			{
				{ "a_Position", ShaderDataType::Float3 },
				{ "a_Normal", ShaderDataType::Float3 }
			};
			Ref<VertexBuffer> VertexBuffer = VertexBuffer::Create(m_Vertices, Cnt * sizeof(float));
			VertexBuffer->SetLayout(Layout);
			m_VertexArray->AddVertexBuffer(VertexBuffer);
			break;
		}
		case StaticMesh::MeshType::Square:
		{
			std::vector<float> Vertices = CreateSquareMesh(m_NU, m_NV);
			if (Vertices.empty())
			{
				ME_ENGINE_WARN("CreateMesh: Failed to create square mesh");
				return;
			}
			m_Vertices = new float[Vertices.size()];
			memcpy(m_Vertices, &Vertices[0], Vertices.size() * sizeof(float));
			Cnt = Vertices.size();

			m_VertexArray = VertexArray::Create();
			BufferLayout Layout =
			{
				{ "a_Position", ShaderDataType::Float3 },
				{ "a_Normal", ShaderDataType::Float3 },
				{ "a_TexCoord", ShaderDataType::Float2 }
			};
			Ref<VertexBuffer> VertexBuffer = VertexBuffer::Create(m_Vertices, Cnt * sizeof(float));
			VertexBuffer->SetLayout(Layout);
			m_VertexArray->AddVertexBuffer(VertexBuffer);
			break;
		}
		case StaticMesh::MeshType::Cube:
		{
			std::vector<float> Vertices = CreateCubeMesh();
			if (Vertices.empty())
			{
				ME_ENGINE_WARN("CreateMesh: Failed to create square mesh");
				return;
			}
			m_Vertices = new float[Vertices.size()];
			memcpy(m_Vertices, &Vertices[0], Vertices.size() * sizeof(float));
			Cnt = Vertices.size();

			m_VertexArray = VertexArray::Create();
			BufferLayout Layout =
			{
				{ "a_Position", ShaderDataType::Float3 },
				{ "a_Normal", ShaderDataType::Float3 },
				{ "a_TexCoord", ShaderDataType::Float2 }
			};
			Ref<VertexBuffer> VertexBuffer = VertexBuffer::Create(m_Vertices, Cnt * sizeof(float));
			VertexBuffer->SetLayout(Layout);
			m_VertexArray->AddVertexBuffer(VertexBuffer);
			break;
		}
		default:
		{
			ME_ENGINE_ERROR("Failed to generate vertices (mesh type:{})", m_Type);
			return;
		}
		}
	}
}