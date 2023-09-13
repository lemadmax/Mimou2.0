#include "mepch.h"
#include "PerspectiveCamera.h"

#include "glm/ext.hpp"

namespace Mimou
{
	PerspectiveCamera::PerspectiveCamera()
	{

	}

	PerspectiveCamera::PerspectiveCamera(float FOV, float Aspect, glm::vec3 Position, glm::vec3 LookAt, glm::vec3 CameraUp)
		: m_FOV(FOV), m_Aspect(Aspect), m_Position(Position), m_LookAt(LookAt), m_CameraUp(CameraUp)
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_LookAt, m_CameraUp);
		m_ProjectionMatrix = glm::perspective<float>(FOV, Aspect, 0.1f, 100.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::SetProjection(float FOV, float Aspect, float zNear, float zFar)
	{
		m_ProjectionMatrix = glm::perspective<float>(FOV, Aspect, zNear, zFar);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_LookAt, m_CameraUp);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}