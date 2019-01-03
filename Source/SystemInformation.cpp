////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: SystemInformation.cpp
///
///			Description:
///
///			Created:	18.03.2017
///			Edited:		18.03.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include "SystemInformation.h"

namespace WOtech
{
	SystemInformation::SystemInformation()
	{
	}
	void SystemInformation::GatherInformations()
	{
	}
	Platform::Array<WOtech::ADAPTER_DXGI>^ SystemInformation::getGraphicInformations()
	{
		Platform::Array<WOtech::ADAPTER_DXGI>^ temp_array;
		//WOtech::ADAPTER_DXGI temp;
		return temp_array;
		// TODO: insert return statement here
	}
	SystemInformation::~SystemInformation()
	{
	}
}