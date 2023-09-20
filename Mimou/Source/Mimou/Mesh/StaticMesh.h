#pragma once
#include "Mimou/Renderer/Material/Material.h"
#include "Mimou/Renderer/VertexArray.h"

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

		void Draw();
		
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
		inline Ref<VertexArray> GetVertexArray()
		{
			if (m_VertexArray == nullptr)
			{
				GenerateVertices();
			}
			return m_VertexArray;
		}

		void GenerateVertices();

		inline void SetMaterial(Ref<Material> Material) { m_Material = Material; }
		inline Ref<Material> GetMaterial() const { return m_Material; }

	private:
		MeshType m_Type;
		uint32_t m_NU, m_NV;

		float* m_Vertices = nullptr;
		uint32_t Cnt = 0;

		Ref<VertexArray> m_VertexArray;
		Ref<Material> m_Material;
	};

	class StaticMeshLibrary
	{
	public:
		static Ref<StaticMesh> CreateSphere(uint32_t NU, uint32_t NV);

		static Ref<StaticMesh> CreateCube(uint32_t NU, uint32_t NV);
	};
}