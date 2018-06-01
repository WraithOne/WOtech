////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: VirtualController.h
///
///			Description:
///
///			Created:	04.01.2017
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "VirtualController.h"

namespace WOtech
{
	VirtualController::VirtualController(_In_ InputManager^ input)
	{
		m_inputManager = input;

		m_state = WOtech::Virtual_Controller_State();
		m_currentInput = WOtech::Current_Input_Device::Unspecified;
		m_currentGamepad = WOtech::Gamepad_Index::PlayerOne; // TODO: Player unknown
		m_mouseWheelbinding = WOtech::Virtual_Controller_Triggers::Left;
		m_mousebinding = WOtech::Virtual_Controller_Sticks::Left;
		m_currentStickLeftID = 0U;
		m_currentStickRightID = 0U;
		m_currentTriggerLeftID = 0U;
		m_currentTriggerRightID = 0U;
	}

	void VirtualController::setCurrentInput(_In_ Current_Input_Device current)
	{
		m_currentInput = current;
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

	void VirtualController::bindGamepad(_In_ Gamepad_Index number)
	{
		m_currentGamepad = number;
	}

	void VirtualController::bindKeyboardtoButton(_In_ Virtual_Controller_Buttons target, _In_ Windows::System::VirtualKey key)
	{
		std::map<Virtual_Controller_Buttons, Windows::System::VirtualKey>::iterator it;
		it = m_keyboardButtonbinding.find(target);

		if (it != m_keyboardButtonbinding.end())
		{
			m_keyboardButtonbinding[target] = key;
		}
		else
		{
			m_keyboardButtonbinding.emplace(target, key);
		}
	}
	void VirtualController::bindKeyboardtoTrigger(_In_ Virtual_Controller_Triggers target, _In_ Windows::System::VirtualKey key)
	{
		std::map<Virtual_Controller_Triggers, Windows::System::VirtualKey>::iterator it;
		it = m_keyboardTriggerbinding.find(target);

		if (it != m_keyboardTriggerbinding.end())
		{
			m_keyboardTriggerbinding[target] = key;
		}
		else
		{
			m_keyboardTriggerbinding.emplace(target, key);
		}
	}
	void VirtualController::bindKeyboardtoTumbstick(_In_ Virtual_Controller_Sticks target, _In_ Windows::System::VirtualKey keyUP, _In_ Windows::System::VirtualKey keyDOWN, _In_ Windows::System::VirtualKey keyLEFT, _In_ Windows::System::VirtualKey keyRIGHT)
	{
		virtual_Stick_keyboard temp;
		temp.up = keyUP;
		temp.down = keyDOWN;
		temp.left = keyLEFT;
		temp.right = keyRIGHT;

		std::map<Virtual_Controller_Sticks, virtual_Stick_keyboard>::iterator it;
		it = m_keyboardStickbinding.find(target);

		if (it != m_keyboardStickbinding.end())
		{
			m_keyboardStickbinding[target] = temp;
		}
		else
		{
			m_keyboardStickbinding.emplace(target, temp);
		}
	}

	void VirtualController::bindMousetoButton(_In_ Virtual_Controller_Buttons target, _In_ Windows::Foundation::Rect area)
	{
		std::map<Virtual_Controller_Buttons, Windows::Foundation::Rect>::iterator it;
		it = m_mouseButtonbinding.find(target);

		if (it != m_mouseButtonbinding.end())
		{
			m_mouseButtonbinding[target] = area;
		}
		else
		{
			m_mouseButtonbinding.emplace(target, area);
		}
	}
	void VirtualController::bindMouseKeytoButton(_In_ Virtual_Controller_Buttons target, _In_ WOtech::VirtualKey_Mouse key)
	{
		std::map<Virtual_Controller_Buttons, WOtech::VirtualKey_Mouse>::iterator it;
		it = m_mouseKeybinding.find(target);

		if (it != m_mouseKeybinding.end())
		{
			m_mouseKeybinding[target] = key;
		}
		else
		{
			m_mouseKeybinding.emplace(target, key);
		}
	}
	void VirtualController::bindMouseWheeltoTrigger(_In_ Virtual_Controller_Triggers target)
	{
		m_mouseWheelbinding = target;
	}
	void VirtualController::bindMousetoTumbstick(_In_ Virtual_Controller_Sticks target)
	{
		m_mousebinding = target;
	}

	void VirtualController::bindTouchtoButton(_In_ Virtual_Controller_Buttons target, _In_ Windows::Foundation::Rect area)
	{
		std::map<Virtual_Controller_Buttons, Windows::Foundation::Rect>::iterator it;
		it = m_touchButtonbinding.find(target);

		if (it != m_touchButtonbinding.end())
		{
			m_touchButtonbinding[target] = area;
		}
		else
		{
			m_touchButtonbinding.emplace(target, area);
		}
	}
	void VirtualController::bindTouchtoTrigger(_In_ Virtual_Controller_Triggers target, _In_ Windows::Foundation::Rect area)
	{
		std::map<Virtual_Controller_Triggers, Windows::Foundation::Rect>::iterator it;
		it = m_touchTriggerbinding.find(target);

		if (it != m_touchTriggerbinding.end())
		{
			m_touchTriggerbinding[target] = area;
		}
		else
		{
			m_touchTriggerbinding.emplace(target, area);
		}
	}
	void VirtualController::bindTouchtoTumbstick(_In_ Virtual_Controller_Sticks target, _In_ Windows::Foundation::Point center, _In_ float32 radius)
	{
		virtual_Stick_touch stick;
		stick.center = center;
		stick.radius = radius;

		std::map<Virtual_Controller_Sticks, virtual_Stick_touch>::iterator it;
		it = m_touchStickbinding.find(target);

		if (it != m_touchStickbinding.end())
		{
			m_touchStickbinding[target] = stick;
		}
		else
		{
			m_touchStickbinding.emplace(target, stick);
		}
	}

	inline Platform::Boolean PointerIntersect(_In_ Touch_State& state, _In_ Windows::Foundation::Rect& area)
	{
		WOtech::Pointer_Position position = state.Position;

		if (((position.X >= area.X) && (position.X <= area.Width)) &&
			((position.Y >= area.Y) && (position.Y <= area.Height)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	inline Touch_State TouchIntersect(_In_ Platform::Array<Touch_State>^ state, _In_ Windows::Foundation::Rect& area)
	{
		Touch_State temp;

		for (unsigned int i = 0; i != state->Length; i++)
		{
			if (state->get(i).PointerID != 0U)
			{
				if (PointerIntersect(state->get(i), area))
					return state->get(i);
			}
		}

		return temp;
	}
	inline Platform::Boolean isIntersecting(Touch_State& state)
	{
		if (state.PointerID != 0U)
			return true;
		else
			return false;
	}

	VirtualController::~VirtualController()
	{
		// Keyboard
		m_keyboardButtonbinding.clear();
		m_keyboardTriggerbinding.clear();
		m_keyboardStickbinding.clear();

		// Mouse
		m_mouseKeybinding.clear();
		m_mouseButtonbinding.clear();

		// Touch
		m_touchButtonbinding.clear();
		m_touchTriggerbinding.clear();
		m_touchStickbinding.clear();
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

	void VirtualController::UpdateGamepad()
	{
		WOtech::Gamepad_State state = m_inputManager->GamepadState(m_currentGamepad);

		// Connection status
		m_state.isConnected = state.Connected;
		m_state.isWireless = state.isWireless;

		// Batterie Percentage
		m_state.ChargePercentage = state.ChargePercentage;;

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
		m_state.Trigger_Left = state.Triggers.Left;
		m_state.Trigger_Right = state.Triggers.Right;

		// Tumbstick states
		m_state.Tumbstick_LeftX = state.Tumbsticks.LeftX;
		m_state.Tumbstick_LeftY = state.Tumbsticks.LeftY;
		m_state.Tumbstick_RightX = state.Tumbsticks.RightX;
		m_state.Tumbstick_RightY = state.Tumbsticks.RightY;
	}
	void VirtualController::UpdateKeyboard()
	{
		m_state.isConnected = true;
		m_state.isWireless = false;
		m_state.ChargePercentage = 100U;

		WOtech::Keyboard_State keyState = m_inputManager->getKeyboardState();

		// Buttons
		for (std::map<Virtual_Controller_Buttons, Windows::System::VirtualKey>::iterator it = m_keyboardButtonbinding.begin(); it != m_keyboardButtonbinding.end(); ++it)
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

		// Triggers
		for (std::map<Virtual_Controller_Triggers, Windows::System::VirtualKey>::iterator it_t = m_keyboardTriggerbinding.begin(); it_t != m_keyboardTriggerbinding.end(); ++it_t)
		{
			if (it_t->first == Virtual_Controller_Triggers::Left)
			{
				if (m_inputManager->KeyDown(it_t->second))
					m_state.Trigger_Left = 1.0;
				else
					m_state.Trigger_Left = 0.0;
			}
			else
			{
				if (m_inputManager->KeyDown(it_t->second))
					m_state.Trigger_Right = 1.0;
				else
					m_state.Trigger_Right = 0.0;
			}
		}

		// Tumbsticks
		for (std::map<Virtual_Controller_Sticks, virtual_Stick_keyboard>::iterator it_s = m_keyboardStickbinding.begin(); it_s != m_keyboardStickbinding.end(); ++it_s)
		{
			virtual_Stick_keyboard keyboard = it_s->second;

			Platform::Boolean key_up = m_inputManager->KeyDown(keyboard.up);
			Platform::Boolean key_down = m_inputManager->KeyDown(keyboard.down);
			Platform::Boolean key_left = m_inputManager->KeyDown(keyboard.left);
			Platform::Boolean key_right = m_inputManager->KeyDown(keyboard.right);

			if (it_s->first == Virtual_Controller_Sticks::Left)
			{
				// Vertical
				if (key_up && !key_down)
					m_state.Tumbstick_LeftY = 1.0;
				else if (!key_up && key_down)
					m_state.Tumbstick_LeftY = -1.0;
				else
					m_state.Tumbstick_LeftY = 0.0;

				// Horizontal
				if (key_right && !key_left)
					m_state.Tumbstick_LeftX = 1.0;
				else if (!key_right && key_left)
					m_state.Tumbstick_LeftX = -1.0;
				else
					m_state.Tumbstick_LeftX = 0.0;
			}
			else
			{
				// Vertical
				if (key_up && !key_down)
					m_state.Tumbstick_RightY = 1.0;
				else if (!key_up && key_down)
					m_state.Tumbstick_RightY = -1.0;
				else
					m_state.Tumbstick_RightY = 0.0;

				// Horizontal
				if (key_right && !key_left)
					m_state.Tumbstick_RightX = 1.0;
				else if (!key_right && key_left)
					m_state.Tumbstick_RightX = -1.0;
				else
					m_state.Tumbstick_RightX = 0.0;
			}
		}
	}
	void VirtualController::UpdateMouse()
	{
		m_state.isConnected = true;
		m_state.isWireless = false;
		m_state.ChargePercentage = 100U;
		// TODO: add things
	}
	void VirtualController::UpdateTouch()
	{
		Platform::Array<Touch_State>^ touchstate = m_inputManager->getTouchState();

		m_state.isConnected = true;
		m_state.isWireless = false;
		m_state.ChargePercentage = 100U;

		// Button states
		for (std::map<Virtual_Controller_Buttons, Windows::Foundation::Rect>::iterator it = m_touchButtonbinding.begin(); it != m_touchButtonbinding.end(); ++it)
		{
			// Buttons A-Y
			if (it->first == Virtual_Controller_Buttons::A)
				m_state.Button_A = isIntersecting(TouchIntersect(touchstate, it->second));
			if (it->first == Virtual_Controller_Buttons::B)
				m_state.Button_B = isIntersecting(TouchIntersect(touchstate, it->second));
			if (it->first == Virtual_Controller_Buttons::X)
				m_state.Button_X = isIntersecting(TouchIntersect(touchstate, it->second));
			if (it->first == Virtual_Controller_Buttons::Y)
				m_state.Button_Y = isIntersecting(TouchIntersect(touchstate, it->second));

			// Buttons Menu, View
			if (it->first == Virtual_Controller_Buttons::Menu)
				m_state.Button_Menu = isIntersecting(TouchIntersect(touchstate, it->second));
			if (it->first == Virtual_Controller_Buttons::View)
				m_state.Button_View = isIntersecting(TouchIntersect(touchstate, it->second));

			// Buttons Shoulder
			if (it->first == Virtual_Controller_Buttons::LeftShoulder)
				m_state.Button_LeftShoulder = isIntersecting(TouchIntersect(touchstate, it->second));
			if (it->first == Virtual_Controller_Buttons::RightShoulder)
				m_state.Button_RightShoulder = isIntersecting(TouchIntersect(touchstate, it->second));

			// Buttons Sticks
			if (it->first == Virtual_Controller_Buttons::LeftStick)
				m_state.Button_LeftStick = isIntersecting(TouchIntersect(touchstate, it->second));
			if (it->first == Virtual_Controller_Buttons::RightStick)
				m_state.Button_RightStick = isIntersecting(TouchIntersect(touchstate, it->second));

			// Buttons DPad
			if (it->first == Virtual_Controller_Buttons::DPad_Up)
				m_state.DPad_Up = isIntersecting(TouchIntersect(touchstate, it->second));
			if (it->first == Virtual_Controller_Buttons::DPad_Down)
				m_state.DPad_Down = isIntersecting(TouchIntersect(touchstate, it->second));
			if (it->first == Virtual_Controller_Buttons::DPad_Left)
				m_state.DPad_Left = isIntersecting(TouchIntersect(touchstate, it->second));
			if (it->first == Virtual_Controller_Buttons::DPad_Right)
				m_state.DPad_Right = isIntersecting(TouchIntersect(touchstate, it->second));
		}
		// Trigger states
		for (std::map<Virtual_Controller_Triggers, Windows::Foundation::Rect>::iterator it_t = m_touchTriggerbinding.begin(); it_t != m_touchTriggerbinding.end(); ++it_t)
		{
			Touch_State state;
			if (it_t->first == Virtual_Controller_Triggers::Left)
			{
				state = TouchIntersect(touchstate, it_t->second);
				if (state.PointerID != 0U)
				{
					if (m_currentTriggerLeftID == 0U)
					{
						m_currentTriggerLeftID = state.PointerID;
					}
					if (m_currentTriggerLeftID == state.PointerID)
					{
						// betwen 0.0 and 1.0
						m_state.Trigger_Left = state.Position.Y / (it_t->second.Height - it_t->second.Y);
						if (m_state.Trigger_Left > 1.0)
							m_state.Trigger_Left = 1.0;

						// TODO : Invert or not
						m_state.Trigger_Left = 1 - m_state.Trigger_Left;
					}
				}
				else
				{
					m_currentTriggerLeftID = 0U;
					m_state.Trigger_Left = 0.0;
				}
			}
			else
			{
				state = TouchIntersect(touchstate, it_t->second);
				if (state.PointerID != 0U)
				{
					if (m_currentTriggerRightID == 0U)
					{
						m_currentTriggerRightID = state.PointerID;
					}
					if (m_currentTriggerRightID == state.PointerID)
					{
						// betwen 0.0 and 1.0
						m_state.Trigger_Right = (it_t->second.Height - it_t->second.Y) / state.Position.Y;
						if (m_state.Trigger_Right > 1.0)
							m_state.Trigger_Right = 1.0;

						// TODO : Invert or not
						m_state.Trigger_Right = 1 - m_state.Trigger_Right;
					}
				}
				else
				{
					m_currentTriggerRightID = 0U;
					m_state.Trigger_Right = 0.0;
				}
			}
		}
		// Stick states
		for (std::map<Virtual_Controller_Sticks, virtual_Stick_touch>::iterator it_s = m_touchStickbinding.begin(); it_s != m_touchStickbinding.end(); ++it_s)
		{
			// TODO: Circle insteed of RECT
			virtual_Stick_touch stick = it_s->second;
			Windows::Foundation::Rect rect{ stick.center.X - stick.radius, stick.center.Y - stick.radius, stick.center.X + stick.radius, stick.center.Y + stick.radius };

			Touch_State state;
			if (it_s->first == Virtual_Controller_Sticks::Left)
			{
				state = TouchIntersect(touchstate, rect);
				if (state.PointerID != 0U)
				{
					if (m_currentStickLeftID == 0U)
					{
						m_currentStickLeftID = state.PointerID;
					}
					if (m_currentStickLeftID == state.PointerID)
					{
						// betwen -1.0 and 1.0
						m_state.Tumbstick_LeftX = (rect.Width - rect.X) / state.Position.X;
						if (state.Position.X < (rect.X + ((rect.Width - rect.X) / 2)))
							m_state.Tumbstick_LeftX *= -1;
						m_state.Tumbstick_LeftY = (rect.Height - rect.Y) / state.Position.Y;
						if (state.Position.Y > (rect.Y + ((rect.Height - rect.Y) / 2)))
							m_state.Tumbstick_LeftY *= -1;
					}
				}
				else
				{
					m_currentStickLeftID = 0U;
					m_state.Tumbstick_LeftX = 0.0;
					m_state.Tumbstick_LeftY = 0.0;
				}
			}
			else
			{
				state = TouchIntersect(touchstate, rect);
				if (state.PointerID != 0U)
				{
					if (m_currentStickLeftID == 0U)
					{
						m_currentStickLeftID = state.PointerID;
					}
					if (m_currentStickLeftID == state.PointerID)
					{
						// betwen -1.0 and 1.0
						m_state.Tumbstick_RightX = (rect.Width - rect.X) / state.Position.X;
						if (state.Position.X < (rect.X + ((rect.Width - rect.X) / 2)))
							m_state.Tumbstick_RightX *= -1;
						m_state.Tumbstick_RightY = (rect.Height - rect.Y) / state.Position.Y;
						if (state.Position.Y > (rect.Y + ((rect.Height - rect.Y) / 2)))
							m_state.Tumbstick_RightY *= -1;
					}
				}
				else
				{
					m_currentStickLeftID = 0U;
					m_state.Tumbstick_LeftX = 0.0;
					m_state.Tumbstick_LeftY = 0.0;
				}
			}
		}
	}
	void VirtualController::UpdatePen()
	{
		m_state.isConnected = true;
		m_state.isWireless = false;
		m_state.ChargePercentage = 100U;
		// TODO: add things
	}
}