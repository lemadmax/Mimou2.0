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
			glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f));

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
		float m_FOV = 70.0f;
		float m_Aspect = 1.5f;
		glm::vec3 EulerAngles = glm::vec3(0.0f);
		glm::vec3 m_CameraPosition = glm::vec3(0.0f);

		PerspectiveCamera m_PerspectiveCamera;


		float m_zNear = 0.1f, m_zFar = 100.0f;
		float MoveSpeed = 1;
		float RotateSpeed = 7;
		bool bIsMousePressMoving = false;
		std::pair<float, float> MousePosition;

		float TestTime = 0.0f;
	};
}
