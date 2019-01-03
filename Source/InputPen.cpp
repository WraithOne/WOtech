////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: InputPen.cpp
///
///			Description:
///
///			Created:	01.05.2014
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <Input.h>

namespace WOtech
{
	Platform::Boolean InputManager::PenConnected()
	{
		for (std::map<UINT, Windows::UI::Input::PointerPoint^>::iterator it = m_pointerdevices.begin(); it != m_pointerdevices.end(); ++it)
		{
			if (it->second->PointerDevice->PointerDeviceType == Windows::Devices::Input::PointerDeviceType::Pen)
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

			if (pointer->PointerDevice->PointerDeviceType == Windows::Devices::Input::PointerDeviceType::Pen)
			{
				temp[nr].PointerID = pointer->PointerId;
				temp[nr].BarrelButton = pointer->Properties->IsBarrelButtonPressed;
				temp[nr].isErazer = pointer->Properties->IsEraser;
				temp[nr].Position.X = pointer->Position.X;
				temp[nr].Position.Y = pointer->Position.Y;
				temp[nr].Pressure = pointer->Properties->Pressure;
			}
		}
		return temp;
	}
}//namespace WOtech