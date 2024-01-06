#pragma once
#include "Mimou/ECS/MEObject.h"
#include "glm/glm.hpp"

namespace Mimou
{
	class Camera : public MEObject
	{
		DECLARE_ME_CLASS(Camera)
	public:
		Camera() = default;
		Camera(const glm::mat4& Projection)
			: m_Projection(Projection) {}
		virtual ~Camera() = default;

		const glm::mat4& GetProjection() const { return m_Projection; }
	protected:
		glm::mat4 m_Projection = glm::mat4(1.0f);
	};
}