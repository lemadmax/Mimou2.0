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

		static bool DrawComboFromVector(const std::string& Label, const std::vector<std::string>& Vec, int* CurrentIdx);

		template<typename T, typename Fn>
		static void DrawDynamicVector(const std::string& Label, std::vector<T>& Vec, Fn ItemFunc)
		{
			ImGuiTreeNodeFlags NodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_DefaultOpen;

			if (ImGui::TreeNodeEx(Label.c_str(), NodeFlags))
			{
				for (int i = 0; i < Vec.size(); i++)
				{
					ItemFunc(Vec[i]);
				}
				ImGui::TreePop();
			}

		}
	};
}