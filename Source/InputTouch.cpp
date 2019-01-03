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
///			Edited:		01.06.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <Input.h>

namespace WOtech
{
	Platform::Boolean InputManager::TouchConnected()
	{
		if (m_touchCapabilities->TouchPresent != 0)
			return true;
		else
			return false;
	}
	Platform::Array<Touch_State>^ InputManager::getTouchState()
	{
		auto output = ref new Platform::Array<Touch_State>(m_touchCapabilities->Contacts);//TODO : max contacts supportet
		unsigned int nr = 0U;

		for (std::map<UINT, Windows::UI::Input::PointerPoint^>::iterator it = m_pointerdevices.begin(); it != m_pointerdevices.end(); ++it)
		{
			Windows::UI::Input::PointerPoint^ pointer = it->second;

			if (pointer->PointerDevice->PointerDeviceType == Windows::Devices::Input::PointerDeviceType::Touch)
			{
				Touch_State temp{ pointer->PointerId ,Pointer_Position{ pointer->Position.X , pointer->Position.Y } };
				output->set(nr, temp);
			}
			nr++;
		}
		return output;
	}
}