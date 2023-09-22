#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

namespace Mimou
{
	class Transform
	{
	public:
		Transform();
		Transform(const glm::vec3& Translation, const glm::vec3& Rotation, const glm::vec3& Scale);
		Transform(const glm::mat4& Matrix);

		inline glm::vec3 Position() const { return m_Translation; }
		inline glm::vec3 Rotation() const { return m_Rotation; }
		inline glm::vec3 Scale() const { return m_Scale; }

		void SetTranslation(const glm::vec3& m_Translation);
		void SetRotation(const glm::vec3& Rotation);
		void SetScale(const glm::vec3& Scale);

		glm::quat GetQuaternion();

	private:
		void RecalculateMatrix();

	private:
		glm::vec3 m_Translation;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
		glm::mat4 m_Matrix;
	};
}