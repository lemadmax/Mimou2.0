#include "PropertiesPanel.h"
#include "SceneHierarchyPanel.h"

#include "Layer/EditorLayer.h"

namespace Mimou
{
	//extern void DrawVec3Control(const std::string& Label, glm::vec3& Values);
	PropertiesPanel::PropertiesPanel(const std::string& PanelName)
		: Panel(PanelType::PropertiesPanel, PanelName)
	{

	}

	void PropertiesPanel::OnImGUIUpdate()
	{
		m_Scene = EditorLayer::GetInstance()->GetActiveScene();

		Ref<SceneHierarchyPanel> SceneHierPanel = std::static_pointer_cast<SceneHierarchyPanel>(EditorLayer::GetInstance()->GetPanel(PanelType::SceneHierarchyPanel));
		if (!SceneHierPanel) return;

		SelectedObject = SceneHierPanel->GetSelectedObject();

		bool pOpen = true;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(300.0f, 500.0f));

		if (!m_Scene)
		{
			ImGui::Begin("Empty");
			ImGui::End();
			ImGui::PopStyleVar(1);
			return;
		}

		ImGui::Begin(m_PanelName.c_str());


		if (!SelectedObject)
		{
			ImGui::End();
			ImGui::PopStyleVar(1);
			return;
		}

		if (ImGui::BeginPopup("Add Component Popup"))
		{

			ImGui::SeparatorText("Compnents");

			SHOW_SELECT_ADD_COMPONENT(CameraComponent, SelectedObject)
			SHOW_SELECT_ADD_COMPONENT(StaticMeshComponent, SelectedObject)
			SHOW_SELECT_ADD_COMPONENT(LightComponent, SelectedObject)
			SHOW_SELECT_ADD_COMPONENT(TransformComponent, SelectedObject)

			ImGui::EndPopup();
		}

		TagComponent* TagComp = SelectedObject->TryGetComponent<TagComponent>();
		if (TagComp)
		{
			char Buffer[256];
			memset(Buffer, 0, sizeof(Buffer));
			strcpy_s(Buffer, sizeof(Buffer), TagComp->Tag.c_str());
			float ItemWidth = ImGui::CalcItemWidth();
			ImGui::PushItemWidth(ItemWidth * 2.0f / 3.0f);
			if (ImGui::InputText("##Tag", Buffer, sizeof(Buffer)))
			{
				TagComp->Tag = std::string(Buffer);
			}
			ImGui::PopItemWidth();
			ImGui::PushItemWidth(ItemWidth / 3.0f);
			ImGui::SameLine();
			if (ImGui::Button("Add Component"))
			{
				ImGui::OpenPopup("Add Component Popup");
			}
			ImGui::PopItemWidth();
		}

		ImGui::Separator();

		ShowComponent<TransformComponent>("Transform Component", [&](TransformComponent* Transform) {
			ImGuiTreeNodeFlags NodeFlags = ImGuiTreeNodeFlags_DefaultOpen
				| ImGuiTreeNodeFlags_OpenOnArrow
				| ImGuiTreeNodeFlags_OpenOnDoubleClick;

			if (ImGui::TreeNodeEx("Transform", NodeFlags))
			{
				ImGui::Spacing();

				PanelUtilities::DrawVec3Control("Translation:", Transform->Translation);
				ImGui::Spacing();
					
				PanelUtilities::DrawVec3Control("Rotation:", Transform->Rotation);
				ImGui::Spacing();

				PanelUtilities::DrawVec3Control("Scale:", Transform->Scale);
				ImGui::Spacing();

				ImGui::TreePop();
			}
			});

