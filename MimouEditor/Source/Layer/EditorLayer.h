#pragma once
#include "Mimou.h"
#include "Panel/Panel.h"

namespace Mimou
{

	class EditorLayer : public Layer
	{
	private:
		EditorLayer();

	public:
		~EditorLayer();

		static EditorLayer* GetInstance();

		virtual void OnUpdate(Timestep Ts) override;
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGUIRender() override;
		virtual void OnEvent(EventBase& Event) override;

		inline Ref<Scene> GetActiveScene() const { return m_ActiveScene; }

	public:
		bool IsPanelOpen(PanelType Type);
		Ref<Panel> GetPanel(PanelType Type);

	private:
		void ShowMenuBar();
		void ShowViewport();
		void ShowSettingPanel();

		void ShowPanel(PanelType Type, const std::string& PanelName);

		void ShowGizmo();
		void ShowGrid();

	private:
		void NewScene();
		void OpenScene();
		void SaveSceneAs();
		void SaveScene();

	private:
		float uTime = 0.0f;

		Ref<Scene> m_ActiveScene;

		Ref<FrameBuffer> m_FrameBuffer;

		Ref<VertexArray> EditorGridVA;
		Ref<Shader> EditorGridShader;


		Ref<Shader> SphereShader;
		Ref<VertexArray> SphereVertices;

		Ref<Light> DirectionalLight;
		Ref<Light> MovingLight;

		EditorCamera EditorCamera;

		bool m_IsViewportFocused;
		bool m_IsViewportHovered;
		glm::vec2 m_ViewportSize;
		glm::vec2 ViewportOffset;
		Ref<Texture> m_TestTexture;

		// UI Panels
		std::map<PanelType, Ref<Panel>> ActivePanels;
		std::map<PanelType, Ref<Panel>> CachedPanels;

		ImGuizmo::OPERATION m_GizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
		ImGuizmo::MODE m_GizmoMode = ImGuizmo::MODE::LOCAL;
		bool bIsSnapping = false;
		float Snap[3] = { 0.5f, 0.5f, 0.5f };

		bool m_ShowDepthPanel = false;

	private:
		// temporary variables
		float TmpColor[3];

		static EditorLayer* s_Instance;
	};
}