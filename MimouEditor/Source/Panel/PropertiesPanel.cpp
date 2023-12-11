#include "PropertiesPanel.h"

#include "Layer/EditorLayer.h"

namespace Mimou
{
	PropertiesPanel::PropertiesPanel(const std::string& PanelName, const Ref<Scene>& Scene)
		: Panel(PanelType::PropertiesPanel, PanelName, Scene)
	{

	}

	void PropertiesPanel::OnImGUIUpdate()
	{
		if (!m_Scene) return;
		
		Ref<SceneHierarchyPanel> SceneHierPanel = std::static_pointer_cast<SceneHierarchyPanel>(EditorLayer::GetInstance()->GetPanel(PanelType::SceneHierarchyPanel));
		if (!SceneHierPanel) return;
	}
}