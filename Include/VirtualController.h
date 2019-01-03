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
///			Edited:		28.08.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_VIRTUALCONTROLLER_H
#define WO_VIRTUALCONTROLLER_H

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <Input.h>

namespace WOtech
{
	public enum class CURRENT_INPUT_DEVICE
	{
		UNSPECIFIED,
		GAMEPAD,
		KEYBOARDANDMOUSE,
		TOUCH,
		PEN,
	};
	public enum class VIRTUAL_CONTROLLER_BUTTONS
	{
		A,
		B,
		X,
		Y,
		LEFTSTICK,
		RIGHTSTICK,
		LEFTSHOULDER,
		RIGHTSHOULDER,
		VIEW,
		MENU,
		DPAD_UP,
		DPAD_DOWN,
		DPAD_LEFT,
		DPAD_RIGHT
	};
	public enum class VIRTUAL_CONTROLLER_TRIGGERS
	{
		LEFT,
		RIGHT
	};
	public enum class VIRTUAL_CONTROLLER_THUMBSTICKS
	{
		LEFT,
		RIGHT
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

		void setCurrentInput(_In_ CURRENT_INPUT_DEVICE current);
		CURRENT_INPUT_DEVICE getCurrent();
		Virtual_Controller_State getState();

		// Gamepad
		void bindGamepad(_In_ GAMEPAD_INDEX number);

		// Keyboard and Mice
		void bindKeyboardtoButton(_In_ VIRTUAL_CONTROLLER_BUTTONS target, _In_ Windows::System::VirtualKey key);
		void bindKeyboardtoTrigger(_In_ VIRTUAL_CONTROLLER_TRIGGERS target, _In_ Windows::System::VirtualKey key);
		void bindKeyboardtoThumbstick(_In_ VIRTUAL_CONTROLLER_THUMBSTICKS target, _In_ Windows::System::VirtualKey keyUP, _In_ Windows::System::VirtualKey keyDOWN, _In_ Windows::System::VirtualKey keyLEFT, _In_ Windows::System::VirtualKey keyRIGHT);

		void bindMousetoButton(_In_ VIRTUAL_CONTROLLER_BUTTONS target, _In_ Windows::Foundation::Rect area);
		void bindMouseKeytoButton(_In_ VIRTUAL_CONTROLLER_BUTTONS target, _In_ WOtech::VIRTUALKEY_MOUSE key);
		void bindMouseWheeltoTrigger(_In_ VIRTUAL_CONTROLLER_TRIGGERS target);
		void bindMousetoThumbstick(_In_ VIRTUAL_CONTROLLER_THUMBSTICKS target);

		// Touch and Pen
		void bindTouchtoButton(_In_ VIRTUAL_CONTROLLER_BUTTONS target, _In_ Windows::Foundation::Rect area);
		void bindTouchtoTrigger(_In_ VIRTUAL_CONTROLLER_TRIGGERS target, _In_ Windows::Foundation::Rect Area);
		void bindTouchtoThumbstick(_In_ VIRTUAL_CONTROLLER_THUMBSTICKS target, _In_ Windows::Foundation::Point center, _In_ float32 radius);

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
		WOtech::InputManager^												m_inputManager;

		Virtual_Controller_State											m_state;

		CURRENT_INPUT_DEVICE												m_currentInput;
		WOtech::GAMEPAD_INDEX												m_currentGamepad;

		struct virtual_Stick_keyboard
		{
			Windows::System::VirtualKey up;
			Windows::System::VirtualKey down;
			Windows::System::VirtualKey left;
			Windows::System::VirtualKey right;
		};
		std::map<VIRTUAL_CONTROLLER_BUTTONS, Windows::System::VirtualKey>	m_keyboardButtonbinding;
		std::map<VIRTUAL_CONTROLLER_TRIGGERS, Windows::System::VirtualKey>	m_keyboardTriggerbinding;
		std::map<VIRTUAL_CONTROLLER_THUMBSTICKS, virtual_Stick_keyboard>	m_keyboardStickbinding;

		std::map<VIRTUAL_CONTROLLER_BUTTONS, WOtech::VIRTUALKEY_MOUSE>		m_mouseKeybinding;
		std::map<VIRTUAL_CONTROLLER_BUTTONS, Windows::Foundation::Rect>		m_mouseButtonbinding;
		WOtech::VIRTUAL_CONTROLLER_TRIGGERS									m_mouseWheelbinding;
		WOtech::VIRTUAL_CONTROLLER_THUMBSTICKS								m_mousebinding;

		std::map<VIRTUAL_CONTROLLER_BUTTONS, Windows::Foundation::Rect>		m_touchButtonbinding;
		std::map<VIRTUAL_CONTROLLER_TRIGGERS, Windows::Foundation::Rect>	m_touchTriggerbinding;
		UINT																m_currentTriggerLeftID;
		UINT																m_currentTriggerRightID;

		struct virtual_Stick_touch
		{
			Windows::Foundation::Point center;
			float32 radius;
		};
		std::map<VIRTUAL_CONTROLLER_THUMBSTICKS, virtual_Stick_touch>		m_touchStickbinding;
		UINT																m_currentStickLeftID;
		UINT																m_currentStickRightID;
	};
};
#endif
