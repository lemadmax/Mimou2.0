#pragma once
#include "Panel.h"

namespace Mimou
{
	class SceneHierarchyPanel : public Panel
	{
	public:
		SceneHierarchyPanel(const std::string PanelName = "Default Panel", const Ref<Scene>& Scene = nullptr);

		virtual void OnImGUIUpdate() override;
		
	private:

	};
}