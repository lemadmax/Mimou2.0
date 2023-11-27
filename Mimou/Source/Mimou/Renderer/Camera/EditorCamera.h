#pragma once
#include "Camera.h"
#include "Mimou/Timestep.h"

#include "glm/glm.hpp"

namespace Mimou
{
	class EditorCamera : public Camera
	{
	public:
		EditorCamera() = default;
		EditorCamera(const EditorCamera&) = default;
		EditorCamera(float FOV, float Aspect, float NearClip, float FarClip, 
			const glm::vec3& Position = { 0.0f, 1.0f, 1.0f },
			const glm::vec3& LookAt = { 0.0f, 0.0f, 0.0f },
			const glm::vec3& CameraUp = { 0.0f, 1.0f, 0.0f }
			);

		const glm::mat4& GetViewProjection() const;
		const glm::mat4& GetViewMatrix() const;

		void OnUpdate(Timestep Ts);

		inline float GetAspect() const { return m_AspectRatio; }
		inline void SetAspect(float Aspect) { m_AspectRatio = Aspect; RecalculateProjection(); }
		
		inline float GetZNear() const { return m_Near; }
		inline float GetZFar() const { return m_Far; }


	private:
		void RecalculateProjection();
		void RecalculateView();
		
	private:
		glm::mat4 m_ViewMatrix;

		float m_FOV = 70.0f, m_Near = 0.01f, m_Far = 100.0f;
		float m_AspectRatio = 1.5f;
		glm::vec3 Position = { 0.5f, 0.5f, 0.5f };
		glm::vec3 LookAt = { 0.0f, 0.0f, 0.0f };
		glm::vec3 CameraUp = { 0.0f, 1.0f, 0.0f };

		float m_Pitch = 0.0f, m_Yaw = 0.0f;

		float MoveSpeed = 1.0f, RotateSpeed = 1.0f;
		bool bIsMouseDragging = false;
		std::pair<float, float> PrevMousePos = { 0.0f, 0.0f };
	};
}