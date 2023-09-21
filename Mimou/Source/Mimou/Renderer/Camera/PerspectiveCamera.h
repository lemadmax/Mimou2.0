#pragma once
#include "Camera.h"

namespace Mimou
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera();
		PerspectiveCamera(float FOV, float Aspect, glm::vec3 Position, glm::vec3 LookAt, glm::vec3 CameraUp);

		void SetProjection(float FOV, float Aspect, float zNear, float zFar);

		inline void SetLookAt(const glm::vec3& LookAt) { m_LookAt = LookAt; RecalculateViewMatrix(); }
		inline void SetCameraUp(const glm::vec3& CameraUp) { m_CameraUp = CameraUp; RecalculateViewMatrix(); }
		glm::vec3 GetLookAt() const { return m_LookAt; }
		glm::vec3 GetCameraUp() const { return m_CameraUp; }
		glm::vec3 GetCameraForward() const { return m_LookAt - m_Position; }
		glm::vec3 GetCameraRight() const { return glm::cross(GetCameraForward(), m_CameraUp); }
		
	private:
		virtual void RecalculateViewMatrix() override;

	private:
		float m_FOV = 70.0f;
		float m_Aspect = 1.5f;
		glm::vec3 m_LookAt = glm::vec3(0.0f);
		glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	};
}