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
///			Edited:		30.04.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "..\Include\Systemhelper.h"
#include "Include\SystemManager.h"
#include "Include\Application.h"

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
	DeviceDX11 ^ Systemhelper::CreateDeviceDX11()
	{
		auto device = ref new DeviceDX11();
		device->Create();

		return device;
	}
	DeviceDX11 ^ Systemhelper::GetDeviceDX11()
	{
		return WOtech::SystemManager::Instance->GetDeviceDX11();
	}
	void Systemhelper::RunGame(_In_ IGame^ Game)
	{
		auto viewsource = ref new ViewSource();
		viewsource->addGame(Game);

		Windows::ApplicationModel::Core::CoreApplication::Run(viewsource);
	}
}