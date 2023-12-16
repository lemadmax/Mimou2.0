#pragma once
#include "Mimou.h"

#include "imgui_internal.h"

namespace Mimou
{
	enum class PanelType : uint32_t
	{
		SceneHierarchyPanel = 1,
		PropertiesPanel = 2,
	};

	class Panel
	{
	public:
		Panel() = default;
		Panel(PanelType Type, const std::string& PanelName, const Ref<Scene>& Scene);
		virtual ~Panel() = default;

		virtual void OnImGUIUpdate();

		static Ref<Panel> CreatePanel(PanelType Type, const std::string& PanelName, const Ref<Scene>& Scene);
		
	protected:
		Ref<Scene> m_Scene;

		PanelType m_Type;
		std::string m_PanelName;
	};

	class PanelUtilities
	{
	public:
		static void DrawVec3Control(const std::string& Label, glm::vec3& Values, const std::string& ItemLabels = "XYZ");

		template<typename T, typename Fn>
		static void DrawDynamicVector(const std::string& Label, std::vector<T>& Vec, Fn ItemFunc)
		{
			ImGuiTreeNodeFlags NodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_AllowItemOverlap;
			float LineWidth = ImGui::CalcItemWidth();

			ImVec2 ContentRegionAvail = ImGui::GetContentRegionAvail();
			float LineHeight = ImGui::GetTextLineHeight();
			ImGui::PushItemWidth(-LineHeight);
			if (ImGui::TreeNodeEx(Label.c_str(), NodeFlags))
			{
				ImGui::TreePop();
			}
			ImGui::PopItemWidth();
			ImGui::SameLine(ContentRegionAvail.x);
			if (ImGui::Button("+", ImVec2(LineHeight, LineHeight)))
			{

			}

			//ImGui::PopStyleVar(1);
		}
	};
}