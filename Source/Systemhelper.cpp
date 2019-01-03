////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Systemhelper.cpp
///
///			Description:
///
///			Created:	23.04.2018
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <Application.h>
#include <Systemhelper.h>
#include <SystemManager.h>
#include <Window.h>

namespace WOtech
{
	Systemhelper::Systemhelper()
	{
		// nothing todo here
	}
	Systemhelper::~Systemhelper()
	{
		// nothing todo here
	}

	DeviceDX11^ Systemhelper::CreateDeviceDX11(_In_ WOtech::Window^ window)
	{
		auto device = ref new DeviceDX11(window);
		device->Create();

		return device;
	}
	DeviceDX11^ Systemhelper::GetDeviceDX11()
	{
		return WOtech::SystemManager::Instance->GetDeviceDX11();
	}

	SpriteBatch^ Systemhelper::CreateSpriteBatch(_In_ WOtech::DeviceDX11 ^ device)
	{
		auto spritebatch = ref new WOtech::SpriteBatch(device);
		spritebatch->Initialize();

		return spritebatch;
	}
	SpriteBatch^ Systemhelper::GetSpriteBatch()
	{
		return WOtech::SystemManager::Instance->GetSpriteBatch();
	}

	InputManager^ Systemhelper::CreateInputManager(_In_ WOtech::Window^ window)
	{
		return ref new WOtech::InputManager(window);
	}
	InputManager^ Systemhelper::GetInputManager()
	{
		return WOtech::SystemManager::Instance->GetInputManager();
	}

	AudioEngine^ Systemhelper::CreateAudioEngine()
	{
		return ref new WOtech::AudioEngine();
	}
	AudioEngine^ Systemhelper::GetAudioEngine()
	{
		return WOtech::SystemManager::Instance->GetAudioEngine();
	}

	void Systemhelper::RunGame(_In_ WOtech::IGame^ Game)
	{
		auto viewsource = ref new ViewSource();
		viewsource->addGame(Game);

		Windows::ApplicationModel::Core::CoreApplication::Run(viewsource);
	}
}