#include "mepch.h"
#include "PerspectiveCameraController.h"

namespace Mimou
{
	PerspectiveCameraController::PerspectiveCameraController()
	{
	}

	PerspectiveCameraController::PerspectiveCameraController(float FOV, float Aspect, glm::vec3 Position, glm::vec3 LookAt, glm::vec3 CameraUp)
		: m_FOV(FOV), m_Aspect(Aspect), m_PerspectiveCamera(FOV, Aspect, Position, LookAt, CameraUp)
	{
	}

	void PerspectiveCameraController::SetFOV(float FOV)
	{
		m_FOV = FOV;
		m_PerspectiveCamera.SetProjection(m_FOV, m_Aspect, m_zNear, m_zFar);
	}

	void PerspectiveCameraController::SetAspect(float Aspect)
	{
		m_Aspect = Aspect;
		m_PerspectiveCamera.SetProjection(m_FOV, m_Aspect, m_zNear, m_zFar);
	}

	void PerspectiveCameraController::OnUpdate(Timestep Ts)
	{
		//glm::vec3 CameraPos = m_PerspectiveCamera.GetPosition();
		//TestTime += Ts.GetSecond();
		//CameraPos = glm::vec3(5.0 * glm::sin(TestTime), 0.0f, 5.0 * glm::cos(TestTime));
		//ME_LOG("Camera Position: ({},{},{})", CameraPos.x, CameraPos.y, CameraPos.z);
		//m_PerspectiveCamera.SetPosition(CameraPos);
	}

	void PerspectiveCameraController::OnEvent(EventBase& Event)
	{
	}

	void PerspectiveCameraController::OnResize(float Width, float Height)
	{
	}
	bool PerspectiveCameraController::OnMouseScrolled(MouseScrollEvent& Event)
	{
		return false;
	}
	bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent& Event)
	{
		return false;
	}
}