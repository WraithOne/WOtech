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
///			Edited:		24.04.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "..\Include\Systemhelper.h"
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
}