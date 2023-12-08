#pragma once
#include "Mimou.h"

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
		Panel() = delete;
		Panel(PanelType Type, const std::string& PanelName, const Ref<Scene>& Scene);
		virtual ~Panel() = default;

		virtual void OnImGUIUpdate();

		static Ref<Panel> CreatePanel(PanelType Type, const std::string& PanelName, const Ref<Scene>& Scene);
		
	protected:
		Ref<Scene> m_Scene;

		PanelType m_Type;
		std::string m_PanelName;
	};
}