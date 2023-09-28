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
		IsDirty = true;
	}

	Transform::Transform(const glm::vec3& Translation, const glm::vec3& Rotation, const glm::vec3& Scale)
		: m_Translation(Translation), m_Rotation(Rotation), m_Scale(Scale)
	{
		IsDirty = true;
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

	glm::mat4 Transform::GetTransform()
	{
		if (IsDirty)
		{
			m_Matrix = glm::translate(m_Translation) *
				glm::rotate(glm::radians(m_Rotation.z), glm::vec3(0, 0, 1)) *
				glm::rotate(glm::radians(m_Rotation.y), glm::vec3(0, 1, 0)) *
				glm::rotate(glm::radians(m_Rotation.x), glm::vec3(1, 0, 0)) *
				glm::scale(m_Scale);
		}
		return m_Matrix;
	}

	glm::vec3 Transform::GetForward()
	{
		if (IsDirty) GetTransform();
		return glm::vec3(m_Matrix[0][2], m_Matrix[1][2], m_Matrix[2][2]);
	}

	glm::vec3 Transform::GetLeft()
	{
		if (IsDirty) GetTransform();
		return glm::vec3(m_Matrix[0][0], m_Matrix[1][0], m_Matrix[2][0]);
	}

	glm::vec3 Transform::GetUp()
	{
		if (IsDirty) GetTransform();
		return glm::vec3(m_Matrix[0][1], m_Matrix[1][1], m_Matrix[2][1]);
	}

	glm::quat Transform::GetQuaternion()
	{
		return glm::quat(m_Rotation);
	}

}