////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: ContentManager.h
///
///			Description:
///
///			Created:	14.01.2018
///			Edited:		14.01.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_GAME_H
#define WO_GAME_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "GameTimer.h"

namespace WOtech
{
	public interface class IGame 
	{
	public:
		virtual void Initalize();
		virtual void Load();
		virtual void UnLoad();
		virtual void Update(GameTime gametime);
		virtual void Draw(GameTime gametime);

		virtual void OnWindowChanged();
		virtual void OnSuspending();
		virtual void OnResuming();
	};
}
#endif