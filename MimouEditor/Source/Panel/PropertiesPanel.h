#pragma once
#include "Panel.h"

namespace Mimou
{
	class PropertiesPanel : public Panel
	{
	public:
		PropertiesPanel(const std::string& PanelName, const Ref<Scene>& Scene);

		virtual void OnImGUIUpdate() override;


	private:

		void ShowTagComponent();

		void ShowTransformComponent();

	private:
		Ref<GameObject> SelectedObject;
	};
}