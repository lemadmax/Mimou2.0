#include "mepch.h"
#include "SceneCamera.h"

#include "glm/ext.hpp"

namespace Mimou
{
	IMPLEMENT_ME_CLASS(SceneCamera)

	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	SceneCamera::~SceneCamera()
	{

	}

	void SceneCamera::SetProjectionPersp(float FOV, float Aspect, float zNear, float zFar)
	{
		m_FOV = FOV;
		m_Aspect = Aspect;
		m_zNear = zNear;
		m_zFar = zFar;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		m_Projection = glm::perspective<float>(m_FOV, m_Aspect, 0.1f, 100.0f);
	}

}