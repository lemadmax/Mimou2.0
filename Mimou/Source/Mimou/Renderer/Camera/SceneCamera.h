#pragma once
#include "Camera.h"

namespace Mimou
{
	class SceneCamera : public Camera
	{
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

	private:

		float m_FOV = 70.0f;
		float m_Aspect = 1.5f;
		float m_zNear = 0.1f, m_zFar = 100.0f;
	};
}