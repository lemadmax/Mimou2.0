#pragma once
#include "Panel.h"

namespace Mimou
{
	class SceneHierarchyPanel : public Panel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const std::string& PanelName = "Default Panel", const Ref<Scene>& Scene = nullptr);
		virtual ~SceneHierarchyPanel() {}

		virtual void OnImGUIUpdate() override;

		void ShowGameObject(Ref<GameObject> GB);

		inline Ref<GameObject> GetSelectedObject() const { return SelectedObject; }
		
	private:

		Ref<GameObject> SelectedObject;
	};
}