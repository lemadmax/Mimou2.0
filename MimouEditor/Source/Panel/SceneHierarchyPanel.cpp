#include "SceneHierarchyPanel.h"

namespace Mimou
{
	SceneHierarchyPanel::SceneHierarchyPanel(const std::string PanelName, const Ref<Scene>& Scene)
		: Panel(PanelType::SceneHierarchyPanel, PanelName, Scene)
	{

	}

	void SceneHierarchyPanel::OnImGUIUpdate()
	{
		ImGui::Begin(m_PanelName.c_str());

		ImGui::End();
	}
}