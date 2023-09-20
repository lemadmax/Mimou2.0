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
	Ref<Shader> SunShader;
	Ref<VertexArray> SunVertices;


	Ref<Shader> SphereShader;
	Ref<VertexArray> SphereVertices;

	Ref<StaticMesh> SphereMesh;
	Ref<Light> DirectionalLight;

	PerspectiveCameraController m_CameraController;
};