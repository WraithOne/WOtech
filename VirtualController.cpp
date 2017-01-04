////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: VirtualController.h
///
///			Created:	04.01.2017
///			Edited:		04.01.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "VirtualController.h"

namespace WOtech
{
	namespace Gameframework
	{
		VirtualController::VirtualController()
		{
		}

		void VirtualController::setCurrentInput(Current_Input current)
		{
			m_currentInput = current;
		}

		Current_Input VirtualController::getCurrent()
		{
			return m_currentInput;
		}

		Virtual_Gamepad VirtualController::getState()
		{
			return m_state;
		}
	}
}
