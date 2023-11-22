#pragma once
#include "Mimou/ECS/Entity/GameObject.h"
#include "glm/glm.hpp"

namespace Mimou
{
	class Light
	{
	public:
		Light(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Color, float Intensity);

		inline glm::vec3 GetColor() const { return m_Color; }
		inline float GetIntensity() const { return m_Intensity; }

		//glm::vec3 GetPosition();
		//glm::vec3 GetDirection();

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Color;

		float m_Intensity;
	};
}