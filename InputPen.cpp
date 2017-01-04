////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: Inputmouse.cpp
///
///			Created:	01.05.2014
///			Edited:		06.11.2016
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

namespace WOtech
{
	Platform::Boolean InputManager::PenConnected()
	{
		for (std::map<UINT, Windows::UI::Input::PointerPoint^>::iterator it = m_pointerdevices.begin(); it != m_pointerdevices.end(); ++it)
		{
			if (it->second->PointerDevice->PointerDeviceType == PointerDeviceType::Pen)
				return true;
		}
		return false;
	}

	Pen_State InputManager::getPenState()
	{
		Pen_State temp;
		for (std::map<UINT, Windows::UI::Input::PointerPoint^>::iterator it = m_pointerdevices.begin(); it != m_pointerdevices.end(); ++it)
		{
			if (it->second->PointerDevice->PointerDeviceType == PointerDeviceType::Pen)
			{
				temp.pointerID = it->second->PointerId;
				temp.BarrelButton = it->second->Properties->IsBarrelButtonPressed;
				temp.isErazer = it->second->Properties->IsEraser;
				temp.position.X = it->second->Position.X;
				temp.position.Y = it->second->Position.Y;
				temp.pressure = it->second->Properties->Pressure;
			}	
		}
		return temp;
	}
}//namespace WOtech