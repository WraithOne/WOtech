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
#ifndef WO_VIRTUALCONTROLLER_H
#define WO_VIRTUALCONTROLLER_H

//////////////
// INCLUDES //
//////////////
#include "Input.h"

namespace WOtech
{
	public enum class Current_Input_Device
	{
		Unspecified,
		Gamepad,
		KeyboardandMouse,
		Touch,
		Pen,
	};
	public enum class Virtual_Controller_Buttons
	{
		A,
		B,
		X,
		Y,
		LeftStick,
		RightStick,
		LeftShoulder,
		RightShoulder,
		View,
		Menu,
		DPad_Up,
		DPad_Down,
		DPad_Left,
		DPad_Right
	};
	public enum class Virtual_Controller_Triggers
	{
		Left,
		Right
	};
	public enum class Virtual_Controller_Sticks
	{
		Left,
		Right
	};

	public value struct Virtual_Controller_State
	{
		Platform::Boolean	isConnected;
		Platform::Boolean	isWireless;
		UINT				ChargePercentage;

		Platform::Boolean	Button_A;
		Platform::Boolean	Button_B;
		Platform::Boolean	Button_X;
		Platform::Boolean	Button_Y;
		Platform::Boolean	Button_LeftStick;
		Platform::Boolean	Button_RightStick;
		Platform::Boolean	Button_LeftShoulder;
		Platform::Boolean	Button_RightShoulder;
		Platform::Boolean	Button_View;
		Platform::Boolean	Button_Menu;

		Platform::Boolean	DPad_Up;
		Platform::Boolean	DPad_Down;
		Platform::Boolean	DPad_Left;
		Platform::Boolean	DPad_Right;

		float64				Trigger_Left;
		float64				Trigger_Right;

		float64				Tumbstick_LeftX;
		float64				Tumbstick_LeftY;
		float64				Tumbstick_RightX;
		float64				Tumbstick_RightY;
	};

	public ref class VirtualController sealed
	{
	public:
		VirtualController(_In_ WOtech::InputManager^ input);

		void setCurrentInput(_In_ Current_Input_Device current);
		Current_Input_Device getCurrent();
		Virtual_Controller_State getState();

		// Gamepad
		void bindGamepad(_In_ Gamepad_Index number);

		// Keyboard and Mice
		void bindKeyboardtoButton(_In_ Virtual_Controller_Buttons target, _In_ Windows::System::VirtualKey key);
		void bindKeyboardtoTrigger(_In_ Virtual_Controller_Triggers target, _In_ Windows::System::VirtualKey key);
		void bindKeyboardtoTumbstick(_In_ Virtual_Controller_Sticks target, _In_ Windows::System::VirtualKey keyUP, _In_ Windows::System::VirtualKey keyDOWN, _In_ Windows::System::VirtualKey keyLEFT, _In_ Windows::System::VirtualKey keyRIGHT);

		void bindMousetoButton(_In_ Virtual_Controller_Buttons target, _In_ Windows::Foundation::Rect area);
		void bindMouseKeytoButton(_In_ Virtual_Controller_Buttons target, _In_ WOtech::VirtualKey_Mouse key);
		void bindMouseWheeltoTrigger(_In_ Virtual_Controller_Triggers target);
		void bindMousetoTumbstick(_In_ Virtual_Controller_Sticks target);

		// Touch and Pen
		void bindTouchtoButton(_In_ Virtual_Controller_Buttons target, _In_ Windows::Foundation::Rect area);
		void bindTouchtoTrigger(_In_ Virtual_Controller_Triggers target, _In_ Windows::Foundation::Rect Area);
		void bindTouchtoTumbstick(_In_ Virtual_Controller_Sticks target, _In_ Windows::Foundation::Point center, _In_ float32 radius);

	internal:

	private:
		~VirtualController();

		void Update();

		void UpdateGamepad();
		void UpdateKeyboard();
		void UpdateMouse();
		void UpdateTouch();
		void UpdatePen();

	private:
		WOtech::InputManager^														m_inputManager;

		Virtual_Controller_State													m_state;

		Current_Input_Device														m_currentInput;
		WOtech::Gamepad_Index														m_currentGamepad;

		struct virtual_Stick_keyboard
		{
			Windows::System::VirtualKey up;
			Windows::System::VirtualKey down;
			Windows::System::VirtualKey left;
			Windows::System::VirtualKey right;
		};
		std::map<Virtual_Controller_Buttons, Windows::System::VirtualKey>			m_keyboardButtonbinding;
		std::map<Virtual_Controller_Triggers, Windows::System::VirtualKey>			m_keyboardTriggerbinding;
		std::map<Virtual_Controller_Sticks, virtual_Stick_keyboard>					m_keyboardStickbinding;

		std::map<Virtual_Controller_Buttons, WOtech::VirtualKey_Mouse>				m_mouseKeybinding;
		std::map<Virtual_Controller_Buttons, Windows::Foundation::Rect>				m_mouseButtonbinding;
		WOtech::Virtual_Controller_Triggers											m_mouseWheelbinding;
		WOtech::Virtual_Controller_Sticks											m_mousebinding;

		std::map<Virtual_Controller_Buttons, Windows::Foundation::Rect>				m_touchButtonbinding;
		std::map<Virtual_Controller_Triggers, Windows::Foundation::Rect>			m_touchTriggerbinding;
		UINT																		m_currentTriggerLeftID;
		UINT																		m_currentTriggerRightID;

		struct virtual_Stick_touch
		{
			Windows::Foundation::Point center;
			float32 radius;
		};
		std::map<Virtual_Controller_Sticks, virtual_Stick_touch>					m_touchStickbinding;
		UINT																		m_currentStickLeftID;
		UINT																		m_currentStickRightID;
	};
};
#endif
