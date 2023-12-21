#include "SceneHierarchyPanel.h"

#include "Layer/EditorLayer.h"

#include "entt/entt.hpp"

namespace Mimou
{
	SceneHierarchyPanel::SceneHierarchyPanel(const std::string& PanelName)
		: Panel(PanelType::SceneHierarchyPanel, PanelName), SelectedObject(nullptr)
	{

	}

	void SceneHierarchyPanel::OnImGUIUpdate()
	{
		m_Scene = EditorLayer::GetInstance()->GetActiveScene();
		if (!m_Scene)
		{
			ImGui::Begin("No Opened Scene");

			ImGui::End();
			return;
		}

		ImGui::Begin(m_PanelName.c_str());

		PendingDestroy.clear();
		bDestroyAll = false;

		if (ImGui::BeginPopupContextWindow("Add Entity", ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight))
		{
			if (ImGui::Selectable("Add game object"))
			{
				m_Scene->CreateGameObject();
			}
			if (ImGui::Selectable("Remove all"))
			{
				bDestroyAll = true;
			}
			ImGui::EndPopup();
		}

		for (auto Object : m_Scene->GameObjects)
		{
			Ref<GameObject> GB = Object.second;
			if (GB->GetParent() == nullptr)
			{
				ShowGameObject(GB);
			}
			if (!SelectedObject) SelectedObject = GB;
		}
		if (bDestroyAll)
		{
			m_Scene->DestroyAllGameObjects();
		}
		else
		{
			for (Ref<GameObject> Object : PendingDestroy)
			{
				m_Scene->DestroyGameObject(Object);
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
			base_flags |= ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		}
		if (SelectedObject == GB)
		{
			base_flags |= ImGuiTreeNodeFlags_Selected;
		}
		entt::entity ID = GB->GetEntityID();
		std::string GBTag = m_Scene->m_Registry.get<TagComponent>(ID).Tag;
		if (ImGui::TreeNodeEx((void*)(uint32_t)ID, base_flags, GBTag.c_str()))
		{

			if (ImGui::BeginPopupContextItem("Add Child Entity", ImGuiPopupFlags_MouseButtonRight))
			{
				SelectedObject = GB;
				if (ImGui::Selectable("Add child game object"))
				{
					m_Scene->CreateGameObject("GameObject", SelectedObject);
				}
				if (ImGui::Selectable("Remove"))
				{
					PendingDestroy.push_back(SelectedObject);
				}
				ImGui::EndPopup();
			}

			if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
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

	Ref<GameObject> SceneHierarchyPanel::GetSelectedObject()
	{
		if (SelectedObject && SelectedObject->GetOwnedScene() != m_Scene)
		{
			SelectedObject = nullptr;
		}
		return SelectedObject;
	}

	void SceneHierarchyPanel::OpenRightClickPopup(Ref<GameObject> GB)
	{
		
	}
}