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
		StaticMesh(MeshType Type, std::vector<float> Vertices);
		~StaticMesh();
		
		inline MeshType GetMeshType() const { return m_Type; }
		inline std::vector<float> GetVerticesVec() const { return m_Vertices; }
		inline const float* GetVertices() const { return m_Vertices.data(); }
		inline uint32_t GetSize() const { return m_Vertices.size(); }

	private:
		MeshType m_Type;

		std::vector<float> m_Vertices;
	};

	class StaticMeshLibrary
	{
	public:
		static Reference<StaticMesh> CreateSphere(uint32_t NU, uint32_t NV);

		static Reference<StaticMesh> CreateCube(uint32_t NU, uint32_t NV);
	};
}