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
#ifndef WO_VIRTUALCONTROLLER_H
#define WO_VIRTUALCONTROLLER_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Input.h"
#include "Graphic.h"

namespace WOtech
{
	namespace Gameframework
	{
		public enum class Current_Input_Device
		{
			Gamepad = 0,
			KeyboardandMouse,
			Touch,
			Pen,
			
		};
		public enum class Virtual_Controller_Buttons
		{
			A = 0,
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

		public value struct Virtual_Controller
		{
			Platform::Boolean isConnected;
			Platform::Boolean isWireless;

			Platform::Boolean Button_A;
			Platform::Boolean Button_B;
			Platform::Boolean Button_X;
			Platform::Boolean Button_Y;
			Platform::Boolean Button_LeftStick;
			Platform::Boolean Button_RightStick;
			Platform::Boolean Button_LeftShoulder;
			Platform::Boolean Button_RightShoulder;
			Platform::Boolean Button_View;
			Platform::Boolean Button_Menu;

			Platform::Boolean DPad_Up;
			Platform::Boolean DPad_Down;
			Platform::Boolean DPad_Left;
			Platform::Boolean DPad_Right;

			float64 Trigger_Left;
			float64 Trigger_Right;

			float64 Tumbstick_LeftX;
			float64 Tumbstick_LeftY;
			float64 Tumbstick_RightX;
			float64 Tumbstick_RightY;
		};

		public ref class VirtualController sealed
		{
		public:
			VirtualController(_In_ WOtech::InputManager^ Input);

			void setCurrentInput(_In_ Current_Input_Device Current);
			Current_Input_Device getCurrent();

			Virtual_Controller getState();

			// Gamepad
			void bindGamepad(_In_ Gamepad_Index number);

			// Keyboard and Mice
			void bindKeyboardKey(_In_ Virtual_Controller_Buttons Target, _In_ Windows::System::VirtualKey Key);
			// Touch and Pen
			void bindTouchArea(_In_ Virtual_Controller_Buttons Target, _In_ WOtech::DXWrapper::RECT Area);

		internal:

		private:
			void Update();

			void UpdateGamepad();
			void UpdateKeyboard();
			void UpdateMouse();
			void UpdateTouch();
			void UpdatePen();
			
		private:
			WOtech::InputManager^												m_inputManager;

			Virtual_Controller													m_state;

			Current_Input_Device												m_currentInput;
			WOtech::Gamepad_Index												m_currentGamepad;
			
			std::map<Virtual_Controller_Buttons, Windows::System::VirtualKey>	m_keyboardbinding;
		};
	};
};
#endif

