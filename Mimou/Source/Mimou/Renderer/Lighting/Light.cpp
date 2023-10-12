#include "mepch.h"
#include "Light.h"

namespace Mimou
{
	Light::Light(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Color, float Intensity)
		: m_Position(Position), m_Color(Color), m_Intensity(Intensity)
	{
		m_Transform.SetPosition(Position);
		m_Transform.SetRotation(Rotation);
	}

	glm::vec3 Light::GetPosition()
	{
		return m_Transform.Translation();
	}

	glm::vec3 Light::GetDirection()
	{
		return m_Transform.GetForward();
	}
}