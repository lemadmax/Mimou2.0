#include "PropertiesPanel.h"
#include "SceneHierarchyPanel.h"

#include "Layer/EditorLayer.h"

namespace Mimou
{
	//extern void DrawVec3Control(const std::string& Label, glm::vec3& Values);
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
			ImGuiTreeNodeFlags NodeFlags = ImGuiTreeNodeFlags_DefaultOpen
				| ImGuiTreeNodeFlags_OpenOnArrow
				| ImGuiTreeNodeFlags_OpenOnDoubleClick;

			TransformComponent* Transform = SelectedObject->TryGetComponent<TransformComponent>();
			if (Transform)
			{
				if (ImGui::TreeNodeEx("Transform", NodeFlags))
				{
					PanelUtilities::DrawVec3Control("Translation", Transform->Translation);
					ImGui::Spacing();
					
					PanelUtilities::DrawVec3Control("Rotation", Transform->Rotation);
					ImGui::Spacing();

					PanelUtilities::DrawVec3Control("Scale", Transform->Scale);

					ImGui::TreePop();
				}
			}
			});

		ImGui::End();
	}
}