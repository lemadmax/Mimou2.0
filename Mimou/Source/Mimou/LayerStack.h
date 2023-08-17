#pragma once
#include "Mimou/Core.h"
#include "Mimou/Layer.h"

#include <vector>

namespace Mimou
{
	class ME_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* Layer);
		void PushOverlay(Layer* Overlay);
		void PopLayer(Layer* Layer);
		void PopOverLay(Layer* Overlay);

		inline std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		inline std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		UINT32 m_InsertIndex = 0;
	};
}