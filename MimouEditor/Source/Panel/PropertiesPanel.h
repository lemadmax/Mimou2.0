#pragma once
#include "Panel.h"

namespace Mimou
{
	class PropertiesPanel : public Panel
	{
	public:
		PropertiesPanel(const std::string& PanelName, const Ref<Scene>& Scene);

		virtual void OnImGUIUpdate() override;


	private:

		void ShowTagComponent();

		template<typename T>
		void ShowComponent(const std::string& Name, std::function<void()> Fn)
		{
			ImGuiTreeNodeFlags NodeFlags = ImGuiTreeNodeFlags_SpanAvailWidth 
				| ImGuiTreeNodeFlags_OpenOnArrow 
				| ImGuiTreeNodeFlags_OpenOnDoubleClick 
				| ImGuiTreeNodeFlags_DefaultOpen
				| ImGuiTreeNodeFlags_Framed;

			if (ImGui::TreeNodeEx(Name.c_str(), NodeFlags))
			{
				ImGui::Spacing();

				Fn();

				ImGui::Spacing();
				ImGui::TreePop();
			}
		}

	private:
		Ref<GameObject> SelectedObject;
	};
}