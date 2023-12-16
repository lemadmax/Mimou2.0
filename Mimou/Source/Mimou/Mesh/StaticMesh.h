#pragma once
#include "Mimou/Renderer/VertexArray.h"

namespace Mimou
{

	class StaticMeshLibrary
	{
	private:
		StaticMeshLibrary() = default;

	public:
		static StaticMeshLibrary* Get()
		{
			if (!s_Instance)
			{
				s_Instance = new StaticMeshLibrary();
			}
			return s_Instance;
		}

		static void Init();
		static Ref<VertexArray> GetAsset(const std::string& AssetName);


		std::vector<std::string> GetAvaliableAssets();
		std::vector<std::string> GetAvaliableAssets(const std::string& AssetName, int& Idx);
		void PreloadAssets();

	private:
		std::map<std::string, Ref<VertexArray>> CachedVA;

		static StaticMeshLibrary* s_Instance;
	};
}