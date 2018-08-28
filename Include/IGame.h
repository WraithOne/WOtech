////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: IGAME.h
///
///			Description:
///
///			Created:	14.01.2018
///			Edited:		28.08.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_IGAME_H
#define WO_IGAME_H

//////////////
// INCLUDES //
//////////////
#include "GameTimer.h"

namespace WOtech
{
	public interface class IGame 
	{
	public:
		virtual void Initalize() = 0;
		virtual void Load() = 0;
		virtual void UnLoad() = 0;
		virtual void Update(GameTime gametime) = 0;
		virtual void Draw(GameTime gametime) = 0;

		virtual void OnWindowChanged() = 0;
		virtual void OnSuspending() = 0;
		virtual void OnResuming() = 0;
	};
}
#endif