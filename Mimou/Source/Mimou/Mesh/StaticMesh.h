#pragma once

namespace Mimou
{
	class StaticMesh
	{
	public:
		enum class MeshType
		{
			None,
			Sphere,
			Cube
		};

	public:
		StaticMesh(MeshType Type, uint32_t NU, uint32_t NV);
		~StaticMesh();
		
		inline MeshType GetMeshType() const { return m_Type; }
		inline uint32_t GetSize() const { return Cnt; }
		inline float* GetVertices()
		{ 
			if (m_Vertices == nullptr)
			{
				GenerateVertices();
			}
			return m_Vertices; 
		}

		void GenerateVertices();

	private:
		MeshType m_Type;
		uint32_t m_NU, m_NV;

		float* m_Vertices = nullptr;
		uint32_t Cnt = 0;
	};

	class StaticMeshLibrary
	{
	public:
		static Reference<StaticMesh> CreateSphere(uint32_t NU, uint32_t NV);

		static Reference<StaticMesh> CreateCube(uint32_t NU, uint32_t NV);
	};
}