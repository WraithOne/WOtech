////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: Input.h
///
///			Created:	01.05.2014
///			Edited:		03.01.2017
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_INPUT_H
#define WO_INPUT_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "DXWrapper.h"

namespace WOtech
{
	public value struct TouchCapabilities
	{
		Platform::Boolean isPresent;
		uint32 MinimumContacts;
	};
	public value struct PenCapabilities
	{
		Platform::Boolean isPresent;
		Windows::Devices::Input::PointerDeviceType DeviceType;
		Platform::Boolean isIntegrated;
		uint32 MaximumContacts;
		WOtech::DXWrapper::RECT PhysicalRect;
		WOtech::DXWrapper::RECT ScreenRect;
	};
	public value struct MouseCapabilities
	{
		Platform::Boolean isPresent;
		Platform::Boolean isVerticalWheelPresent;
		Platform::Boolean isHorizontalWheelPresent;
		Platform::Boolean SwapButtons;
		uint32 NumberofButtons;
	};
	public value struct KeyboardCapabilities
	{
		Platform::Boolean isPresent;
	};

	public value struct Pointer_Position
	{
		float32 X;
		float32 Y;
	};

	public value struct Touch_State
	{
		UINT pointerID;
		Pointer_Position position;
	};

	public value struct Mouse_Position
	{
		int32 X;
		int32 Y;
	};
	public value struct Mouse_Buttons
	{
		Platform::Boolean LeftButton;
		Platform::Boolean RightButton;
		Platform::Boolean MiddleButton;
		Platform::Boolean X1Button;
		Platform::Boolean X2Button;
	};
	public value struct Mouse_State
	{
		UINT pointerID;
		Mouse_Position position;
		Mouse_Buttons buttons;
		int wheeldelta;
	};

	public value struct Pen_State
	{
		UINT pointerID;
		Pointer_Position position;
		Platform::Boolean BarrelButton;
		Platform::Boolean isErazer;
		float pressure;
	};

	public enum class GamepadIndex
	{
		PlayerOne,
		PlayerTwo,
		PlayerThree,
		PlayerFour,
		PlayerFive,
		PlayerSix,
		PlayerSeven,
		PlayerEight
	};
	public value struct Gamepad_Buttons
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
	public value struct Gamepad_DPad
	{
		Platform::Boolean Up;
		Platform::Boolean Down;
		Platform::Boolean Left;
		Platform::Boolean Right;
	};
	public value struct Gamepad_Trigger_State
	{
		float64 Left;
		float64 Right;
	};
	public value struct Gamepad_Tumbstick_State
	{
		float64 LeftX;
		float64 LeftY;
		float64 RightX;
		float64 RightY;
	};
	public value struct Gamepad_State
	{
		Platform::Boolean Connected;
		Platform::Boolean isWireless;
		UINT64 TimeStamp;
		Gamepad_Buttons Buttons;
		Gamepad_DPad DPad;
		Gamepad_Tumbstick_State tumbsticks;
		Gamepad_Trigger_State triggers;
	};
	
