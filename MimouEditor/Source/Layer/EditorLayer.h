#pragma once
#include "Mimou.h"

class EditorLayer : public Layer
{
public:
	EditorLayer();

	~EditorLayer();

	virtual void OnUpdate(Timestep Ts) override;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnImGUIRender() override;
	virtual void OnEvent(EventBase& Event) override;

private:
	void ShowMenuBar();
	void ShowViewport();
	void ShowSettingPanel();

private:
	float uTime = 0.0f;

	Ref<FrameBuffer> m_FrameBuffer;

	Ref<VertexArray> EditorGridVA;
	Ref<Shader> EditorGridShader;


	Ref<Shader> SphereShader;
	Ref<VertexArray> SphereVertices;

	Ref<StaticMesh> SphereMesh;
	Ref<Light> DirectionalLight;
	Ref<Light> MovingLight;

	std::vector<Ref<GameObject>> GameObjects;

	PerspectiveCameraController m_CameraController;

	bool m_IsViewportFocused;
	bool m_IsViewportHovered;
	glm::vec2 m_ViewportSize;
	Ref<Texture> m_TestTexture;

private:
	// temporary variables
	float TmpColor[3];
};