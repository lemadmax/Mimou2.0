#include "mepch.h"
#include "EditorCamera.h"
#include "Mimou/Input.h"

#include "glm/ext.hpp"

namespace Mimou
{
	EditorCamera::EditorCamera(float FOV, float Aspect, float NearClip, float FarClip,
		const glm::vec3& Position = { 0.0f, 0.0f, 10.0f },
		const glm::vec3& LookAt = { 0.0f, 0.0f, 0.0f },
		const glm::vec3& CameraUp = { 0.0f, 1.0f, 0.0f })
		: m_FOV(FOV), m_AspectRatio(Aspect), m_Near(NearClip), m_Far(FarClip)
	{
		RecalculateProjection();
		RecalculateView();
	}

	const glm::mat4& EditorCamera::GetViewProjection() const
	{
		return m_Projection * m_ViewMatrix;
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
			Position -= ActualMoveSpeed * Ts.GetSecond() * CameraForward;
		}
		if (Input::IsKeyPressed(Key::S))
		{
			Position += ActualMoveSpeed * Ts.GetSecond() * CameraForward;
		}
		if (Input::IsMouseButtonPressed(Mouse::LeftButton))
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

					LookAt.x = glm::cos(CameraPitch) * glm::sin(CameraYaw);
					LookAt.y = glm::sin(CameraPitch);
					LookAt.z = glm::cos(CameraPitch) * glm::cos(CameraYaw);
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
