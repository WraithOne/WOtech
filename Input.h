////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: Input.h
///
///			Created:	01.05.2014
///			Edited:		22.11.2016
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_INPUT_H
#define WO_INPUT_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"

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
		Windows::Foundation::Rect PhysicalRect;
		Windows::Foundation::Rect ScreenRect;
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

	public value struct PointerPosition
	{
		float32 PointerX;
		float32 PointerY;
	};
	public value struct MousePosition
	{
		int32 MouseX;
		int32 MouseY;
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

		// Pointer
		Platform::Boolean PenConnected();
		PointerPosition PenLocation();
		int32 PenWheelPosition();
		Platform::Boolean PenPressed();
		Platform::Boolean PenButtonDown(_In_ Windows::System::VirtualKey Button);
		Platform::Boolean PenButtonUp(_In_ Windows::System::VirtualKey Button);

		// Mouse
		Platform::Boolean MouseConnected();
		MousePosition MouseDelta();
		Platform::Boolean MouseButtonPressed();
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

		// Mouse + Pointer
		void OnPointerPressed(_In_ Windows::UI::Core::CoreWindow^ Sender, _In_ Windows::UI::Core::PointerEventArgs^ Args);
		void OnPointerMoved(_In_ Windows::UI::Core::CoreWindow^ Sender, _In_ Windows::UI::Core::PointerEventArgs^ Args);
		void OnPointerReleased(_In_ Windows::UI::Core::CoreWindow^ Sender, _In_ Windows::UI::Core::PointerEventArgs^ Args);
		void OnPointerWheelChanged(_In_ Windows::UI::Core::CoreWindow^ Sender, _In_ Windows::UI::Core::PointerEventArgs^ Args);
		void OnMouseMoved(_In_ Windows::Devices::Input::MouseDevice^ MouseDevice, _In_ Windows::Devices::Input::MouseEventArgs^ Args);

		// Keyboard
		void OnKeyDown(_In_ Windows::UI::Core::CoreWindow^ Sender, _In_ Windows::UI::Core::KeyEventArgs^ Args);
		void OnKeyUp(_In_ Windows::UI::Core::CoreWindow^ Sender, _In_ Windows::UI::Core::KeyEventArgs^ Args);

		// Hardware back button is only present on some device families such as Phone.
		void OnHardwareBackButtonPressed(_In_ Platform::Object^ Sender, _In_ Windows::Phone::UI::Input::BackPressedEventArgs^ Args);

		// Gamepad
		void OnGamepadAdded(_In_ Platform::Object^ Sender, _In_ Windows::Gaming::Input::Gamepad^ Gamepad);
		void OnGamepadRemoved(_In_ Platform::Object^ Sender, _In_ Windows::Gaming::Input::Gamepad^ Gamepad);

	private:
		Platform::Agile<Windows::UI::Core::CoreWindow> m_window;

		Platform::Boolean m_isInitialized;

		// HardwarebackButton
		Platform::Boolean m_hwbbPressed;
		Platform::Boolean m_hwbbConfirmed;

		// Keyboard
		Windows::Devices::Input::KeyboardCapabilities^ m_keyBoardCapabilities;
		Windows::System::VirtualKey	m_keyDown;
		Windows::System::VirtualKey	m_keyUp;

		// Touch
		Windows::Devices::Input::TouchCapabilities^ m_touchCapabilities;

		// Pointer a.k.a. Pen
		Windows::Devices::Input::PointerDevice^	m_pointerDevice;
		Platform::Boolean m_pointerpressed;
		Windows::UI::Input::PointerPoint^ m_pointer;
		Windows::UI::Input::PointerPointProperties^ m_pointerProparties;

		// Mouse
		Windows::Devices::Input::MouseCapabilities^	m_mouseCapabilities;
		DirectX::XMINT2	m_mouseDelta;
		DirectX::XMINT2	m_mouseLastDelta;

		// Gamepad
		static const uint32	MAX_PLAYER_COUNT = 8;
		Windows::Gaming::Input::Gamepad^ m_gamePad[MAX_PLAYER_COUNT];
	};//class InputClass
}// namespace WOtech

#endif