	public ref class InputManager sealed
	{
	public:
		InputManager();

		void SuspendInput();
		void ResumeInput();

		// Hardwarebackbutton
		Platform::Boolean HardwarebackbuttonConnceted();
		void HardwarebackbuttonUse(_In_ Platform::Boolean comfirm);
		Platform::Boolean HardwarebackbuttonInUse();
		Platform::Boolean HardwarebackbuttonPressed();

		// SytemOverlay
		void SystemoverlaySupress(_In_ Platform::Boolean confirm);
		Platform::Boolean SystemoverlaySupressed();

		// Keyboard
		Platform::Boolean KeyboardConnected();
		Platform::Boolean KeyDown(_In_ Windows::System::VirtualKey Key);
		Platform::Boolean KeyUp(_In_ Windows::System::VirtualKey Key);

		// Touch
		Platform::Boolean TouchConnected();
		Touch_State getTouchState();// TODO: more then 1 point
		// Pointer
		Platform::Boolean PenConnected();
		Pen_State getPenState();// TODO: more then 1 point if needed

		// Mouse
		Platform::Boolean MouseConnected();
		Mouse_State getMouseState();
		void MouseShowCursor(_In_ Platform::Boolean show);
		Platform::Boolean MouseCursorVisible();

		// Gamepad
		Platform::Boolean GamepadConnected(_In_ GamepadIndex PlayerIndex);
		Gamepad_State GamepadState(_In_ GamepadIndex PlayerIndex);
		void GamepadSetVibration(_In_ GamepadIndex PlayerIndex, _In_ Windows::Gaming::Input::GamepadVibration Vibration);
		Platform::Boolean GamepadButtonDown(_In_ GamepadIndex PlayerIndex, _In_ Windows::Gaming::Input::GamepadButtons Button);
		Platform::Boolean GamepadButtonUp(_In_ GamepadIndex PlayerIndex, _In_ Windows::Gaming::Input::GamepadButtons Button);
		Gamepad_Trigger_State GamepadTigger(_In_ GamepadIndex PlayerIndex);
		Gamepad_Tumbstick_State GamePadTumbStick(_In_ GamepadIndex PlayerIndex);


		// OrientationSensor
		Platform::Boolean OrientationSensorConnected();
		void ActivateOrientationSensor(_In_ uint32 interval);
		void DeactivateOrientationSensor();
		Platform::Boolean OrientationSensorActive();
		void OrientationSensorQuaternion(_In_ Windows::Devices::Sensors::SensorQuaternion^ quaternion);
		void OrientationSensorMatrix(_Out_ Windows::Devices::Sensors::SensorRotationMatrix^ martix);

	private:
		~InputManager();
		void Initialize();
		void ScanDeviceCapabilities();
		void ScanGamePad();

		// Pointer
		void OnPointerPressed(_In_ Windows::UI::Core::CoreWindow^ Sender, _In_ Windows::UI::Core::PointerEventArgs^ Args);
		void OnPointerMoved(_In_ Windows::UI::Core::CoreWindow^ Sender, _In_ Windows::UI::Core::PointerEventArgs^ Args);
		void OnPointerReleased(_In_ Windows::UI::Core::CoreWindow^ Sender, _In_ Windows::UI::Core::PointerEventArgs^ Args);
		void OnPointerEntered(_In_ Windows::UI::Core::CoreWindow^ Sender, _In_ Windows::UI::Core::PointerEventArgs^ Args);
		void OnPointerExited(_In_ Windows::UI::Core::CoreWindow^ Sender, _In_ Windows::UI::Core::PointerEventArgs^ Args);
		void OnPointerWheelChanged(_In_ Windows::UI::Core::CoreWindow^ Sender, _In_ Windows::UI::Core::PointerEventArgs^ Args);
		void OnMouseMoved(_In_ Windows::Devices::Input::MouseDevice^ MouseDevice, _In_ Windows::Devices::Input::MouseEventArgs^ Args);

		void UpdatePointerDevices(_In_ Windows::UI::Input::PointerPoint^ device);
		void RemovePointerDevice(_In_ Windows::UI::Input::PointerPoint^ device);
		// Keyboard
		void OnKeyDown(_In_ Windows::UI::Core::CoreWindow^ Sender, _In_ Windows::UI::Core::KeyEventArgs^ Args);
		void OnKeyUp(_In_ Windows::UI::Core::CoreWindow^ Sender, _In_ Windows::UI::Core::KeyEventArgs^ Args);

		// Hardware back button is only present on some device families such as Phone.
		void OnHardwareBackButtonPressed(_In_ Platform::Object^ Sender, _In_ Windows::Phone::UI::Input::BackPressedEventArgs^ Args);

		// Gamepad
		void OnGamepadAdded(_In_ Platform::Object^ Sender, _In_ Windows::Gaming::Input::Gamepad^ Gamepad);
		void OnGamepadRemoved(_In_ Platform::Object^ Sender, _In_ Windows::Gaming::Input::Gamepad^ Gamepad);

	private:
		Platform::Agile<Windows::UI::Core::CoreWindow>		m_window;

		Platform::Boolean									m_isInitialized;

		// HardwarebackButton
		Platform::Boolean									m_hwbbPressed;
		Platform::Boolean									m_hwbbConfirmed;

		// Keyboard
		Windows::Devices::Input::KeyboardCapabilities^		m_keyBoardCapabilities;
		Windows::System::VirtualKey							m_keyboardKeys;

		// Touch
		Windows::Devices::Input::TouchCapabilities^			m_touchCapabilities;
		// Mouse
		Windows::Devices::Input::MouseCapabilities^			m_mouseCapabilities;
		Mouse_Position										m_mouseDelta;
		// Pointer a.k.a. Touch/Pen/Mouse
		std::map <UINT, Windows::UI::Input::PointerPoint^>	m_pointerdevices;

		// Gamepad
		static const uint32	MAX_PLAYER_COUNT =				8;
		Windows::Gaming::Input::Gamepad^					m_gamePad[MAX_PLAYER_COUNT];
	};//class InputClass
}// namespace WOtech

#endif
