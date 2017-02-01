////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: VirtualController.h
///
///			Created:	04.01.2017
///			Edited:		01.02.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "VirtualController.h"

using namespace WOtech;
using namespace Windows::System;

namespace WOtech
{
	VirtualController::VirtualController(_In_ InputManager^ Input)
	{
		m_inputManager = Input;
	}

	void VirtualController::Update()
	{
		switch (m_currentInput)
		{
		case Current_Input_Device::Gamepad:
			UpdateGamepad();
			break;
		case Current_Input_Device::KeyboardandMouse:
			UpdateKeyboard();
			UpdateMouse();
			break;
		case Current_Input_Device::Touch:
			UpdateTouch();
			break;
		case Current_Input_Device::Pen:
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

	Virtual_Controller_State VirtualController::getState()
	{
		// Update state before returning
		Update();

		return m_state;
	}
	void VirtualController::bindGamepad(_In_ Gamepad_Index Number)
	{
		m_currentGamepad = Number;
	}
	void VirtualController::bindKeyboardKey(_In_ Virtual_Controller_Buttons Target, _In_ VirtualKey Key)
	{
		std::map<Virtual_Controller_Buttons, VirtualKey>::iterator it;
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
	void VirtualController::bindTouchArea(_In_ Virtual_Controller_Buttons Target, _In_ DXWrapper::RECT Area)
	{
		std::map<Virtual_Controller_Buttons, DXWrapper::RECT>::iterator it;
		it = m_touchbinding.find(Target);

		if (it != m_touchbinding.end())
		{
			m_touchbinding[Target] = Area;
		}
		else
		{
			m_touchbinding.emplace(Target, Area);
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

	Platform::Boolean PointerIntersect(_In_ Pointer_Position Position, _In_ DXWrapper::RECT Area)
	{
		if (((Position.X >= Area.X) && (Position.X <= Area.Width)) &&
			((Position.Y >= Area.Y) && (Position.Y <= Area.Height)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	Platform::Boolean TouchIntersect(_In_ Platform::Array<Touch_State>^ State, _In_ DXWrapper::RECT Area)
	{
		for (unsigned int i = 0; i != State->Length; i++)
		{
			if (State[i].pointerID != 0U)
			{
				return PointerIntersect(State[i].position, Area);
			}
		}

		return false;
	}

	void VirtualController::UpdateMouse()
	{
		return; // TODO
	}
	void VirtualController::UpdateTouch()
	{
		Platform::Array<Touch_State>^ state = m_inputManager->getTouchState();

		for (std::map<Virtual_Controller_Buttons, DXWrapper::RECT>::iterator it = m_touchbinding.begin(); it != m_touchbinding.end(); ++it)
		{
			// Buttons A-Y
			if (it->first == Virtual_Controller_Buttons::A)
				m_state.Button_A = TouchIntersect(state, it->second);
			if (it->first == Virtual_Controller_Buttons::B)
				m_state.Button_B = TouchIntersect(state, it->second);
			if (it->first == Virtual_Controller_Buttons::X)
				m_state.Button_X = TouchIntersect(state, it->second);
			if (it->first == Virtual_Controller_Buttons::Y)
				m_state.Button_Y = TouchIntersect(state, it->second);

			// Buttons Menu, View
			if (it->first == Virtual_Controller_Buttons::Menu)
				m_state.Button_Menu = TouchIntersect(state, it->second);
			if (it->first == Virtual_Controller_Buttons::View)
				m_state.Button_View = TouchIntersect(state, it->second);

			// Buttons Shoulder
			if (it->first == Virtual_Controller_Buttons::LeftShoulder)
				m_state.Button_LeftShoulder = TouchIntersect(state, it->second);
			if (it->first == Virtual_Controller_Buttons::RightShoulder)
				m_state.Button_RightShoulder = TouchIntersect(state, it->second);

			// Buttons Sticks
			if (it->first == Virtual_Controller_Buttons::LeftStick)
				m_state.Button_LeftStick = TouchIntersect(state, it->second);
			if (it->first == Virtual_Controller_Buttons::RightStick)
				m_state.Button_RightStick = TouchIntersect(state, it->second);

			// Buttons DPad
			if (it->first == Virtual_Controller_Buttons::DPad_Up)
				m_state.DPad_Up = TouchIntersect(state, it->second);
			if (it->first == Virtual_Controller_Buttons::DPad_Down)
				m_state.DPad_Down = TouchIntersect(state, it->second);
			if (it->first == Virtual_Controller_Buttons::DPad_Left)
				m_state.DPad_Left = TouchIntersect(state, it->second);
			if (it->first == Virtual_Controller_Buttons::DPad_Right)
				m_state.DPad_Right = TouchIntersect(state, it->second);

			// Trigger states
			// Tumbstick states
		}
	}
	void VirtualController::UpdatePen()
	{
		return; // TODO
	}
}
