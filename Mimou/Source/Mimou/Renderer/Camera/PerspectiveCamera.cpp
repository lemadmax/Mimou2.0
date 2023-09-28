#include "mepch.h"
#include "PerspectiveCamera.h"

#include "glm/ext.hpp"

namespace Mimou
{
	PerspectiveCamera::PerspectiveCamera()
	{

	}

	PerspectiveCamera::PerspectiveCamera(float FOV, float Aspect, const glm::vec3& Position, const glm::vec3& Rotation)
		: m_FOV(FOV), m_Aspect(Aspect), GameObject(Transform(Position, Rotation, glm::vec3(1.0)))
	{
		m_ProjectionMatrix = glm::perspective<float>(FOV, Aspect, 0.1f, 100.0f);
	}

	PerspectiveCamera::PerspectiveCamera(float FOV, float Aspect, const Transform& Transform)
		: m_FOV(FOV), m_Aspect(Aspect), GameObject(Transform)
	{
		m_ProjectionMatrix = glm::perspective<float>(FOV, Aspect, 0.1f, 100.0f);
	}

	const glm::mat4& PerspectiveCamera::GetProjectionMatrix()
	{
		return m_ProjectionMatrix;
	}

	const glm::mat4& PerspectiveCamera::GetViewMatrix()
	{
		glm::mat4 TransformMatrix = m_Transform.GetTransform();
		m_ViewMatrix = glm::inverse(TransformMatrix);
		return m_ViewMatrix;
	}

	const glm::mat4& PerspectiveCamera::GetViewProjectionMatrix()
	{
		glm::mat4 View = GetViewMatrix();
		glm::mat4 Projection = GetProjectionMatrix();
		m_ViewProjectionMatrix = Projection * View;
		return m_ViewProjectionMatrix;
	}

	void PerspectiveCamera::SetProjection(float FOV, float Aspect, float zNear, float zFar)
	{
		m_FOV = FOV;
		m_Aspect = Aspect;
		m_zNear = zNear;
		m_zFar = zFar;
		m_ProjectionMatrix = glm::perspective<float>(FOV, Aspect, 0.1f, 100.0f);
	}
}