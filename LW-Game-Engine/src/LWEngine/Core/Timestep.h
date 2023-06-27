#pragma once

namespace LWEngine {

	class Timestep
	{
	public:
		Timestep(float time = 0.0f, float elapsedTime = 0.0f)
			: m_Time(time), m_ElapsedTime(elapsedTime)
		{
		}
		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMiliseconds() const { return m_Time * 1000.0f; }
		float GetElapsedTime() const { return m_ElapsedTime; }
		
	private:
		float m_Time;
		float m_ElapsedTime;
	};
}