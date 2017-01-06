////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: VirtualController.h
///
///			Created:	04.01.2017
///			Edited:		06.01.2017
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
			case WOtech::Gameframework::Current_Input_Device::Gamepad:
				UpdateGamepad();
				break;
			case WOtech::Gameframework::Current_Input_Device::TouchandPen:
				UpdateTouchandPen();
				break;
			case WOtech::Gameframework::Current_Input_Device::KeyboardandMouse:
				UpdateKeyboardandMouse();
				break;
			default:
				break;
			}
		}

		void VirtualController::setCurrentInput(Current_Input_Device current)
		{
			m_currentInput = current;
		}

		Current_Input_Device VirtualController::getCurrent()
		{
			return m_currentInput;
		}

		Virtual_Controller VirtualController::getState()
		{
			return m_state;
		}
		void VirtualController::bindGamepad(GamepadIndex number)
		{
			m_currentGamepad = number;
		}
		void VirtualController::bindKeyboardKey(Virtual_Controller_Buttons target, Windows::System::VirtualKey key)
		{
			std::map<Virtual_Controller_Buttons, Windows::System::VirtualKey>::iterator it;
			it = m_keyboardbinding.find(target);

			if (it != m_keyboardbinding.end())
			{
				m_keyboardbinding[target] = key;
			}
			else
			{
				m_keyboardbinding.emplace(target, key);
			}
		}
		void VirtualController::UpdateGamepad()
		{
			WOtech::Gamepad_State state = m_inputManager->GamepadState(m_currentGamepad);
			m_state.Button_A = state.Buttons.A;
			m_state.Button_B = state.Buttons.B;
			m_state.Button_X = state.Buttons.X;
			m_state.Button_Y = state.Buttons.Y;
			m_state.Button_Menu = state.Buttons.Menu;
			m_state.Button_View = state.Buttons.View;
			m_state.Button_LeftShoulder = state.Buttons.LeftShoulder;
			m_state.Button_LeftStick = state.Buttons.LeftStick;
			m_state.Button_RightShoulder = state.Buttons.RightShoulder;
			m_state.Button_RightStick = state.Buttons.RightStick;

			m_state.DPad_Up = state.DPad.Up;
			m_state.DPad_Down = state.DPad.Down;
			m_state.DPad_Left = state.DPad.Left;
			m_state.DPad_Right = state.DPad.Right;

			m_state.Trigger_Left = state.triggers.Left;
			m_state.Trigger_Right = state.triggers.Right;

			m_state.Tumbstick_LeftX = state.tumbsticks.LeftX;
			m_state.Tumbstick_LeftY = state.tumbsticks.LeftY;
			m_state.Tumbstick_RightX = state.tumbsticks.RightX;
			m_state.Tumbstick_RightY = state.tumbsticks.RightY;
		}
		void VirtualController::UpdateKeyboardandMouse()
		{
			for(std::map<Virtual_Controller_Buttons, Windows::System::VirtualKey>::iterator it = m_keyboardbinding.begin(); it != m_keyboardbinding.end(); ++it)
			{
				if (it->first == Virtual_Controller_Buttons::A)
					m_state.Button_A = m_inputManager->KeyDown(it->second);
				if (it->first == Virtual_Controller_Buttons::B)
					m_state.Button_B = m_inputManager->KeyDown(it->second);
				if (it->first == Virtual_Controller_Buttons::X)
					m_state.Button_X = m_inputManager->KeyDown(it->second);
				if (it->first == Virtual_Controller_Buttons::Y)
					m_state.Button_Y = m_inputManager->KeyDown(it->second);

			}
		}
		void VirtualController::UpdateTouchandPen()
		{
			throw ref new Platform::NotImplementedException();
		}
	}
}
