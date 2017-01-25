////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: VirtualController.h
///
///			Created:	04.01.2017
///			Edited:		25.01.2017
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
		VirtualController::VirtualController(_In_ WOtech::InputManager^ Input)
		{
			m_inputManager = Input;
		}

		void VirtualController::Update()
		{
			switch (m_currentInput)
			{
			case WOtech::Gameframework::Current_Input_Device::Gamepad:
				UpdateGamepad();
				break;
			case WOtech::Gameframework::Current_Input_Device::KeyboardandMouse:
				UpdateKeyboard();
				UpdateMouse();
				break;
			case WOtech::Gameframework::Current_Input_Device::Touch:
				UpdateTouch();
				break;
			case WOtech::Gameframework::Current_Input_Device::Pen:
				UpdatePen();
				break;
			default:
				break;
			}
		}

		void VirtualController::setCurrentInput(_In_ Current_Input_Device Current)
		{
			m_currentInput = Current;
		}

		Current_Input_Device VirtualController::getCurrent()
		{
			return m_currentInput;
		}

		Virtual_Controller VirtualController::getState()
		{
			// Update state before returning
			Update();

			return m_state;
		}
		void VirtualController::bindGamepad(_In_ Gamepad_Index Number)
		{
			m_currentGamepad = Number;
		}
		void VirtualController::bindKeyboardKey(_In_ Virtual_Controller_Buttons Target, _In_ Windows::System::VirtualKey Key)
		{
			std::map<Virtual_Controller_Buttons, Windows::System::VirtualKey>::iterator it;
			it = m_keyboardbinding.find(Target);

			if (it != m_keyboardbinding.end())
			{
				m_keyboardbinding[Target] = Key;
			}
			else
			{
				m_keyboardbinding.emplace(Target, Key);
			}
		}
		void VirtualController::UpdateGamepad()
		{
			WOtech::Gamepad_State state = m_inputManager->GamepadState(m_currentGamepad);

			// Connection status
			m_state.isConnected = state.Connected;
			m_state.isWireless = state.isWireless;

			// Buttons A-Y
			m_state.Button_A = state.Buttons.A;
			m_state.Button_B = state.Buttons.B;
			m_state.Button_X = state.Buttons.X;
			m_state.Button_Y = state.Buttons.Y;

			// Buttons Menu, View
			m_state.Button_Menu = state.Buttons.Menu;
			m_state.Button_View = state.Buttons.View;

			// Buttons Shoulder
			m_state.Button_LeftShoulder = state.Buttons.LeftShoulder;
			m_state.Button_RightShoulder = state.Buttons.RightShoulder;

			// Buttons Sticks
			m_state.Button_LeftStick = state.Buttons.LeftStick;	
			m_state.Button_RightStick = state.Buttons.RightStick;

			// Buttons DPad
			m_state.DPad_Up = state.DPad.Up;
			m_state.DPad_Down = state.DPad.Down;
			m_state.DPad_Left = state.DPad.Left;
			m_state.DPad_Right = state.DPad.Right;

			// Trigger states
			m_state.Trigger_Left = state.triggers.Left;
			m_state.Trigger_Right = state.triggers.Right;

			// Tumbstick states
			m_state.Tumbstick_LeftX = state.tumbsticks.LeftX;
			m_state.Tumbstick_LeftY = state.tumbsticks.LeftY;
			m_state.Tumbstick_RightX = state.tumbsticks.RightX;
			m_state.Tumbstick_RightY = state.tumbsticks.RightY;
		}
		void VirtualController::UpdateKeyboard()
		{
			m_state.isConnected = true;
			m_state.isWireless = false;
			WOtech::Keyboard_State keyState = m_inputManager->getKeyboardState();

			for(std::map<Virtual_Controller_Buttons, Windows::System::VirtualKey>::iterator it = m_keyboardbinding.begin(); it != m_keyboardbinding.end(); ++it)
			{
				// Buttons A-Y
				if (it->first == Virtual_Controller_Buttons::A)
					m_state.Button_A = m_inputManager->KeyDown(it->second);
				if (it->first == Virtual_Controller_Buttons::B)
					m_state.Button_B = m_inputManager->KeyDown(it->second);
				if (it->first == Virtual_Controller_Buttons::X)
					m_state.Button_X = m_inputManager->KeyDown(it->second);
				if (it->first == Virtual_Controller_Buttons::Y)
					m_state.Button_Y = m_inputManager->KeyDown(it->second);

				// Buttons Menu, View
				if (it->first == Virtual_Controller_Buttons::Menu)
					m_state.Button_Menu = m_inputManager->KeyDown(it->second);
				if (it->first == Virtual_Controller_Buttons::View)
					m_state.Button_View = m_inputManager->KeyDown(it->second);

				// Buttons Shoulder
				if (it->first == Virtual_Controller_Buttons::LeftShoulder)
					m_state.Button_LeftShoulder = m_inputManager->KeyDown(it->second);
				if (it->first == Virtual_Controller_Buttons::RightShoulder)
					m_state.Button_RightShoulder = m_inputManager->KeyDown(it->second);

				// Buttons Sticks
				if (it->first == Virtual_Controller_Buttons::LeftStick)
					m_state.Button_LeftStick = m_inputManager->KeyDown(it->second);
				if (it->first == Virtual_Controller_Buttons::RightStick)
					m_state.Button_RightStick = m_inputManager->KeyDown(it->second);

				// Buttons DPad
				if (it->first == Virtual_Controller_Buttons::DPad_Up)
					m_state.DPad_Up = m_inputManager->KeyDown(it->second);
				if (it->first == Virtual_Controller_Buttons::DPad_Down)
					m_state.DPad_Down = m_inputManager->KeyDown(it->second);
				if (it->first == Virtual_Controller_Buttons::DPad_Left)
					m_state.DPad_Left = m_inputManager->KeyDown(it->second);
				if (it->first == Virtual_Controller_Buttons::DPad_Right)
					m_state.DPad_Right = m_inputManager->KeyDown(it->second);

				// Trigger states
				// Tumbstick states
			}
		}
		void VirtualController::UpdateMouse()
		{
			return; // TODO
		}
		
		void VirtualController::UpdateTouch()
		{
			return; // TODO
		}
		void VirtualController::UpdatePen()
		{
			return; // TODO
		}
	}
}
