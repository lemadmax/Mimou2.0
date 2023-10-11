#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#define MARK_DIRTY(x) { IsDirty = x; }

namespace Mimou
{
	class Transform
	{
	public:
		Transform();
		Transform(const glm::vec3& Translation, const glm::vec3& Rotation, const glm::vec3& Scale);
		Transform(const glm::mat4& Matrix);

		glm::mat4 GetTransformMatrix();

		inline glm::vec3 Position() const { return m_Translation; }
		inline glm::vec3 Translation() const { return m_Translation; }
		inline glm::vec3 Rotation() const { return m_Rotation; }
		inline glm::vec3 Scale() const { return m_Scale; }

		inline void SetPosition(glm::vec3 Position) { m_Translation = Position; MARK_DIRTY(true) }
		inline void SetTranslation(const glm::vec3& Translation) { m_Translation = Translation; MARK_DIRTY(true) }
		inline void SetRotation(const glm::vec3& Rotation) { m_Rotation = Rotation; MARK_DIRTY(true) }
		inline void SetScale(const glm::vec3& Scale) { m_Scale = Scale; MARK_DIRTY(true) }

		inline void SetPitch(float Pitch) { m_Rotation.x = Pitch; MARK_DIRTY(true) }
		inline void SetYaw(float Yaw) { m_Rotation.y = Yaw; MARK_DIRTY(true) }
		inline void SetRoll(float Roll) { m_Rotation.z = Roll; MARK_DIRTY(true) }

		inline float GetPitch() const { return m_Rotation.x; }
		inline float GetYaw() const { return m_Rotation.y; }
		inline float GetRoll() const { return m_Rotation.z; }

		glm::vec3 GetForward();
		glm::vec3 GetLeft();
		glm::vec3 GetUp();

		glm::quat GetQuaternion();

		void DebugPrint();

	private:
		glm::vec3 m_Translation;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
		glm::mat4 m_Matrix;

		bool IsDirty;
	};
}