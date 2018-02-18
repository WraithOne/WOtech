////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: InputMouse.cpp
///
///			Description:
///
///			Created:	28.08.2015
///			Edited:		18.02.2018
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
			auto pointer = it->second;

			if (pointer->PointerDevice->PointerDeviceType == PointerDeviceType::Mouse)
			{
				temp.PointerID = pointer->PointerId;
				temp.Position = m_mouseDelta;
				temp.Buttons.LeftButton = pointer->Properties->IsLeftButtonPressed;
				temp.Buttons.RightButton = pointer->Properties->IsRightButtonPressed;
				temp.Buttons.MiddleButton = pointer->Properties->IsMiddleButtonPressed;
				temp.Buttons.X1Button = pointer->Properties->IsXButton1Pressed;
				temp.Buttons.X2Button = pointer->Properties->IsXButton2Pressed;
				temp.WheelDelta = pointer->Properties->MouseWheelDelta;
			}
		}
		return temp;
	}

	void InputManager::MouseShowCursor(_In_ Platform::Boolean Show)
	{
		Windows::UI::Core::CoreWindow^ window = Windows::UI::Core::CoreWindow::GetForCurrentThread();

		if (Show)
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