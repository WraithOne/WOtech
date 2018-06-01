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
///			Edited:		12.05.2018
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
		static WOtech::DeviceDX11^ CreateDeviceDX11();
		static WOtech::DeviceDX11^ GetDeviceDX11();

		static WOtech::SpriteBatch^ CreateSpriteBatch(_In_ DeviceDX11^ device);
		static WOtech::SpriteBatch^ GetSpriteBatch();

		static WOtech::InputManager^ CreateInputManager();
		static WOtech::InputManager^ GetInputManager();

		static WOtech::AudioEngine^ CreateAudioEngine();
		static WOtech::AudioEngine^ GetAudioEngine();

		static void RunGame(_In_ IGame^ Game);
	};
}
#endif