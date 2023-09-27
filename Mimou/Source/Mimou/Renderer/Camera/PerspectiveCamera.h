#pragma once
#include "Mimou/ECS/Entity/GameObject.h"

namespace Mimou
{
	class PerspectiveCamera : public GameObject
	{
	public:
		PerspectiveCamera();
		PerspectiveCamera(float FOV, float Aspect, const glm::vec3& Position, const glm::vec3& Rotation);
		PerspectiveCamera(float FOV, float Aspect, const Transform& Transform);

		const glm::mat4& GetProjectionMatrix();
		const glm::mat4& GetViewMatrix();
		const glm::mat4& GetViewProjectionMatrix();

		void SetProjection(float FOV, float Aspect, float zNear, float zFar);

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		float m_FOV = 70.0f;
		float m_Aspect = 1.5f;
		float m_zNear = 0.1f, m_zFar = 100.0f;
	};
}