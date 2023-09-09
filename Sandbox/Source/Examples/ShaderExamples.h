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
	Reference<Shader> SunShader;
	Reference<VertexArray> SunVertices;


	Reference<Shader> SphereShader;
	Reference<VertexArray> SphereVertices;
};