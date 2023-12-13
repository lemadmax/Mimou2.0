#include "Panel.h"
#include "SceneHierarchyPanel.h"
#include "PropertiesPanel.h"

#include "imgui_internal.h"

namespace Mimou
{

	Ref<Panel> Panel::CreatePanel(PanelType Type, const std::string& PanelName, const Ref<Scene>& Scene)
	{
		switch (Type)
		{
		case PanelType::SceneHierarchyPanel:
		{
			return CreateRef<SceneHierarchyPanel>(PanelName, Scene);
			break;
		}
		case PanelType::PropertiesPanel:
		{
			return CreateRef<PropertiesPanel>(PanelName, Scene);
			break;
		}
		default:
		{

		}
		}
		return Ref<Panel>();
	}

	Panel::Panel(PanelType Type, const std::string& PanelName, const Ref<Scene>& Scene)
		: m_Type(Type), m_PanelName(PanelName), m_Scene(Scene)
	{

	}

	void Panel::OnImGUIUpdate()
	{
			
	}

	void PanelUtilities::DrawVec3Control(const std::string& Label, glm::vec3& Values)
	{
		static float DragSpeed = 0.001;

		ImGui::PushID(Label.c_str());

		ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());

		ImGui::DragFloat("X", &Values.x, DragSpeed);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::DragFloat("Y", &Values.y, DragSpeed);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::DragFloat("Z", &Values.z, DragSpeed);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::Text(Label.c_str());
		ImGui::PopItemWidth();

		ImGui::PopID();
	}
}
