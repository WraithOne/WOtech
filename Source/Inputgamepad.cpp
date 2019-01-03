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
///			Edited:		28.08.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <Input.h>

namespace WOtech
{
	void InputManager::ScanGamePad()
	{
		unsigned int index = MAX_PLAYER_COUNT - 1;// gamepad index is 0-7
		for (unsigned int i = 0; i <= index; i++)
		{
			if (i < Windows::Gaming::Input::Gamepad::Gamepads->Size)
			{
				m_gamePad[i] = Windows::Gaming::Input::Gamepad::Gamepads->GetAt(i);
			}
			else
			{
				m_gamePad[i] = nullptr;
			}
		}
	}

	Platform::Boolean InputManager::GamepadConnected(_In_ GAMEPAD_INDEX PlayerIndex)
	{
		if (m_gamePad[(unsigned int)PlayerIndex])
		{
			return true;
		}

		return false;
	}

	Gamepad_State InputManager::GamepadState(_In_ GAMEPAD_INDEX PlayerIndex)
	{
		if (m_gamePad[(unsigned int)PlayerIndex])
		{
			auto reading = m_gamePad[(unsigned int)PlayerIndex]->GetCurrentReading();
			auto BatterieState = m_gamePad[(unsigned int)PlayerIndex]->TryGetBatteryReport();
			//auto maxcharge = BatterieState->FullChargeCapacityInMilliwattHours; 
			auto currentcharge = BatterieState->RemainingCapacityInMilliwattHours;
			Gamepad_State state;

			state.Connected = true;
			state.isWireless = m_gamePad[(unsigned int)PlayerIndex]->IsWireless;
			state.ChargePercentage = currentcharge->Value / 10; // todo: compute the correct percentage

			state.TimeStamp = reading.Timestamp;
			state.Buttons.A = (reading.Buttons & Windows::Gaming::Input::GamepadButtons::A) == Windows::Gaming::Input::GamepadButtons::A;
			state.Buttons.B = (reading.Buttons & Windows::Gaming::Input::GamepadButtons::B) == Windows::Gaming::Input::GamepadButtons::B;
			state.Buttons.X = (reading.Buttons & Windows::Gaming::Input::GamepadButtons::X) == Windows::Gaming::Input::GamepadButtons::X;
			state.Buttons.Y = (reading.Buttons & Windows::Gaming::Input::GamepadButtons::Y) == Windows::Gaming::Input::GamepadButtons::Y;
			state.Buttons.LeftStick = (reading.Buttons & Windows::Gaming::Input::GamepadButtons::LeftThumbstick) == Windows::Gaming::Input::GamepadButtons::LeftThumbstick;
			state.Buttons.RightStick = (reading.Buttons & Windows::Gaming::Input::GamepadButtons::RightThumbstick) == Windows::Gaming::Input::GamepadButtons::RightThumbstick;
			state.Buttons.LeftShoulder = (reading.Buttons & Windows::Gaming::Input::GamepadButtons::LeftShoulder) == Windows::Gaming::Input::GamepadButtons::LeftShoulder;
			state.Buttons.RightShoulder = (reading.Buttons & Windows::Gaming::Input::GamepadButtons::RightShoulder) == Windows::Gaming::Input::GamepadButtons::RightShoulder;
			state.Buttons.View = (reading.Buttons & Windows::Gaming::Input::GamepadButtons::View) == Windows::Gaming::Input::GamepadButtons::View;
			state.Buttons.Menu = (reading.Buttons & Windows::Gaming::Input::GamepadButtons::Menu) == Windows::Gaming::Input::GamepadButtons::Menu;

			state.DPad.Up = (reading.Buttons & Windows::Gaming::Input::GamepadButtons::DPadUp) == Windows::Gaming::Input::GamepadButtons::DPadUp;
			state.DPad.Down = (reading.Buttons & Windows::Gaming::Input::GamepadButtons::DPadDown) == Windows::Gaming::Input::GamepadButtons::DPadDown;
			state.DPad.Left = (reading.Buttons & Windows::Gaming::Input::GamepadButtons::DPadLeft) == Windows::Gaming::Input::GamepadButtons::DPadLeft;
			state.DPad.Right = (reading.Buttons & Windows::Gaming::Input::GamepadButtons::DPadRight) == Windows::Gaming::Input::GamepadButtons::DPadRight;

			state.Tumbsticks.LeftX = reading.LeftThumbstickX;
			state.Tumbsticks.LeftY = reading.LeftThumbstickY;
			state.Tumbsticks.RightX = reading.RightThumbstickX;
			state.Tumbsticks.RightY = reading.RightThumbstickY;

			state.Triggers.Left = reading.LeftTrigger;
			state.Triggers.Right = reading.RightTrigger;

			return state;
		}
		return Gamepad_State();
	}

	void InputManager::GamepadSetVibration(_In_ GAMEPAD_INDEX PlayerIndex, _In_ Windows::Gaming::Input::GamepadVibration Vibration)
	{
		if (m_gamePad[(unsigned int)PlayerIndex])
		{
			m_gamePad[(unsigned int)PlayerIndex]->Vibration = Vibration;
		}
	}// InputClass GamePadSetVibration
} // namespace WOtech