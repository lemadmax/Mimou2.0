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
					| ImGuiTreeNodeFlags_Framed;

				if (ImGui::TreeNodeEx(Name.c_str(), NodeFlags))
				{
					ImGui::Spacing();

					DrawFunc(Component);

					ImGui::Spacing();
					ImGui::TreePop();
				}
			}
		}

	private:
		Ref<GameObject> SelectedObject;
	};
}