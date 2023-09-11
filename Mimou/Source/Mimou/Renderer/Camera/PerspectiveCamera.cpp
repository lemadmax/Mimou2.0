#include "mepch.h"
#include "PerspectiveCamera.h"

#include "glm/ext.hpp"

namespace Mimou
{

	PerspectiveCamera::PerspectiveCamera(float FOV, float Aspect, glm::vec3 Position, glm::vec3 LookAt, glm::vec3 CameraUp)
		: m_FOV(FOV), m_Aspect(Aspect), m_Position(Position), m_LookAt(LookAt), m_CameraUp(CameraUp)
	{
	}

	void PerspectiveCamera::SetProjection(float FOV, float Aspect, float zNear, float zFar)
	{
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		//glm::mat4 LookAtMatrix
	}
}