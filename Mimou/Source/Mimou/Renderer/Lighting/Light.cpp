#include "mepch.h"
#include "Light.h"

namespace Mimou
{
	Light::Light(glm::vec3 Position, glm::vec3 Color, glm::vec3 Direction, float Intensity)
		: m_Position(Position), m_Color(Color), m_Direction(Direction), m_Intensity(Intensity)
	{

	}
}