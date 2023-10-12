#include "mepch.h"
#include "PerspectiveCameraController.h"
#include "Mimou/Event/MouseEvent.h"
#include "Mimou/Event/KeyEvent.h"
#include "Mimou/Event/KeyCodes.h"
#include "Mimou/Input.h"

namespace Mimou
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	PerspectiveCameraController::PerspectiveCameraController()
	{

	}

	PerspectiveCameraController::PerspectiveCameraController(float FOV, float Aspect, glm::vec3 Position, glm::vec3 Rotation)
		: m_FOV(FOV), m_Aspect(Aspect), m_CameraPosition(Position), m_PerspectiveCamera(FOV, Aspect, Position, Rotation)
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
		////ME_LOG("Camera Position: ({},{},{})", CameraPos.x, CameraPos.y, CameraPos.z);
		//m_PerspectiveCamera.SetPosition(CameraPos);
		if (Input::IsKeyPressed(Key::A))
		{
			glm::vec3 CameraPos = m_PerspectiveCamera.m_Transform.Position();
			glm::vec3 CameraLeft = m_PerspectiveCamera.m_Transform.GetLeft();
			CameraPos -= MoveSpeed * Ts.GetSecond() * CameraLeft;
			m_PerspectiveCamera.m_Transform.SetPosition(CameraPos);
		}
		if (Input::IsKeyPressed(Key::D))
		{
			glm::vec3 CameraPos = m_PerspectiveCamera.m_Transform.Position();
			glm::vec3 CameraLeft = m_PerspectiveCamera.m_Transform.GetLeft();
			CameraPos += MoveSpeed * Ts.GetSecond() * CameraLeft;
			m_PerspectiveCamera.m_Transform.SetPosition(CameraPos);
		}
		if (Input::IsKeyPressed(Key::W))
		{
			glm::vec3 CameraPos = m_PerspectiveCamera.m_Transform.Position();
			glm::vec3 Forward = m_PerspectiveCamera.m_Transform.GetForward();
			CameraPos -= MoveSpeed * Ts.GetSecond() * Forward;
			m_PerspectiveCamera.m_Transform.SetPosition(CameraPos);
		}
		if (Input::IsKeyPressed(Key::S))
		{
			glm::vec3 CameraPos = m_PerspectiveCamera.m_Transform.Position();
			glm::vec3 Forward = m_PerspectiveCamera.m_Transform.GetForward();
			CameraPos += MoveSpeed * Ts.GetSecond() * Forward;
			m_PerspectiveCamera.m_Transform.SetPosition(CameraPos);
		}
		if (Input::IsMouseButtonPressed(Mouse::LeftButton))
		{
			std::pair<float, float> CurMousePosition = Input::GetMousePosition();
			if (!bIsMousePressMoving)
			{
				bIsMousePressMoving = true;
			}
			else
			{
				if (CurMousePosition != MousePosition)
				{
					float OffsetX = CurMousePosition.first - MousePosition.first;
					float OffsetY = CurMousePosition.second - MousePosition.second;
					float CameraPitch = m_PerspectiveCamera.m_Transform.GetPitch();
					float CameraYaw = m_PerspectiveCamera.m_Transform.GetYaw();
					CameraPitch -= OffsetY * RotateSpeed * Ts.GetSecond();
					CameraYaw -= OffsetX * RotateSpeed * Ts.GetSecond();
					m_PerspectiveCamera.m_Transform.SetPitch(CameraPitch);
					m_PerspectiveCamera.m_Transform.SetYaw(CameraYaw);
					//ME_ENGINE_LOG("Mouse press moving ({},{})", OffsetX, OffsetY);
					glm::vec3 CameraRot = m_PerspectiveCamera.m_Transform.Rotation();
					//ME_ENGINE_LOG("Camera rotation: ({},{},{})", CameraRot.x, CameraRot.y, CameraRot.z);
				}
			}
			MousePosition = CurMousePosition;
			//ME_ENGINE_LOG("Left mouse button pressed");
		}
		else
		{
			bIsMousePressMoving = false;
		}
		if (Input::IsMouseButtonPressed(Mouse::RightButton))
		{
			m_PerspectiveCamera.m_Transform.DebugPrint();
		}
		if (Input::IsMouseButtonReleased(Mouse::RightButton))
		{
		}

	}

	void PerspectiveCameraController::OnEvent(EventBase& Event)
	{
		EventDispatcher Dispatcher(Event);
		Dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(PerspectiveCameraController::OnWindowResized));
	}

	void PerspectiveCameraController::OnResize(float Width, float Height)
	{
		m_Aspect = Width / Height;
		m_PerspectiveCamera.SetProjection(m_FOV, m_Aspect, m_zNear, m_zFar);
	}

	bool PerspectiveCameraController::OnMouseScrolled(MouseScrollEvent& Event)
	{
		return false;
	}

	bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent& Event)
	{
		OnResize(Event.GetWidth(), Event.GetHeight());
		return true;
	}

}