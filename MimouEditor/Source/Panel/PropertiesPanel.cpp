#include "PropertiesPanel.h"
#include "SceneHierarchyPanel.h"

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

		SelectedObject = SceneHierPanel->GetSelectedObject();

		ImGui::Begin(m_PanelName.c_str());

		if (!SelectedObject)
		{
			ImGui::End();
			return;
		}

		ShowTagComponent();

		ImGui::End();
	}

	void PropertiesPanel::ShowTagComponent()
	{
		TagComponent* Tag = SelectedObject->TryGetComponent<TagComponent>();
		if (Tag)
		{
			char Buffer[256];
			memset(Buffer, 0, sizeof(Buffer));
			strcpy_s(Buffer, sizeof(Buffer), Tag->Tag.c_str());
			ImGui::InputText("Tag", Buffer, sizeof(Buffer));
		}
	}
}