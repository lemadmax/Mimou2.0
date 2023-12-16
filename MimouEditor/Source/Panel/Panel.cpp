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

	void PanelUtilities::DrawVec3Control(const std::string& Label, glm::vec3& Values, const std::string& ItemLabels)
	{
		ME_ENGINE_ASSERT(ItemLabels.length == 3, "Bad vec3 item labels");
		static float DragSpeed = 0.001;

		ImGui::PushID(Label.c_str());

		//ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());
		float LineWidth = ImGui::CalcItemWidth();
		float vecItemWidth = (LineWidth - 120.0f) / 3;
		
		//ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%c", ItemLabels[0]);
		//ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));

		//ImGui::PushItemWidth(80.0f);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(1.0f, 0.0f));
		ImGui::ButtonEx(Label.c_str(), ImVec2(90.0f, 0.0f));
		ImGui::PopStyleVar(1);
		ImGui::PopStyleColor(1);
		ImGui::SameLine();

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

		ImGui::PushItemWidth(10.0f);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.0f, 0.0f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4f, 0.0f, 0.0f, 1.0f));
		if (ImGui::Button(std::format("{}:", ItemLabels[0]).c_str()))
		{
			Values.x = 0.0f;
		}
		ImGui::PopStyleColor(3);
		ImGui::PopItemWidth();

		ImGui::SameLine();
		ImGui::PushItemWidth(vecItemWidth);
		ImGui::DragFloat("##X", &Values.x, DragSpeed);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		//ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%c", ItemLabels[1]);

		ImGui::PushItemWidth(10.0f);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.8f, 0.0f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.4f, 0.0f, 1.0f));
		if(ImGui::Button(std::format("{}:", ItemLabels[1]).c_str()))
		{
			Values.x = 0.0f;
		}
		ImGui::PopStyleColor(3);
		ImGui::PopItemWidth();

		ImGui::SameLine();
		ImGui::PushItemWidth(vecItemWidth);
		ImGui::DragFloat("##Y", &Values.y, DragSpeed);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		//ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%c", ItemLabels[2]);

		ImGui::PushItemWidth(10.0f);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 1.0f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.8f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.0f, 0.4f, 1.0f));
		if(ImGui::Button(std::format("{}:", ItemLabels[2]).c_str()))
		{
			Values.x = 0.0f;
		}
		ImGui::PopStyleColor(3);
		ImGui::PopItemWidth();

		ImGui::SameLine();
		ImGui::PushItemWidth(vecItemWidth);
		ImGui::DragFloat("##Z", &Values.z, DragSpeed);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar(1);

		ImGui::PopID();
	}
}
