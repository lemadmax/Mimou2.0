#pragma once
#include "Mimou.h"

class ShaderEgLayer : Layer
{
public:
	ShaderEgLayer();

	~ShaderEgLayer();

	virtual void OnUpdate(Timestep Ts) override;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnImGUIRender() override;
	virtual void OnEvent(EventBase& Event) override;
private:
	Reference<Shader> SunShader;
};