////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: Inputkeyboard.cpp
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

using namespace Windows::System;
using namespace Windows::UI::Core;

namespace WOtech
{
	Platform::Boolean InputManager::KeyboardConnected()
	{
		if (m_keyBoardCapabilities->KeyboardPresent >= 1)
			return true;

		return false;
	}

	Platform::Boolean InputManager::KeyDown(_In_ VirtualKey Key)
	{
		if (Key == m_keyDown)
		{
			return true;
		}

		return false;
	}// InputClass KeyboardKeyDown
	Platform::Boolean InputManager::KeyUp(_In_ VirtualKey Key)
	{
		if (Key == m_keyUp)
		{
			return true;
		}

		return false;
	}// InputClass KeyboardKeyUp
}//namespace WOtech