		ShowComponent<CameraComponent>("Camera", [&](CameraComponent* Camera) {
			Ref<SceneCamera> CameraInst = Camera->Camera;
			ImGui::Spacing();
			ImGui::Checkbox("Is Primiary", &Camera->IsPrimary);
			ImGui::Spacing();

			float FOV = CameraInst->GetFOV();
			if (ImGui::InputFloat("FOV", &FOV))
			{
				CameraInst->SetFOV(FOV);
			}
			ImGui::Spacing();

			ImGui::PushItemWidth(80.0f);

			float zFar = CameraInst->GetZFar();
			float zNear = CameraInst->GetZNear();
			bool zFarChanged = ImGui::DragFloat("Clip far", &zFar);
			ImGui::SameLine();
			bool zNearChanged = ImGui::DragFloat("Clip near", &zNear);

			if (zFarChanged || zNearChanged)
			{
				CameraInst->SetClipDistance(zFar, zNear);
			}

			ImGui::PopItemWidth();

			ImGui::Spacing();
			});

		ShowComponent<LightComponent>("Light", [&](LightComponent* Light) {
			ImGui::Spacing();
			ImGui::Checkbox("Is on", &Light->IsOn);
			ImGui::Spacing();

			//PanelUtilities::DrawVec3Control("Light color", Light->Color, "RGB");
			//ImGui::Spacing();

			ImGui::DragFloat("Intensity", &Light->Intensity, 0.1f, 0.0f, 120.0f, "%.1f");

			ImGui::Spacing();
			});

		ShowComponent<StaticMeshComponent>("Static Mesh", [&](StaticMeshComponent* StaticMesh) {
			ImGui::Spacing();

			int CurrentIdx = 0;
			std::vector<std::string> MeshNames = StaticMeshLibrary::Get()->GetAvaliableAssets(StaticMesh->AssetName, CurrentIdx);
			if (PanelUtilities::DrawComboFromVector("Mesh Asset", MeshNames, &CurrentIdx))
			{ 
				StaticMesh->AssetName = MeshNames[CurrentIdx];
			}

			ImGui::Spacing();
			PanelUtilities::DrawDynamicVector("Material Slots", StaticMesh->MaterialSlots, [&](Ref<Material>& Mat) {
				ImGui::Spacing();
				
				int CurMatIdx = 0;
				std::vector<std::string> MatNames = MaterialLibrary::Get()->GetNames(Mat->GetName(), CurMatIdx);
				if (PanelUtilities::DrawComboFromVector("Material Instance", MatNames, &CurMatIdx))
				{
					Mat = MaterialLibrary::Get()->GetMaterial(MatNames[CurMatIdx]);
				}

				ImGuiColorEditFlags MiscFlags = ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoLabel;
				float Ambient[4] = { Mat->m_Ambient.x, Mat->m_Ambient.y, Mat->m_Ambient.z, Mat->m_Ambient.w };
				if (ImGui::ColorEdit4("Ambient", Ambient, MiscFlags))
				{
					Mat->m_Ambient = glm::vec4(Ambient[0], Ambient[1] , Ambient[2], Ambient[3]);
				}
				float Diffuse[4] = { Mat->m_Diffuse.x, Mat->m_Diffuse.y, Mat->m_Diffuse.z, Mat->m_Diffuse.w };
				if (ImGui::ColorEdit4("Diffuse", Diffuse, MiscFlags))
				{
					Mat->m_Diffuse = glm::vec4(Diffuse[0], Diffuse[1], Diffuse[2], Diffuse[3]);
				}float Specular[4] = { Mat->m_Specular.x, Mat->m_Specular.y, Mat->m_Specular.z, Mat->m_Specular.w };
				if (ImGui::ColorEdit4("Specular", Specular, MiscFlags))
				{
					Mat->m_Specular = glm::vec4(Specular[0], Specular[1], Specular[2], Specular[3]);
				}

				ImGui::DragFloat("Transparency", &Mat->m_Transparency, 0.01f, 0.0f, 1.0f, "%.3f");
				ImGui::DragFloat("IrradiPerp", &Mat->m_IrradiPerp, 0.01f, 0.0f, 1.0f, "%.3f");

				ImGui::Spacing();

				});
			ImGui::Spacing();
			});
		
		ImGui::End();
		ImGui::PopStyleVar(1);
	}

	void PropertiesPanel::ShowMaterial(Ref<Material> Mat)
	{

	}
}