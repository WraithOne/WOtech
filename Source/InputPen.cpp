////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Inputmouse.cpp
///
///			Description:
///
///			Created:	01.05.2014
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

	Platform::Array<Pen_State>^ InputManager::getPenState()
	{
		auto temp = ref new Platform::Array<Pen_State>(m_touchCapabilities->Contacts); // TODO: max pen supportet
		unsigned int nr = 0;
		for (std::map<UINT, Windows::UI::Input::PointerPoint^>::iterator it = m_pointerdevices.begin(); it != m_pointerdevices.end(); ++it)
		{
			auto pointer = it->second;

			if (pointer->PointerDevice->PointerDeviceType == PointerDeviceType::Pen)
			{
				temp[nr].pointerID = pointer->PointerId;
				temp[nr].BarrelButton = pointer->Properties->IsBarrelButtonPressed;
				temp[nr].isErazer = pointer->Properties->IsEraser;
				temp[nr].position.X = pointer->Position.X;
				temp[nr].position.Y = pointer->Position.Y;
				temp[nr].pressure = pointer->Properties->Pressure;
			}
		}
		return temp;
	}
}//namespace WOtech