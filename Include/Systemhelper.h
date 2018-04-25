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
///			Edited:		24.04.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_SYSTEMHELPER_H
#define WO_SYSTEMHELPER_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Application.h"
#include "Window.h"
#include "Audio.h"
#include "DeviceDX11.h"
#include "Input.h"

namespace WOtech
{
	public ref class Systemhelper sealed
	{
	private:
		Systemhelper();
		~Systemhelper();

	public:
		static DeviceDX11^ CreateDeviceDX11();
	};
}
#endif