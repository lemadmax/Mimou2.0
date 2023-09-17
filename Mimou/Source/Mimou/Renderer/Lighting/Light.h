#pragma once
#include "glm/glm.hpp"

namespace Mimou
{
	class Light
	{
	public:
		Light(glm::vec3 Position, glm::vec3 Color, glm::vec3 Direction, float Intensity);

		inline glm::vec3 GetPosition() const { return m_Position; }
		inline glm::vec3 GetColor() const { return m_Color; }
		inline glm::vec3 GetDirection() const { return m_Direction; }
		inline float GetIntensity() const { return m_Intensity; }

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Color;
		glm::vec3 m_Direction;

		float m_Intensity;
	};
}