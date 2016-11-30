////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: Inputmouse.cpp
///
///			Created:	28.08.2015
///			Edited:		06.11.2016
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Input.h"

using namespace Windows::Gaming::Input;
using namespace Windows::Foundation::Collections;
using namespace Platform;

namespace WOtech
{
	Boolean InputManager::MouseConnected()
	{

		if (m_mouseCapabilities->MousePresent >= 1)
			return true;

		return false;
	}
	MousePosition InputManager::MouseDelta()
	{
		MousePosition position;

		position.MouseX = m_mouseDelta.x;
		position.MouseY = m_mouseDelta.y;

		return position;
	}
	Platform::Boolean InputManager::MouseButtonPressed()
	{
		return Platform::Boolean();
	}
	void InputManager::MouseShowCursor(_In_ Platform::Boolean show)
	{
		throw ref new Platform::NotImplementedException();
	}
	Platform::Boolean InputManager::MouseCursorVisible()
	{
		return Platform::Boolean();
	}
}// namespace WOtech