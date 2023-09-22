#include "mepch.h"
#include "Transform.h"

#include "glm/gtx/matrix_decompose.hpp"

namespace Mimou
{

	Transform::Transform()
	{
		m_Translation = glm::vec3(1.0f);
		m_Rotation = glm::vec3(0.0f);
		m_Scale = glm::vec3(1.0f);
	}

	Transform::Transform(const glm::vec3& Translation, const glm::vec3& Rotation, const glm::vec3& Scale)
		: m_Translation(Translation), m_Rotation(Rotation), m_Scale(Scale)
	{
		RecalculateMatrix();
	}

	Transform::Transform(const glm::mat4& Matrix)
	{
		glm::vec3 Scale;
		glm::quat Rotation;
		glm::vec3 Translation;
		glm::vec3 Skew;
		glm::vec4 Perspective;
		glm::decompose(Matrix, Scale, Rotation, Translation, Skew, Perspective);
		m_Translation = Translation;
		m_Rotation = glm::eulerAngles(glm::conjugate(Rotation));
		m_Scale = Scale;
	}

	void Transform::SetTranslation(const glm::vec3& Translation)
	{
		m_Translation = Translation;
		RecalculateMatrix();
	}

	void Transform::SetRotation(const glm::vec3& Rotation)
	{
		m_Rotation = Rotation;
		RecalculateMatrix();
	}

	void Transform::SetScale(const glm::vec3& Scale)
	{
		m_Scale = Scale;
		RecalculateMatrix();
	}

	glm::quat Transform::GetQuaternion()
	{
		return glm::quat(m_Rotation);
	}

	void Transform::RecalculateMatrix()
	{
		m_Matrix = glm::translate(m_Translation) * glm::rotate(0.0f, m_Rotation) * glm::scale(m_Scale);
	}

}