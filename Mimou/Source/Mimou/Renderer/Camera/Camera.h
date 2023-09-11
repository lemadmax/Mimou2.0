#pragma once
#include "glm/glm.hpp"

namespace Mimou
{
	class Camera
	{
	public:

		virtual const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		virtual const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		virtual const glm::mat4& GetViewProjectionMatix() const { return m_ViewProjectionMatrix; }

		virtual const glm::vec3& GetPosition() const { return m_Position; }
		virtual float GetRotation() const { return m_Rotation; }

		virtual void SetPosition(const glm::vec3& Position) { m_Position = Position; RecalculateViewMatrix(); }
		virtual void SetRotation(float Rotation) { m_Rotation = Rotation, RecalculateViewMatrix(); }

	protected:
		virtual void RecalculateViewMatrix() = 0;

	protected:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};
}