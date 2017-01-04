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
		VirtualController::VirtualController(WOtech::InputManager^ input)
		{
			m_inputManager = input;
		}

		void VirtualController::Update()
		{
			switch (m_currentInput)
			{
			case WOtech::Gameframework::Current_Input::Gamepad:
				UpdateGamepad();
				break;
			case WOtech::Gameframework::Current_Input::TouchandPen:
				UpdateTouchandPen;
				break;
			case WOtech::Gameframework::Current_Input::KeyboardandMouse:
				UpdateKeyboardandMouse();
				break;
			default:
				break;
			}
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
		void VirtualController::bindGamepad(GamepadIndex number)
		{
			m_currentGamepad = number;
		}
		void VirtualController::bindKeyboardKey(Virtual_Gamepad_Buttons target, Windows::System::VirtualKey key)
		{
			throw ref new Platform::NotImplementedException();
		}
		void VirtualController::UpdateGamepad()
		{
			WOtech::Gamepad_State state = m_inputManager->GamepadState(m_currentGamepad);
			m_state.Buttons.A = state.Buttons.A;
			m_state.Buttons.B = state.Buttons.B;
			m_state.Buttons.X = state.Buttons.X;
			m_state.Buttons.Y = state.Buttons.Y;
			m_state.Buttons.Menu = state.Buttons.Menu;
			m_state.Buttons.View = state.Buttons.View;
			m_state.Buttons.LeftShoulder = state.Buttons.LeftShoulder;
			m_state.Buttons.LeftStick = state.Buttons.LeftStick;
			m_state.Buttons.RightShoulder = state.Buttons.RightShoulder;
			m_state.Buttons.RightStick = state.Buttons.RightStick;

			m_state.Buttons.DPad.Up = state.DPad.Up;
			m_state.Buttons.DPad.Down = state.DPad.Down;
			m_state.Buttons.DPad.Left = state.DPad.Left;
			m_state.Buttons.DPad.Right = state.DPad.Right;

			m_state.Triggers.Left = state.triggers.Left;
			m_state.Triggers.Right = state.triggers.Right;

			m_state.Tumbsticks.LeftX = state.tumbsticks.LeftX;
			m_state.Tumbsticks.LeftY = state.tumbsticks.LeftY;
			m_state.Tumbsticks.RightX = state.tumbsticks.RightX;
			m_state.Tumbsticks.RightY = state.tumbsticks.RightY;
		}
		void VirtualController::UpdateKeyboardandMouse()
		{
			throw ref new Platform::NotImplementedException();
		}
		void VirtualController::UpdateTouchandPen()
		{
			throw ref new Platform::NotImplementedException();
		}
	}
}
