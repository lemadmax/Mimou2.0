#pragma once
#include "Panel.h"

namespace Mimou
{
	class SceneHierarchyPanel : public Panel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const std::string& PanelName = "Default Panel");
		virtual ~SceneHierarchyPanel() {}

		virtual void OnImGUIUpdate() override;

		void ShowGameObject(Ref<GameObject> GB);

		Ref<GameObject> GetSelectedObject();

	private:
		void OpenRightClickPopup(Ref<GameObject> GB);
		
	private:

		Ref<GameObject> SelectedObject;

		std::vector<Ref<GameObject>> PendingDestroy;
		bool bDestroyAll = false;
	};
}