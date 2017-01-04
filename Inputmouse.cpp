////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: Inputmouse.cpp
///
///			Created:	28.08.2015
///			Edited:		03.01.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Input.h"

using namespace Windows::Gaming::Input;
using namespace Windows::Foundation::Collections;
using namespace Windows::Devices::Input;
using namespace Platform;

namespace WOtech
{
	Boolean InputManager::MouseConnected()
	{
		if (m_mouseCapabilities->MousePresent >= 1)
			return true;

		return false;
	}
	Mouse_State InputManager::getMouseState()
	{
		Mouse_State temp;
		for (std::map<UINT, Windows::UI::Input::PointerPoint^>::iterator it = m_pointerdevices.begin(); it != m_pointerdevices.end(); ++it)
		{
			if (it->second->PointerDevice->PointerDeviceType == PointerDeviceType::Mouse)
			{
				temp.pointerID = it->second->PointerId;
				temp.position = m_mouseDelta;
				temp.buttons.LeftButton = it->second->Properties->IsLeftButtonPressed;
				temp.buttons.RightButton = it->second->Properties->IsRightButtonPressed;
				temp.buttons.MiddleButton = it->second->Properties->IsMiddleButtonPressed;
				temp.buttons.X1Button = it->second->Properties->IsXButton1Pressed;
				temp.buttons.X2Button = it->second->Properties->IsXButton2Pressed;
				temp.wheeldelta = it->second->Properties->MouseWheelDelta;
			}
		}
		return temp;
	}

	void InputManager::MouseShowCursor(_In_ Platform::Boolean show)
	{
		Windows::UI::Core::CoreWindow^ window = Windows::UI::Core::CoreWindow::GetForCurrentThread();

		if (show)
		{
			window->PointerCursor = ref new Windows::UI::Core::CoreCursor(Windows::UI::Core::CoreCursorType::Arrow, 0);
		}
		else

		{
			window->PointerCursor = nullptr;
		}
	}
	Platform::Boolean InputManager::MouseCursorVisible()
	{
		Windows::UI::Core::CoreWindow^ window = Windows::UI::Core::CoreWindow::GetForCurrentThread();
		if (window->PointerCursor == nullptr)
			return false;

		return true;
	}
}// namespace WOtech