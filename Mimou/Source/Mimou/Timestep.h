#pragma once

namespace Mimou
{
	class Timestep
	{
	public:
		Timestep(float Time = 0.0f) : m_Time(Time) {}

		operator float() const { return m_Time; }

		inline float GetSecond() const { return m_Time; }
		inline float GetMillisecond() const { return m_Time * 1000.f; }
	private:
		float m_Time;
	};
}