#include "mepch.h"
#include "LayerStack.h"

namespace Mimou
{
	LayerStack::LayerStack()
	{

	}

	LayerStack::~LayerStack()
	{
		for (Layer* Layer : m_Layers)
		{
			delete Layer;
		}
	}

	void LayerStack::PushLayer(Layer* Layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_InsertIndex, Layer);
		m_InsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* Overlay)
	{
		m_Layers.emplace_back(Overlay);
	}

	void LayerStack::PopLayer(Layer* Layer)
	{
		auto It = std::find(m_Layers.begin(), m_Layers.begin() + m_InsertIndex, Layer);
		if (It != m_Layers.begin() + m_InsertIndex)
		{
			Layer->OnDetach();
			m_Layers.erase(It);
			m_InsertIndex--;
		}
	}

	void LayerStack::PopOverLay(Layer* Overlay)
	{
		auto It = std::find(m_Layers.begin() + m_InsertIndex, m_Layers.end(), Overlay);
		if (It != m_Layers.end()) 
		{
			Overlay->OnDetach();
			m_Layers.erase(It);
		}
	}

}