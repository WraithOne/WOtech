////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Gametimer.cpp
///
///			Description:
///
///			Created:	12.05.2014
///			Edited:		06.11.2016
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "GameTimer.h"

namespace WOtech
{
	GameTimer::GameTimer() : m_active(false)
	{
		LARGE_INTEGER frequency;

		if (!QueryPerformanceFrequency(&frequency))
		{
			//g_pLogfile->Textout(RED, false, "QueryPreformanceFrequency FAILED <frequency>");
		}
		m_secondsPerCount = 1.0f / static_cast<float32>(frequency.QuadPart);

		Reset();
	}

	float32 GameTimer::PlayingTime()
	{
		if (m_active)
		{
			// The distance m_currentTime - m_baseTime includes paused time,
			// which we do not want to count.  To correct this, we can subtract
			// the paused time from m_currentTime:
			return static_cast<float32>(((m_currentTime.QuadPart - m_pausedTime.QuadPart) - m_baseTime.QuadPart)*m_secondsPerCount);
		}
		else
		{
			// The clock is currently not running so don't count the time since
			// the clock was stopped
			return static_cast<float32>(((m_stopTime.QuadPart - m_pausedTime.QuadPart) - m_baseTime.QuadPart)*m_secondsPerCount);
		}
	}

	void GameTimer::PlayingTime(_In_ float32 time)
	{
		// Reset the internal state to reflect a PlayingTime of 'time'
		// Offset the baseTime by this 'time'.

		m_baseTime.QuadPart = m_stopTime.QuadPart - static_cast<__int64>(time / m_secondsPerCount);
	}

	float32 GameTimer::DeltaTime()
	{
		return m_deltaTime;
	}

	void GameTimer::Reset()
	{
		LARGE_INTEGER currentTime;

		if (!QueryPerformanceCounter(&currentTime))
		{
			//g_pLogfile->Textout(RED, false, "QueryPreformanceFrequency FAILED <currentTime>");
		}
		m_baseTime = currentTime;
		m_previousTime = currentTime;
		m_stopTime = currentTime;
		m_currentTime = currentTime;
		m_pausedTime.QuadPart = 0;
		m_active = false;
	}

	void GameTimer::Start()
	{
		LARGE_INTEGER startTime;

		if (!QueryPerformanceCounter(&startTime))
		{
			//g_pLogfile->Textout(RED, false, "QueryPreformanceFrequency FAILED <startTime>");
		}
		if (!m_active)
		{
			// Accumulate the time elapsed between stop and start pairs.
			m_pausedTime.QuadPart += (startTime.QuadPart - m_stopTime.QuadPart);

			m_previousTime = startTime;
			m_stopTime.QuadPart = 0;
			m_active = true;
		}
	}

	void GameTimer::Stop()
	{
		if (m_active)
		{
			// Set the stop time to the time of the last update.
			m_stopTime = m_currentTime;
			m_active = false;
		}
	}

	void GameTimer::Update()
	{
		if (!m_active)
		{
			m_deltaTime = 0.0;
			return;
		}

		LARGE_INTEGER currentTime;

		if (!QueryPerformanceCounter(&currentTime))
		{
			//g_pLogfile->Textout(RED, false, "QueryPreformanceFrequency FAILED <currentTime>");
		}
		m_currentTime = currentTime;

		m_deltaTime = (m_currentTime.QuadPart - m_previousTime.QuadPart)*m_secondsPerCount;
		m_previousTime = m_currentTime;

		if (m_deltaTime < 0.0)
		{
			m_deltaTime = 0.0;
		}
	}
}//namespace WOtech