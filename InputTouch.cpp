////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: InputTouch.cpp
///
///			Created:	27.08.2016
///			Edited:		03.01.2017
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
		for (std::map<UINT, Windows::UI::Input::PointerPoint^>::iterator it = m_pointerdevices.begin(); it != m_pointerdevices.end(); ++it)
		{
			if (it->second->PointerDevice->PointerDeviceType == PointerDeviceType::Touch)
				return true;
		}
		return false;
	}
	Touch_State InputManager::getTouchState()
	{
		Touch_State temp;// [100] TODO : max contacts supportet
		for (std::map<UINT, Windows::UI::Input::PointerPoint^>::iterator it = m_pointerdevices.begin(); it != m_pointerdevices.end(); ++it)
		{
			if (it->second->PointerDevice->PointerDeviceType == PointerDeviceType::Touch)
			{
				temp.pointerID = it->second->PointerId;
				temp.position.X = it->second->Position.X;
				temp.position.Y = it->second->Position.Y;
			}
		}
		return temp;
	}
}