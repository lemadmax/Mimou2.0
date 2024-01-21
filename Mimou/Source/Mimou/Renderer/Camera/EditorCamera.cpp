#include "mepch.h"
#include "EditorCamera.h"
#include "Mimou/Input.h"

#include "glm/ext.hpp"

namespace Mimou
{
	EditorCamera::EditorCamera(float FOV, float Aspect, float NearClip, float FarClip,
		const glm::vec3& Position,
		const glm::vec3& LookAt,
		const glm::vec3& CameraUp)
		: m_FOV(FOV), m_AspectRatio(Aspect), m_Near(NearClip), m_Far(FarClip)
	{
		RecalculateProjection();
		RecalculateView();
	}

	const glm::mat4& EditorCamera::GetViewProjection() const
	{
		return m_Projection * m_ViewMatrix;
	}

	const glm::mat4& EditorCamera::GetViewMatrix() const
	{
		return m_ViewMatrix;
	}

	void EditorCamera::OnUpdate(Timestep Ts)
	{
		glm::vec3 CameraForward = glm::normalize(LookAt - Position);
		glm::vec3 CameraLeft = glm::cross(CameraForward, CameraUp);
		float ActualMoveSpeed = MoveSpeed;
		if (Input::IsKeyPressed(Key::LeftShift))
		{
			ActualMoveSpeed = MoveSpeed * 5;
		}
		if (Input::IsKeyPressed(Key::A))
		{
			Position -= ActualMoveSpeed * Ts.GetSecond() * CameraLeft;
		}
		if (Input::IsKeyPressed(Key::D))
		{
			Position += ActualMoveSpeed * Ts.GetSecond() * CameraLeft;
		}
		if (Input::IsKeyPressed(Key::W))
		{
			Position += ActualMoveSpeed * Ts.GetSecond() * CameraForward;
		}
		if (Input::IsKeyPressed(Key::S))
		{
			Position -= ActualMoveSpeed * Ts.GetSecond() * CameraForward;
		}
		if (Input::IsMouseButtonPressed(Mouse::RightButton))
		{
			std::pair<float, float> CurMousePosition = Input::GetMousePosition();
			if (!bIsMouseDragging)
			{
				bIsMouseDragging = true;
			}
			else
			{
				if (CurMousePosition != PrevMousePos)
				{
					float OffsetX = CurMousePosition.first - PrevMousePos.first;
					float OffsetY = CurMousePosition.second - PrevMousePos.second;

					float CameraPitch = glm::asin(CameraForward.y);
					float CameraYaw = glm::atan(CameraForward.x, CameraForward.z);
					CameraPitch -= OffsetY * RotateSpeed * Ts.GetSecond();
					CameraYaw -= OffsetX * RotateSpeed * Ts.GetSecond();

					CameraPitch = std::min(CameraPitch, glm::half_pi<float>() - 0.1f);
					CameraPitch = std::max(CameraPitch, -glm::half_pi<float>() + 0.1f);

					CameraForward.x = glm::cos(CameraPitch) * glm::sin(CameraYaw);
					CameraForward.y = CameraLeft.y = glm::sin(CameraPitch);
					CameraForward.z = CameraLeft.x = glm::cos(CameraPitch) * glm::cos(CameraYaw);

					CameraLeft.x = -glm::cos(CameraYaw);
					CameraLeft.y = 0;
					CameraLeft.z = glm::sin(CameraYaw);

					//glm::rotate
					//LookAt = Position + CameraForward;
				}
			}
			PrevMousePos = CurMousePosition;
		}
		else
		{
			bIsMouseDragging = false;
		}

		if (Input::IsMouseButtonPressed(Mouse::RightButton))
		{
		}

		if (Input::IsMouseButtonReleased(Mouse::RightButton))
		{
		}

		LookAt = Position + CameraForward;
		CameraUp = glm::cross(CameraLeft, CameraForward);
		RecalculateView();
	}

	void EditorCamera::RecalculateProjection()
	{
		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_Near, m_Far);
	}

	void EditorCamera::RecalculateView()
	{
		m_ViewMatrix = glm::lookAt(Position, LookAt, CameraUp);
	}
}
