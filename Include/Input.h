////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Input.h
///
///			Description:
///
///			Created:	01.05.2014
///			Edited:		29.01.2017
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
	public value struct Touch_Capabilities
	{
		Platform::Boolean isPresent;
		uint32 MinimumContacts;
	};
	public value struct Pen_Capabilities
	{
		Platform::Boolean isPresent;
		Windows::Devices::Input::PointerDeviceType DeviceType;
		Platform::Boolean isIntegrated;
		uint32 MaximumContacts;
		WOtech::DXWrapper::RECT PhysicalRect;
		WOtech::DXWrapper::RECT ScreenRect;
	};
	public value struct Mouse_Capabilities
	{
		Platform::Boolean isPresent;
		Platform::Boolean isVerticalWheelPresent;
		Platform::Boolean isHorizontalWheelPresent;
		Platform::Boolean SwapButtons;
		uint32 NumberofButtons;
	};
	public value struct Keyboard_Capabilities
	{
		Platform::Boolean isPresent;
	};

	public value struct Keyboard_State
	{
		Platform::Boolean Back;					// VK_BACK, 0x8
		Platform::Boolean Tab;					// VK_TAB, 0x9
		Platform::Boolean Enter;				// VK_RETURN, 0xD
		Platform::Boolean Pause;				// VK_PAUSE, 0x13
		Platform::Boolean CapsLock;				// VK_CAPITAL, 0x14
		Platform::Boolean Kana;					// VK_KANA, 0x15
		Platform::Boolean Kanji;				// VK_KANJI, 0x19
		Platform::Boolean Escape;				// VK_ESCAPE, 0x1B
		Platform::Boolean ImeConvert;			// VK_CONVERT, 0x1C
		Platform::Boolean ImeNoConvert;			// VK_NONCONVERT, 0x1D
		Platform::Boolean Space;				// VK_SPACE, 0x20
		Platform::Boolean PageUp;				// VK_PRIOR, 0x21
		Platform::Boolean PageDown;				// VK_NEXT, 0x22
		Platform::Boolean End;					// VK_END, 0x23
		Platform::Boolean Home;					// VK_HOME, 0x24
		Platform::Boolean Left;					// VK_LEFT, 0x25
		Platform::Boolean Up;					// VK_UP, 0x26
		Platform::Boolean Right;				// VK_RIGHT, 0x27
		Platform::Boolean Down;					// VK_DOWN, 0x28
		Platform::Boolean Select;				// VK_SELECT, 0x29
		Platform::Boolean Print;				// VK_PRINT, 0x2A
		Platform::Boolean Execute;				// VK_EXECUTE, 0x2B
		Platform::Boolean PrintScreen;			// VK_SNAPSHOT, 0x2C
		Platform::Boolean Insert;				// VK_INSERT, 0x2D
		Platform::Boolean Delete;				// VK_DELETE, 0x2E
		Platform::Boolean Help;					// VK_HELP, 0x2F
		Platform::Boolean D0;					// 0x30
		Platform::Boolean D1;					// 0x31
		Platform::Boolean D2;					// 0x32
		Platform::Boolean D3;					// 0x33
		Platform::Boolean D4;					// 0x34
		Platform::Boolean D5;					// 0x35
		Platform::Boolean D6;					// 0x36
		Platform::Boolean D7;					// 0x37
		Platform::Boolean D8;					// 0x38
		Platform::Boolean D9;					// 0x39
		Platform::Boolean A;					// 0x41
		Platform::Boolean B;					// 0x42
		Platform::Boolean C;					// 0x43
		Platform::Boolean D;					// 0x44
		Platform::Boolean E;					// 0x45
		Platform::Boolean F;					// 0x46
		Platform::Boolean G;					// 0x47
		Platform::Boolean H;					// 0x48
		Platform::Boolean I;					// 0x49
		Platform::Boolean J;					// 0x4A
		Platform::Boolean K;					// 0x4B
		Platform::Boolean L;					// 0x4C
		Platform::Boolean M;					// 0x4D
		Platform::Boolean N;					// 0x4E
		Platform::Boolean O;					// 0x4F
		Platform::Boolean P;					// 0x50
		Platform::Boolean Q;					// 0x51
		Platform::Boolean R;					// 0x52
		Platform::Boolean S;					// 0x53
		Platform::Boolean T;					// 0x54
		Platform::Boolean U;					// 0x55
		Platform::Boolean V;					// 0x56
		Platform::Boolean W;					// 0x57
		Platform::Boolean X;					// 0x58
		Platform::Boolean Y;					// 0x59
		Platform::Boolean Z;					// 0x5A
		Platform::Boolean LeftWindows;			// VK_LWIN, 0x5B
		Platform::Boolean RightWindows;			// VK_RWIN, 0x5C
		Platform::Boolean Apps;					// VK_APPS, 0x5D
		Platform::Boolean Sleep;				// VK_SLEEP, 0x5F
		Platform::Boolean NumPad0;				// VK_NUMPAD0, 0x60
		Platform::Boolean NumPad1;				// VK_NUMPAD1, 0x61
		Platform::Boolean NumPad2;				// VK_NUMPAD2, 0x62
		Platform::Boolean NumPad3;				// VK_NUMPAD3, 0x63
		Platform::Boolean NumPad4;				// VK_NUMPAD4, 0x64
		Platform::Boolean NumPad5;				// VK_NUMPAD5, 0x65
		Platform::Boolean NumPad6;				// VK_NUMPAD6, 0x66
		Platform::Boolean NumPad7;				// VK_NUMPAD7, 0x67
		Platform::Boolean NumPad8;				// VK_NUMPAD8, 0x68
		Platform::Boolean NumPad9;				// VK_NUMPAD9, 0x69
		Platform::Boolean Multiply;				// VK_MULTIPLY, 0x6A
		Platform::Boolean Add;					// VK_ADD, 0x6B
		Platform::Boolean Separator;			// VK_SEPARATOR, 0x6C
		Platform::Boolean Subtract;				// VK_SUBTRACT, 0x6D
		Platform::Boolean Decimal;				// VK_DECIMANL, 0x6E
		Platform::Boolean Divide;				// VK_DIVIDE, 0x6F
		Platform::Boolean F1;					// VK_F1, 0x70
		Platform::Boolean F2;					// VK_F2, 0x71
		Platform::Boolean F3;					// VK_F3, 0x72
		Platform::Boolean F4;					// VK_F4, 0x73
		Platform::Boolean F5;					// VK_F5, 0x74
		Platform::Boolean F6;					// VK_F6, 0x75
		Platform::Boolean F7;					// VK_F7, 0x76
		Platform::Boolean F8;					// VK_F8, 0x77
		Platform::Boolean F9;					// VK_F9, 0x78
		Platform::Boolean F10;					// VK_F10, 0x79
		Platform::Boolean F11;					// VK_F11, 0x7A
		Platform::Boolean F12;					// VK_F12, 0x7B
		Platform::Boolean F13;					// VK_F13, 0x7C
		Platform::Boolean F14;					// VK_F14, 0x7D
		Platform::Boolean F15;					// VK_F15, 0x7E
		Platform::Boolean F16;					// VK_F16, 0x7F
		Platform::Boolean F17;					// VK_F17, 0x80
		Platform::Boolean F18;					// VK_F18, 0x81
		Platform::Boolean F19;					// VK_F19, 0x82
		Platform::Boolean F20;					// VK_F20, 0x83
		Platform::Boolean F21;					// VK_F21, 0x84
		Platform::Boolean F22;					// VK_F22, 0x85
		Platform::Boolean F23;					// VK_F23, 0x86
		Platform::Boolean F24;					// VK_F24, 0x87
		Platform::Boolean NumLock;				// VK_NUMLOCK, 0x90
		Platform::Boolean Scroll;				// VK_SCROLL, 0x91
		Platform::Boolean LeftShift;			// VK_LSHIFT, 0xA0
		Platform::Boolean RightShift;			// VK_RSHIFT, 0xA1
		Platform::Boolean LeftControl;			// VK_LCONTROL, 0xA2
		Platform::Boolean RightControl;			// VK_RCONTROL, 0xA3
		Platform::Boolean LeftAlt;				// VK_LMENU, 0xA4
		Platform::Boolean RightAlt;				// VK_RMENU, 0xA5
		Platform::Boolean BrowserBack;			// VK_BROWSER_BACK, 0xA6
		Platform::Boolean BrowserForward;		// VK_BROWSER_FORWARD, 0xA7
		Platform::Boolean BrowserRefresh;		// VK_BROWSER_REFRESH, 0xA8
		Platform::Boolean BrowserStop;			// VK_BROWSER_STOP, 0xA9
		Platform::Boolean BrowserSearch;		// VK_BROWSER_SEARCH, 0xAA
		Platform::Boolean BrowserFavorites;		// VK_BROWSER_FAVORITES, 0xAB
		Platform::Boolean BrowserHome;			// VK_BROWSER_HOME, 0xAC
		Platform::Boolean VolumeMute;			// VK_VOLUME_MUTE, 0xAD
		Platform::Boolean VolumeDown;			// VK_VOLUME_DOWN, 0xAE
		Platform::Boolean VolumeUp;				// VK_VOLUME_UP, 0xAF
		Platform::Boolean MediaNextTrack;		// VK_MEDIA_NEXT_TRACK, 0xB0
		Platform::Boolean MediaPreviousTrack;	// VK_MEDIA_PREV_TRACK, 0xB1
		Platform::Boolean MediaStop;			// VK_MEDIA_STOP, 0xB2
		Platform::Boolean MediaPlayPause;		// VK_MEDIA_PLAY_PAUSE, 0xB3
		Platform::Boolean LaunchMail;			// VK_LAUNCH_MAIL, 0xB4
		Platform::Boolean SelectMedia;			// VK_LAUNCH_MEDIA_SELECT, 0xB5
		Platform::Boolean LaunchApplication1;	// VK_LAUNCH_APP1, 0xB6
		Platform::Boolean LaunchApplication2;	// VK_LAUNCH_APP2, 0xB7
		Platform::Boolean OemSemicolon;			// VK_OEM_1, 0xBA
		Platform::Boolean OemPlus;				// VK_OEM_PLUS, 0xBB
		Platform::Boolean OemComma;				// VK_OEM_COMMA, 0xBC
		Platform::Boolean OemMinus;				// VK_OEM_MINUS, 0xBD
		Platform::Boolean OemPeriod;			// VK_OEM_PERIOD, 0xBE
		Platform::Boolean OemQuestion;			// VK_OEM_2, 0xBF
		Platform::Boolean OemTilde;				// VK_OEM_3, 0xC0
		Platform::Boolean OemOpenBrackets;		// VK_OEM_4, 0xDB
		Platform::Boolean OemPipe;				// VK_OEM_5, 0xDC
		Platform::Boolean OemCloseBrackets;		// VK_OEM_6, 0xDD
		Platform::Boolean OemQuotes;			// VK_OEM_7, 0xDE
		Platform::Boolean Oem8;					// VK_OEM_8, 0xDF
		Platform::Boolean OemBackslash;			// VK_OEM_102, 0xE2
		Platform::Boolean ProcessKey;			// VK_PROCESSKEY, 0xE5
		Platform::Boolean OemCopy;				// 0XF2
		Platform::Boolean OemAuto;				// 0xF3
		Platform::Boolean OemEnlW;				// 0xF4
		Platform::Boolean Attn;					// VK_ATTN, 0xF6
		Platform::Boolean Crsel;				// VK_CRSEL, 0xF7
		Platform::Boolean Exsel;				// VK_EXSEL, 0xF8
		Platform::Boolean EraseEof;				// VK_EREOF, 0xF9
		Platform::Boolean Play;					// VK_PLAY, 0xFA
		Platform::Boolean Zoom;					// VK_ZOOM, 0xFB
		Platform::Boolean Pa1;					// VK_PA1, 0xFD
		Platform::Boolean OemClear;				// VK_OEM_CLEAR, 0xFE
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

	public enum class Gamepad_Index
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
		void HardwarebackbuttonUse(_In_ Platform::Boolean Comfirm);
		Platform::Boolean HardwarebackbuttonInUse();
		Platform::Boolean HardwarebackbuttonPressed();

		// SytemOverlay
		void SystemoverlaySupress(_In_ Platform::Boolean Confirm);
		Platform::Boolean SystemoverlaySupressed();

		// Keyboard
		Platform::Boolean KeyboardConnected();
		Keyboard_State getKeyboardState();
		Platform::Boolean KeyDown(_In_ Windows::System::VirtualKey key);

		// Touch
		Platform::Boolean TouchConnected();
		Platform::Array<Touch_State>^ getTouchState();
		// Pointer
		Platform::Boolean PenConnected();
		Platform::Array<Pen_State>^ getPenState();

		// Mouse
		Platform::Boolean MouseConnected();
		Mouse_State getMouseState();
		void MouseShowCursor(_In_ Platform::Boolean Show);
		Platform::Boolean MouseCursorVisible();

		// Gamepad
		Platform::Boolean GamepadConnected(_In_ Gamepad_Index PlayerIndex);
		Gamepad_State GamepadState(_In_ Gamepad_Index PlayerIndex);
		void GamepadSetVibration(_In_ Gamepad_Index PlayerIndex, _In_ Windows::Gaming::Input::GamepadVibration Vibration);

		// OrientationSensor
		Platform::Boolean OrientationSensorConnected();
		void ActivateOrientationSensor(_In_ Windows::Devices::Sensors::SensorReadingType Type, _In_ Windows::Devices::Sensors::SensorOptimizationGoal Goal, _In_ uint32 Interval);
		void DeactivateOrientationSensor();
		Platform::Boolean OrientationSensorActive();
		void OrientationSensorQuaternion(_Out_ Windows::Devices::Sensors::SensorQuaternion^ Quaternion);
		void OrientationSensorMatrix(_Out_ Windows::Devices::Sensors::SensorRotationMatrix^ Matrix);

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

		void UpdatePointerDevices(_In_ Windows::UI::Input::PointerPoint^ Device);
		void RemovePointerDevice(_In_ Windows::UI::Input::PointerPoint^ Device);

		// Keyboard
		void OnKeyDown(_In_ Windows::UI::Core::CoreWindow^ Sender, _In_ Windows::UI::Core::KeyEventArgs^ Args);
		void OnKeyUp(_In_ Windows::UI::Core::CoreWindow^ Sender, _In_ Windows::UI::Core::KeyEventArgs^ Args);

		// Hardware back button is only present on some device families such as Phone.
		void OnHardwareBackButtonPressed(_In_ Platform::Object^ Sender, _In_ Windows::Phone::UI::Input::BackPressedEventArgs^ Args);

		// Orientation Sensor
		void ReadingChanged(_In_ Windows::Devices::Sensors::OrientationSensor^ Sender, _In_ Windows::Devices::Sensors::OrientationSensorReadingChangedEventArgs^ Args);

		// Gamepad
		void OnGamepadAdded(_In_ Platform::Object^ Sender, _In_ Windows::Gaming::Input::Gamepad^ Gamepad);
		void OnGamepadRemoved(_In_ Platform::Object^ Sender, _In_ Windows::Gaming::Input::Gamepad^ Gamepad);

	private:
		Platform::Agile<Windows::UI::Core::CoreWindow>			m_window;

		Platform::Boolean										m_isInitialized;

		// Keyboard
		Windows::Devices::Input::KeyboardCapabilities^			m_keyBoardCapabilities;
		Keyboard_State											m_keyboardState;

		// Touch
		Windows::Devices::Input::TouchCapabilities^				m_touchCapabilities;
		// Mouse
		Windows::Devices::Input::MouseCapabilities^				m_mouseCapabilities;
		Mouse_Position											m_mouseDelta;
		// Pointer a.k.a. Touch/Pen/Mouse
		std::map <UINT, Windows::UI::Input::PointerPoint^>		m_pointerdevices;

		// Orientation Sensor
		Windows::Devices::Sensors::OrientationSensor^			m_orientationSensor;
		Windows::Foundation::EventRegistrationToken				m_orientationToken;
		Windows::Devices::Sensors::OrientationSensorReading^	m_orientationSensorReading;
		Platform::Boolean										m_orientationActive;

		// HardwarebackButton
		Platform::Boolean										m_hwbbPressed;
		Platform::Boolean										m_hwbbConfirmed;

		// Gamepad
		static const uint32	MAX_PLAYER_COUNT = 8;
		Windows::Gaming::Input::Gamepad^						m_gamePad[MAX_PLAYER_COUNT];
	};//class InputClass
}// namespace WOtech

#endif
