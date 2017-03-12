////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: InputGamepad.cpp
///
///			Description:
///
///			Created:	01.05.2014
///			Edited:		12.03.2017
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
	void InputManager::ScanGamePad()
	{
		unsigned int index = MAX_PLAYER_COUNT - 1;// gamepad index is 0-7
		for (unsigned int i = 0; i <= index; i++)
		{
			if (i < Gamepad::Gamepads->Size)
			{
				m_gamePad[i] = Gamepad::Gamepads->GetAt(i);
			}
			else
			{
				m_gamePad[i] = nullptr;
			}
		}
	}

	Boolean InputManager::GamepadConnected(_In_ Gamepad_Index PlayerIndex)
	{
		if (m_gamePad[(unsigned int)PlayerIndex])
		{
			return true;
		}
			
		return false;
	}

	Gamepad_State InputManager::GamepadState(_In_ Gamepad_Index PlayerIndex)
	{
		if (m_gamePad[(unsigned int)PlayerIndex])
		{
			GamepadReading reading;
			reading = m_gamePad[(unsigned int)PlayerIndex]->GetCurrentReading();


			Gamepad_State state;
			
			state.Connected = true;
			state.isWireless = m_gamePad[(unsigned int)PlayerIndex]->IsWireless;

			state.TimeStamp = reading.Timestamp;
			state.Buttons.A = (reading.Buttons & GamepadButtons::A) == GamepadButtons::A;
			state.Buttons.B = (reading.Buttons & GamepadButtons::B) == GamepadButtons::B;
			state.Buttons.X = (reading.Buttons & GamepadButtons::X) == GamepadButtons::X;
			state.Buttons.Y = (reading.Buttons & GamepadButtons::Y) == GamepadButtons::Y;
			state.Buttons.LeftStick = (reading.Buttons & GamepadButtons::LeftThumbstick) == GamepadButtons::LeftThumbstick;
			state.Buttons.RightStick = (reading.Buttons & GamepadButtons::RightThumbstick) == GamepadButtons::RightThumbstick;
			state.Buttons.LeftShoulder = (reading.Buttons & GamepadButtons::LeftShoulder) == GamepadButtons::LeftShoulder;
			state.Buttons.RightShoulder = (reading.Buttons & GamepadButtons::RightShoulder) == GamepadButtons::RightShoulder;
			state.Buttons.View = (reading.Buttons & GamepadButtons::View) == GamepadButtons::View;
			state.Buttons.Menu = (reading.Buttons & GamepadButtons::Menu) == GamepadButtons::Menu;

			state.DPad.Up = (reading.Buttons & GamepadButtons::DPadUp) == GamepadButtons::DPadUp;
			state.DPad.Down = (reading.Buttons & GamepadButtons::DPadDown) == GamepadButtons::DPadDown;
			state.DPad.Left = (reading.Buttons & GamepadButtons::DPadLeft) == GamepadButtons::DPadLeft;
			state.DPad.Right = (reading.Buttons & GamepadButtons::DPadRight) == GamepadButtons::DPadRight;

			state.tumbsticks.LeftX = reading.LeftThumbstickX;
			state.tumbsticks.LeftY = reading.LeftThumbstickY;
			state.tumbsticks.RightX = reading.RightThumbstickX;
			state.tumbsticks.RightY = reading.RightThumbstickY;

			state.triggers.Left = reading.LeftTrigger;
			state.triggers.Right = reading.RightTrigger;

			return state;
		}
		return Gamepad_State();
	}

	void InputManager::GamepadSetVibration(_In_ Gamepad_Index PlayerIndex, _In_ GamepadVibration Vibration)
	{
		if (m_gamePad[(unsigned int)PlayerIndex])
		{
			m_gamePad[(unsigned int)PlayerIndex]->Vibration = Vibration;
		}

	}// InputClass GamePadSetVibration
} // namespace WOtech