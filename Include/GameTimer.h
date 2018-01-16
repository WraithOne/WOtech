////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Gametimer.h
///
///			Description:
///
///			Created:	12.05.2014
///			Edited:		14.01.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_GAMETIMER_H
#define WO_GAMETIMER_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"

namespace WOtech
{
	public value struct GameTime
	{
		float32 DeltaTime; // Return the Delta time between the last two updates
		float32 PlayingTime; // Return the Elapsed time the Game has been active in seconds since Reset
	};

	public ref class GameTimer sealed
	{
	public:
		GameTimer();
			
		GameTime GetTime();

		void PlayingTime(_In_ float32 time);	// Set the Elapsed playing time -- used for restarting in the middle of a game
						
		void Reset();
		void Start();
		void Stop();
		void Update();

		Platform::Boolean Active();

	private:
		float32			m_secondsPerCount;	// 1.0 / Frequency
		float32			m_deltaTime;

		LARGE_INTEGER	m_baseTime;
		LARGE_INTEGER	m_pausedTime;
		LARGE_INTEGER	m_stopTime;
		LARGE_INTEGER	m_previousTime;
		LARGE_INTEGER	m_currentTime;

		Platform::Boolean m_active;
	};
}
#endif