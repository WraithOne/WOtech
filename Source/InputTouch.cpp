////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: InputTouch.cpp
///
///			Description:
///
///			Created:	27.08.2016
///			Edited:		15.01.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Input.h"

using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::Devices::Input;
using namespace Platform;

namespace WOtech
{
	Boolean InputManager::TouchConnected()
	{
		if (m_touchCapabilities->TouchPresent != 0)
			return true;
		else
			return false;

	}
	Platform::Array<Touch_State>^ InputManager::getTouchState()
	{
		auto temp = ref new Platform::Array<Touch_State>(m_touchCapabilities->Contacts);//TODO : max contacts supportet
		unsigned int nr = 0;

		for (std::map<UINT, Windows::UI::Input::PointerPoint^>::iterator it = m_pointerdevices.begin(); it != m_pointerdevices.end(); ++it)
		{
			if (it->second->PointerDevice->PointerDeviceType == PointerDeviceType::Touch)
			{
				temp[nr].pointerID = it->second->PointerId;
				temp[nr].position.X = it->second->Position.X;
				temp[nr].position.Y = it->second->Position.Y;
			}
			nr++;
		}
		return temp;
	}
}