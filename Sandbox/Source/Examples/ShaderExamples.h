#pragma once
#include "Mimou.h"

class ShaderEgLayer : public Layer
{
public:
	ShaderEgLayer();

	~ShaderEgLayer();

	virtual void OnUpdate(Timestep Ts) override;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnImGUIRender() override;
	virtual void OnEvent(EventBase& Event) override;

	void TestSun();
private:
	float uTime = 0.0f;
	Ref<Shader> SunShader;
	Ref<VertexArray> SunVertices;

	Ref<VertexArray> EditorGridVA;
	Ref<Shader> EditorGridShader;


	Ref<Shader> SphereShader;
	Ref<VertexArray> SphereVertices;

	Ref<StaticMesh> SphereMesh;
	Ref<Light> DirectionalLight;
	Ref<Light> MovingLight;

	std::vector<Ref<GameObject>> GameObjects;

	PerspectiveCameraController m_CameraController;
};