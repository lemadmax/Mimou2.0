#include "Panel.h"
#include "SceneHierarchyPanel.h"
#include "PropertiesPanel.h"

namespace Mimou
{

	Ref<Panel> Panel::CreatePanel(PanelType Type, const std::string& PanelName, const Ref<Scene>& Scene)
	{
		switch (Type)
		{
		case PanelType::SceneHierarchyPanel:
		{
			return CreateRef<SceneHierarchyPanel>(PanelName, Scene);
			break;
		}
		case PanelType::PropertiesPanel:
		{
			return CreateRef<PropertiesPanel>(PanelName, Scene);
			break;
		}
		default:
		{

		}
		}
		return Ref<Panel>();
	}

	Panel::Panel(PanelType Type, const std::string& PanelName, const Ref<Scene>& Scene)
		: m_Type(Type), m_PanelName(PanelName), m_Scene(Scene)
	{

	}

	void Panel::OnImGUIUpdate()
	{
			
	}
}
