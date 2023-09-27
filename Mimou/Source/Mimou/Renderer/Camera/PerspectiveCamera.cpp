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
		
	}

	PerspectiveCamera::PerspectiveCamera(float FOV, float Aspect, const Transform& Transform)
		: m_FOV(FOV), m_Aspect(Aspect), GameObject(Transform)
	{
		m_ProjectionMatrix = glm::perspective<float>(FOV, Aspect, 0.1f, 100.0f);
	}

	const glm::mat4& PerspectiveCamera::GetProjectionMatrix()
	{
		return glm::perspective<float>(m_FOV, m_Aspect, m_zNear, m_zFar);
	}

	const glm::mat4& PerspectiveCamera::GetViewMatrix()
	{
		glm::mat4 TransformMatrix = m_Transform.GetTransform();
		return glm::inverse(TransformMatrix);
	}

	const glm::mat4& PerspectiveCamera::GetViewProjectionMatrix()
	{
		//glm::mat4 View = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		//glm::mat4 Projection = glm::perspective<float>(m_FOV, m_Aspect, m_zNear, m_zFar);
		glm::mat4 View = GetViewMatrix();
		glm::mat4 Projection = GetProjectionMatrix();
		////return Projection * View;
		glm::mat4 ViewProjectionMatrix = Projection * View;
		return ViewProjectionMatrix;
		//m_ViewProjectionMatrix = GetProjectionMatrix() * GetViewMatrix();
		//return m_ViewProjectionMatrix;
		//return GetProjectionMatrix() * GetViewMatrix();
	}

	void PerspectiveCamera::SetProjection(float FOV, float Aspect, float zNear, float zFar)
	{
		m_FOV = FOV;
		m_Aspect = Aspect;
		m_zNear = zNear;
		m_zFar = zFar;
	}
}