#pragma once
#include "Camera.h"

namespace Mimou
{
	class SceneCamera : public Camera
	{
		DECLARE_ME_CLASS(SceneCamera)
	public:
		SceneCamera();
		~SceneCamera();

		void SetProjectionPersp(float FOV, float Aspect, float zNear, float zFar);

		inline void SetFOV(float FOV) { m_FOV = FOV; RecalculateProjection(); }
		inline void SetAspect(float Aspect) { m_Aspect = Aspect; RecalculateProjection(); }
		inline void SetClipDistance(float zNear, float zFar) { m_zNear = zNear; m_zFar = zFar; RecalculateProjection();}

		inline float GetFOV() const { return m_FOV; }
		inline float GetAspect() const { return m_Aspect; }
		inline float GetZNear() const { return m_zNear; }
		inline float GetZFar() const { return m_zFar; }

	private:
		void RecalculateProjection();

	public:

		ME_PROPERTY(m_FOV, MEPropType::FLOAT)
		float m_FOV = 70.0f;

		ME_PROPERTY(m_Aspect, MEPropType::FLOAT)
		float m_Aspect = 1.5f;

		ME_PROPERTY(m_zNear, MEPropType::FLOAT)
		float m_zNear = 0.1f;

		ME_PROPERTY(m_zFar, MEPropType::FLOAT)
		float m_zFar = 100.0f;
	};
}