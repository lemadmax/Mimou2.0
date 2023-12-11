#include "SceneHierarchyPanel.h"

#include "entt/entt.hpp"

namespace Mimou
{
	SceneHierarchyPanel::SceneHierarchyPanel(const std::string& PanelName, const Ref<Scene>& Scene)
		: Panel(PanelType::SceneHierarchyPanel, PanelName, Scene), SelectedObject(nullptr)
	{

	}

	void SceneHierarchyPanel::OnImGUIUpdate()
	{
		if (!m_Scene) return;

		ImGui::Begin(m_PanelName.c_str());

		for (auto Object : m_Scene->GameObjects)
		{
			Ref<GameObject> GB = Object.second;
			if (GB->GetParent() == nullptr)
			{
				ShowGameObject(GB);
			}
		}

		ImGui::End();
	}

	void SceneHierarchyPanel::ShowGameObject(Ref<GameObject> GB)
	{
		ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_SpanAvailWidth;
		if (!GB->HasChildren())
		{
			base_flags |= ImGuiTreeNodeFlags_Leaf;
		}
		else
		{
			base_flags |= ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;
		}
		if (SelectedObject == GB)
		{
			base_flags |= ImGuiTreeNodeFlags_Selected;
		}
		entt::entity ID = GB->GetEntityID();
		std::string GBTag = m_Scene->m_Registry.get<TagComponent>(ID).Tag;
		if (ImGui::TreeNodeEx((void*)(uint32_t)ID, base_flags, GBTag.c_str()))
		{
			if (ImGui::IsItemClicked() || ImGui::IsItemToggledOpen())
			{
				SelectedObject = GB;
			}
			for (auto Child : GB->GetChildren())
			{
				ShowGameObject(Child);
			}

			ImGui::TreePop();
		}

		
	}
}