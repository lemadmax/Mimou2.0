#pragma once
#include "PerspectiveCamera.h"
#include "Mimou/Timestep.h"
#include "Mimou/Event/AppEvent.h"
#include "Mimou/Event/MouseEvent.h"

namespace Mimou
{
	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController();
		PerspectiveCameraController(
			float FOV, 
			float Aspect, 
			glm::vec3 Position = glm::vec3(0.0f, 0.0f, 5.0f),
			glm::vec3 LookAt = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 CameraUp = glm::vec3(0.0f, 1.0f, 0.0f));

		void SetFOV(float FOV);
		void SetAspect(float Aspect);

		void OnUpdate(Timestep Ts);
		void OnEvent(EventBase& Event);

		void OnResize(float Width, float Height);

		PerspectiveCamera& GetCamera() { return m_PerspectiveCamera; }
		const PerspectiveCamera& GetCamera() const { return m_PerspectiveCamera; }

	private:
		bool OnMouseScrolled(MouseScrollEvent& Event);
		bool OnWindowResized(WindowResizeEvent& Event);

	private:
		float m_FOV;
		float m_Aspect;
		glm::vec3 EulerAngles = glm::vec3(0.0f);
		glm::vec3 m_CameraPosition;

		PerspectiveCamera m_PerspectiveCamera;


		float m_zNear = 0.1f, m_zFar = 100.0f;
		float MoveSpeed = 1;
		float RotateSpeed = 1;

		float TestTime = 0.0f;
	};
}
