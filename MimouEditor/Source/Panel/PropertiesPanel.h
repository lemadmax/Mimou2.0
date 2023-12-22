#pragma once
#include "Panel.h"

namespace Mimou
{
	class PropertiesPanel : public Panel
	{
	public:
		PropertiesPanel(const std::string& PanelName);

		virtual void OnImGUIUpdate() override;


	private:

		template<typename T, typename Fn>
		void ShowComponent(const std::string& Name, Fn DrawFunc)
		{
			T* Component = SelectedObject->TryGetComponent<T>();
			if (Component)
			{
				ImGuiTreeNodeFlags NodeFlags = ImGuiTreeNodeFlags_SpanAvailWidth
					| ImGuiTreeNodeFlags_OpenOnArrow
					| ImGuiTreeNodeFlags_OpenOnDoubleClick
					| ImGuiTreeNodeFlags_DefaultOpen
					| ImGuiTreeNodeFlags_Framed
					| ImGuiTreeNodeFlags_AllowOverlap;

				if (ImGui::BeginPopupContextItem("Edit Component"))
				{
					if (ImGui::Selectable("Remove"))
					{
						SelectedObject->RemoveComponent<T>();
					}
					ImGui::EndPopup();
				}

				ImVec2 RegionSize = ImGui::GetContentRegionAvail();
				
				bool NodeOpened = ImGui::TreeNodeEx(Name.c_str(), NodeFlags);

				float FrameHeight = ImGui::GetFrameHeight();
				ImGui::SameLine(RegionSize.x - FrameHeight * 0.5);
				ImGui::Button("+", ImVec2(FrameHeight, FrameHeight));

				if (NodeOpened)
				{
					ImGui::Spacing();

					DrawFunc(Component);

					ImGui::Spacing();
					ImGui::TreePop();
				}


			}
		}

		void ShowMaterial(Ref<Material> Mat);

	private:
		Ref<GameObject> SelectedObject;
	};
}

#define SHOW_SELECT_ADD_COMPONENT(Component, GameObject) if(ImGui::Selectable(#Component)) { GameObject->AddComponent<Component>(); }