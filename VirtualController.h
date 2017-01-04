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
		public enum class Current_Input
		{
			Gamepad = 0,
			TouchandPen,
			KeyboardandMouse
		};

		public value struct Virtual_Gamepad_Buttons
		{
			Platform::Boolean A;
			Platform::Boolean B;
			Platform::Boolean X;
			Platform::Boolean Y;
			Platform::Boolean LeftStick;
			Platform::Boolean RightStick;
			Platform::Boolean LeftShoulder;
			Platform::Boolean RightShoulder;
			Platform::Boolean View;
			Platform::Boolean Menu;
		};
		public value struct Virtual_Gamepad_DPad
		{
			Platform::Boolean Up;
			Platform::Boolean Down;
			Platform::Boolean Left;
			Platform::Boolean Right;
		};
		public value struct Virtual_Gamepad_Trigger_State
		{
			float64 Left;
			float64 Right;
		};
		public value struct Virtual_Gamepad_Tumbstick_State
		{
			float64 LeftX;
			float64 LeftY;
			float64 RightX;
			float64 RightY;
		};
		public value struct Virtual_Gamepad
		{
			Virtual_Gamepad_Buttons Buttons;
			Virtual_Gamepad_DPad DPad;
			Virtual_Gamepad_Trigger_State Triggers;
			Virtual_Gamepad_Tumbstick_State Tumbsticks;
		};

		public ref class VirtualController sealed
		{
		public:
			VirtualController();
			void setCurrentInput(_In_ Current_Input current);
			Current_Input getCurrent();

			Virtual_Gamepad getState();

			// Gamepad

			// Keyboard and Mice

			// Touch and Pen

		internal:

		private:
			
		private:
			Virtual_Gamepad	m_state;
			Current_Input	m_currentInput;
		};
	};
};
#endif

