#include "PropertiesPanel.h"
#include "SceneHierarchyPanel.h"

#include "Layer/EditorLayer.h"

namespace Mimou
{
	extern void DrawVec3Control(const std::string& Label, glm::vec3& Values);
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

		ShowComponent<TagComponent>("Tag Component", [&]() {
			TagComponent* Tag = SelectedObject->TryGetComponent<TagComponent>();
			if (Tag)
			{
				char Buffer[256];
				memset(Buffer, 0, sizeof(Buffer));
				strcpy_s(Buffer, sizeof(Buffer), Tag->Tag.c_str());
				if (ImGui::InputText("Tag", Buffer, sizeof(Buffer)))
				{
					Tag->Tag = std::string(Buffer);
				}
			}
			});

		ShowComponent<TransformComponent>("Transform Component", [&]() {
			TransformComponent* Transform = SelectedObject->TryGetComponent<TransformComponent>();
			if (Transform)
			{
				DrawVec3Control("Transform", Transform->Translation);
			}
			});

		ImGui::End();
	}
}