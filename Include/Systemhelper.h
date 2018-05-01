////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Systemhelper.h
///
///			Description:
///
///			Created:	23.04.2018
///			Edited:		01.05.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_SYSTEMHELPER_H
#define WO_SYSTEMHELPER_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Audio.h"
#include "DeviceDX11.h"
#include "SpriteBatch.h"
#include "Input.h"
#include "IGame.h"

namespace WOtech
{
	public ref class Systemhelper sealed
	{
	private:
		Systemhelper();
		~Systemhelper();

	public:
		static DeviceDX11^ CreateDeviceDX11();
		static DeviceDX11^ GetDeviceDX11();

		static SpriteBatch^ CreateSpriteBatch(_In_ DeviceDX11^ device);
		static SpriteBatch^ GetSpriteBatch();

		static void RunGame(_In_ IGame^ Game);
	};
}
#endif