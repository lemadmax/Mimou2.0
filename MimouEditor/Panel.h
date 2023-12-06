#pragma once
#include "Mimou.h"

namespace Mimou
{
	class Panel
	{
	public:
		Panel() = default;
		Panel(const Ref<Scene>& Scene);
		virtual ~Panel() = default;

		virtual void OnImGUIUpdate();
		
	private:
		Ref<Scene> m_Scene;
	};
}