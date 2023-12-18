#pragma once
#include "yaml-cpp/yaml.h"

namespace Mimou
{
	class SceneSerializer
	{
	private:
		SceneSerializer() = default;

	public:
		static SceneSerializer* Get()
		{
			if (!s_Instance)
				[

				]
		}

	private:
		static SceneSerializer* s_Instance;
	};
}