////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Input.cpp
///
///			Description:
///
///			Created:	02.05.2014
///			Edited:		15.01.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Input.h"
#include "SystemManager.h"

using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Devices::Input;
using namespace Windows::Gaming::Input;
using namespace Windows::Foundation::Collections;
using namespace Windows::Phone::UI::Input;
using namespace Windows::UI::Input;
using namespace Platform;

namespace WOtech
{
	InputManager::InputManager()
	{
		SystemManager::Instance->AddInputManager(this);

		m_window = CoreWindow::GetForCurrentThread();

		Initialize();
	}

	void InputManager::SuspendInput()
	{
		for (UINT i = 0; i != sizeof(m_gamePad); i++)
		{
			m_gamePad[i] = nullptr;
		}
	}

	void InputManager::ResumeInput()
	{
		m_window = CoreWindow::GetForCurrentThread();
		ScanGamePad();
	}

	InputManager::~InputManager()
	{
		SystemManager::Instance->RemoveInputManager(this);
	}

	void InputManager::Initialize()
	{
		m_isInitialized = false;
		m_hwbbConfirmed = false;
		m_hwbbPressed = false;

		// opt in to receive touch/mouse events
		m_window->PointerPressed += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &InputManager::OnPointerPressed);
		m_window->PointerMoved += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &InputManager::OnPointerMoved);
		m_window->PointerReleased += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &InputManager::OnPointerReleased);
		m_window->PointerEntered += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &InputManager::OnPointerEntered);
		m_window->PointerExited += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &InputManager::OnPointerExited);
		m_window->PointerWheelChanged += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &InputManager::OnPointerWheelChanged);

		// opt in to receive key events
		m_window->KeyDown += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &InputManager::OnKeyDown);
		m_window->KeyUp += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &InputManager::OnKeyUp);
		// There is a separate handler for mouse only relative mouse movement events.
		MouseDevice::GetForCurrentView()->MouseMoved += ref new TypedEventHandler<MouseDevice^, MouseEventArgs^>(this, &InputManager::OnMouseMoved);

		// Detect game pad connection and disconnection events.
		Gamepad::GamepadAdded += ref new EventHandler<Gamepad^>(this, &InputManager::OnGamepadAdded);
		Gamepad::GamepadRemoved += ref new EventHandler<Gamepad^>(this, &InputManager::OnGamepadRemoved);

		// Scan for Capabilities
		ScanDeviceCapabilities();

		// Scan for Gamepads
		ScanGamePad();

		m_isInitialized = true;
	}

	void InputManager::ScanDeviceCapabilities()
	{
		m_keyBoardCapabilities = ref new Windows::Devices::Input::KeyboardCapabilities();
		m_touchCapabilities = ref new Windows::Devices::Input::TouchCapabilities();
		m_mouseCapabilities = ref new Windows::Devices::Input::MouseCapabilities();
	}

	void InputManager::SystemoverlaySupress(_In_ Platform::Boolean confirm)
	{
		if (confirm)
		{
			Windows::UI::ViewManagement::ApplicationView::GetForCurrentView()->TryEnterFullScreenMode();//>SuppressSystemOverlays = true;
			if (Windows::Foundation::Metadata::ApiInformation::IsTypePresent("Windows.UI.ViewManagement.StatusBar"))
#pragma warning(push)
#pragma warning (disable : 4014)
			{
				Windows::UI::ViewManagement::StatusBar::GetForCurrentView()->HideAsync();
			}
#pragma warning (pop)
		}
		else
		{
			Windows::UI::ViewManagement::ApplicationView::GetForCurrentView()->ExitFullScreenMode();//>SuppressSystemOverlays = false;
			if (Windows::Foundation::Metadata::ApiInformation::IsTypePresent("Windows.UI.ViewManagement.StatusBar"))
#pragma warning(push)
#pragma warning (disable : 4014)
			{
				Windows::UI::ViewManagement::StatusBar::GetForCurrentView()->ShowAsync();
			}
#pragma warning (pop)
		}
	}
	Platform::Boolean InputManager::SystemoverlaySupressed()
	{
		Platform::Boolean isSupressed = false;
		// isSupressed = Windows::UI::ViewManagement::ApplicationView::GetForCurrentView()->SuppressSystemOverlays TODO::hmmmm
		return isSupressed;
	}

	/// Events
	void InputManager::OnHardwareBackButtonPressed(_In_ Object^ Sender, _In_ BackPressedEventArgs^ Args)
	{
		UNREFERENCED_PARAMETER(Sender);

		if (m_hwbbConfirmed)
			Args->Handled = true;
		else
			Args->Handled = false;

		m_hwbbPressed = true;
	}

	void InputManager::ReadingChanged(_In_ Windows::Devices::Sensors::OrientationSensor ^ Sender, _In_ Windows::Devices::Sensors::OrientationSensorReadingChangedEventArgs ^ Args)
	{
		m_orientationSensorReading = Args->Reading;
	}

	inline void HandleKeys(_Inout_ WOtech::Keyboard_State* keystate, _In_ Windows::System::VirtualKey key, _In_ Boolean down)
	{
		switch (key)
		{
		case Windows::System::VirtualKey::None:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::LeftButton:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::RightButton:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::Cancel:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::MiddleButton:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::XButton1:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::XButton2:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::Back:
			keystate->Back = down;
			break;
		case Windows::System::VirtualKey::Tab:
			keystate->Tab = down;
			break;
		case Windows::System::VirtualKey::Clear:
			//keystate. = down;
			break;
		case Windows::System::VirtualKey::Enter:
			keystate->Enter = down;
			break;
		case Windows::System::VirtualKey::Shift:
			//keystate. = down;
			break;
		case Windows::System::VirtualKey::Control:
			//keystate. = down;
			break;
		case Windows::System::VirtualKey::Menu:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::Pause:
			keystate->Pause = down;
			break;
		case Windows::System::VirtualKey::CapitalLock:
			keystate->CapsLock = down;
			break;
		case Windows::System::VirtualKey::Kana:
			keystate->Kana = down;
			break;
			//case Windows::System::VirtualKey::Hangul:
				//keystate-> = down;
				//	break;
		case Windows::System::VirtualKey::Junja:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::Final:
			break;
			//case Windows::System::VirtualKey::Hanja:
				//keystate-> = down;
				//break;
		case Windows::System::VirtualKey::Kanji:
			keystate->Kanji = down;
			break;
		case Windows::System::VirtualKey::Escape:
			keystate->Escape = down;
			break;
		case Windows::System::VirtualKey::Convert:
			keystate->ImeConvert = down;
			break;
		case Windows::System::VirtualKey::NonConvert:
			keystate->ImeNoConvert = down;
			break;
		case Windows::System::VirtualKey::Accept:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::ModeChange:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::Space:
			keystate->Space = down;
			break;
		case Windows::System::VirtualKey::PageUp:
			keystate->PageUp = down;
			break;
		case Windows::System::VirtualKey::PageDown:
			keystate->PageDown = down;
			break;
		case Windows::System::VirtualKey::End:
			keystate->End = down;
			break;
		case Windows::System::VirtualKey::Home:
			keystate->Home = down;
			break;
		case Windows::System::VirtualKey::Left:
			keystate->Left = down;
			break;
		case Windows::System::VirtualKey::Up:
			keystate->Up = down;
			break;
		case Windows::System::VirtualKey::Right:
			keystate->Right = down;
			break;
		case Windows::System::VirtualKey::Down:
			keystate->Down = down;
			break;
		case Windows::System::VirtualKey::Select:
			keystate->Select = down;
			break;
		case Windows::System::VirtualKey::Print:
			keystate->Print = down;
			break;
		case Windows::System::VirtualKey::Execute:
			keystate->Execute = down;
			break;
		case Windows::System::VirtualKey::Snapshot:
			keystate->PrintScreen = down;
			break;
		case Windows::System::VirtualKey::Insert:
			keystate->Insert = down;
			break;
		case Windows::System::VirtualKey::Delete:
			keystate->Delete = down;
			break;
		case Windows::System::VirtualKey::Help:
			keystate->Help = down;
			break;
		case Windows::System::VirtualKey::Number0:
			keystate->D0 = down;
			break;
		case Windows::System::VirtualKey::Number1:
			keystate->D1 = down;
			break;
		case Windows::System::VirtualKey::Number2:
			keystate->D2 = down;
			break;
		case Windows::System::VirtualKey::Number3:
			keystate->D3 = down;
			break;
		case Windows::System::VirtualKey::Number4:
			keystate->D4 = down;
			break;
		case Windows::System::VirtualKey::Number5:
			keystate->D5 = down;
			break;
		case Windows::System::VirtualKey::Number6:
			keystate->D6 = down;
			break;
		case Windows::System::VirtualKey::Number7:
			keystate->D7 = down;
			break;
		case Windows::System::VirtualKey::Number8:
			keystate->D8 = down;
			break;
		case Windows::System::VirtualKey::Number9:
			keystate->D9 = down;
			break;
		case Windows::System::VirtualKey::A:
			keystate->A = down;
			break;
		case Windows::System::VirtualKey::B:
			keystate->B = down;
			break;
		case Windows::System::VirtualKey::C:
			keystate->C = down;
			break;
		case Windows::System::VirtualKey::D:
			keystate->D = down;
			break;
		case Windows::System::VirtualKey::E:
			keystate->E = down;
			break;
		case Windows::System::VirtualKey::F:
			keystate->F = down;
			break;
		case Windows::System::VirtualKey::G:
			keystate->G = down;
			break;
		case Windows::System::VirtualKey::H:
			keystate->H = down;
			break;
		case Windows::System::VirtualKey::I:
			keystate->I = down;
			break;
		case Windows::System::VirtualKey::J:
			keystate->J = down;
			break;
		case Windows::System::VirtualKey::K:
			keystate->K = down;
			break;
		case Windows::System::VirtualKey::L:
			keystate->L = down;
			break;
		case Windows::System::VirtualKey::M:
			keystate->M = down;
			break;
		case Windows::System::VirtualKey::N:
			keystate->N = down;
			break;
		case Windows::System::VirtualKey::O:
			keystate->O = down;
			break;
		case Windows::System::VirtualKey::P:
			keystate->P = down;
			break;
		case Windows::System::VirtualKey::Q:
			keystate->Q = down;
			break;
		case Windows::System::VirtualKey::R:
			keystate->R = down;
			break;
		case Windows::System::VirtualKey::S:
			keystate->S = down;
			break;
		case Windows::System::VirtualKey::T:
			keystate->T = down;
			break;
		case Windows::System::VirtualKey::U:
			keystate->U = down;
			break;
		case Windows::System::VirtualKey::V:
			keystate->V = down;
			break;
		case Windows::System::VirtualKey::W:
			keystate->W = down;
			break;
		case Windows::System::VirtualKey::X:
			keystate->X = down;
			break;
		case Windows::System::VirtualKey::Y:
			keystate->Y = down;
			break;
		case Windows::System::VirtualKey::Z:
			keystate->Z = down;
			break;
		case Windows::System::VirtualKey::LeftWindows:
			keystate->LeftWindows = down;
			break;
		case Windows::System::VirtualKey::RightWindows:
			keystate->RightWindows = down;
			break;
		case Windows::System::VirtualKey::Application:
			keystate->Apps = down;
			break;
		case Windows::System::VirtualKey::Sleep:
			keystate->Sleep = down;
			break;
		case Windows::System::VirtualKey::NumberPad0:
			keystate->NumPad0 = down;
			break;
		case Windows::System::VirtualKey::NumberPad1:
			keystate->NumPad1 = down;
			break;
		case Windows::System::VirtualKey::NumberPad2:
			keystate->NumPad2 = down;
			break;
		case Windows::System::VirtualKey::NumberPad3:
			keystate->NumPad3 = down;
			break;
		case Windows::System::VirtualKey::NumberPad4:
			keystate->NumPad4 = down;
			break;
		case Windows::System::VirtualKey::NumberPad5:
			keystate->NumPad5 = down;
			break;
		case Windows::System::VirtualKey::NumberPad6:
			keystate->NumPad6 = down;
			break;
		case Windows::System::VirtualKey::NumberPad7:
			keystate->NumPad7 = down;
			break;
		case Windows::System::VirtualKey::NumberPad8:
			keystate->NumPad8 = down;
			break;
		case Windows::System::VirtualKey::NumberPad9:
			keystate->NumPad9 = down;
			break;
		case Windows::System::VirtualKey::Multiply:
			keystate->Multiply = down;
			break;
		case Windows::System::VirtualKey::Add:
			keystate->Add = down;
			break;
		case Windows::System::VirtualKey::Separator:
			keystate->Separator = down;
			break;
		case Windows::System::VirtualKey::Subtract:
			keystate->Subtract = down;
			break;
		case Windows::System::VirtualKey::Decimal:
			keystate->Decimal = down;
			break;
		case Windows::System::VirtualKey::Divide:
			keystate->Divide = down;
			break;
		case Windows::System::VirtualKey::F1:
			keystate->F1 = down;
			break;
		case Windows::System::VirtualKey::F2:
			keystate->F2 = down;
			break;
		case Windows::System::VirtualKey::F3:
			keystate->F3 = down;
			break;
		case Windows::System::VirtualKey::F4:
			keystate->F4 = down;
			break;
		case Windows::System::VirtualKey::F5:
			keystate->F5 = down;
			break;
		case Windows::System::VirtualKey::F6:
			keystate->F6 = down;
			break;
		case Windows::System::VirtualKey::F7:
			keystate->F7 = down;
			break;
		case Windows::System::VirtualKey::F8:
			keystate->F8 = down;
			break;
		case Windows::System::VirtualKey::F9:
			keystate->F9 = down;
			break;
		case Windows::System::VirtualKey::F10:
			keystate->F10 = down;
			break;
		case Windows::System::VirtualKey::F11:
			keystate->F11 = down;
			break;
		case Windows::System::VirtualKey::F12:
			keystate->F12 = down;
			break;
		case Windows::System::VirtualKey::F13:
			keystate->F13 = down;
			break;
		case Windows::System::VirtualKey::F14:
			keystate->F14 = down;
			break;
		case Windows::System::VirtualKey::F15:
			keystate->F15 = down;
			break;
		case Windows::System::VirtualKey::F16:
			keystate->F16 = down;
			break;
		case Windows::System::VirtualKey::F17:
			keystate->F17 = down;
			break;
		case Windows::System::VirtualKey::F18:
			keystate->F18 = down;
			break;
		case Windows::System::VirtualKey::F19:
			keystate->F19 = down;
			break;
		case Windows::System::VirtualKey::F20:
			keystate->F20 = down;
			break;
		case Windows::System::VirtualKey::F21:
			keystate->F21 = down;
			break;
		case Windows::System::VirtualKey::F22:
			keystate->F22 = down;
			break;
		case Windows::System::VirtualKey::F23:
			keystate->F23 = down;
			break;
		case Windows::System::VirtualKey::F24:
			keystate->F24 = down;
			break;
		case Windows::System::VirtualKey::NavigationView:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::NavigationMenu:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::NavigationUp:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::NavigationDown:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::NavigationLeft:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::NavigationRight:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::NavigationAccept:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::NavigationCancel:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::NumberKeyLock:
			keystate->NumLock = down;
			break;
		case Windows::System::VirtualKey::Scroll:
			keystate->Scroll = down;
			break;
		case Windows::System::VirtualKey::LeftShift:
			keystate->LeftShift = down;
			break;
		case Windows::System::VirtualKey::RightShift:
			keystate->RightShift = down;
			break;
		case Windows::System::VirtualKey::LeftControl:
			keystate->LeftControl = down;
			break;
		case Windows::System::VirtualKey::RightControl:
			keystate->RightControl = down;
			break;
		case Windows::System::VirtualKey::LeftMenu:
			keystate->LeftAlt = down;
			break;
		case Windows::System::VirtualKey::RightMenu:
			keystate->RightAlt = down;
			break;
		case Windows::System::VirtualKey::GoBack:
			keystate->BrowserBack = down;
			break;
		case Windows::System::VirtualKey::GoForward:
			keystate->BrowserForward = down;
			break;
		case Windows::System::VirtualKey::Refresh:
			keystate->BrowserRefresh = down;
			break;
		case Windows::System::VirtualKey::Stop:
			keystate->BrowserStop = down;
			break;
		case Windows::System::VirtualKey::Search:
			keystate->BrowserSearch = down;
			break;
		case Windows::System::VirtualKey::Favorites:
			keystate->BrowserFavorites = down;
			break;
		case Windows::System::VirtualKey::GoHome:
			keystate->BrowserHome = down;
			break;
		case Windows::System::VirtualKey::GamepadA:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadB:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadX:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadY:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadRightShoulder:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadLeftShoulder:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadLeftTrigger:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadRightTrigger:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadDPadUp:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadDPadDown:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadDPadLeft:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadDPadRight:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadMenu:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadView:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickButton:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickButton:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickUp:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickDown:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickRight:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickLeft:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickUp:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickDown:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickRight:
			//keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickLeft:
			//keystate-> = down;
			break;
		default:
			break;
		}
	}

	void InputManager::OnKeyDown(_In_ CoreWindow^ Sender, _In_ KeyEventArgs^ Args)
	{
		UNREFERENCED_PARAMETER(Sender);
		Windows::System::VirtualKey Key;
		Key = Args->VirtualKey;

		HandleKeys(&m_keyboardState, Key, true);
	}
	void InputManager::OnKeyUp(_In_ CoreWindow^ Sender, _In_ KeyEventArgs^ Args)
	{
		UNREFERENCED_PARAMETER(Sender);
		Windows::System::VirtualKey Key;
		Key = Args->VirtualKey;

		HandleKeys(&m_keyboardState, Key, false);
	}

	void InputManager::OnGamepadAdded(_In_ Object ^ Sender, _In_ Gamepad ^ Gamepad)
	{
		UNREFERENCED_PARAMETER(Sender);
		UNREFERENCED_PARAMETER(Gamepad);

		ScanGamePad();
	}
	void InputManager::OnGamepadRemoved(_In_ Object ^ Sender, _In_  Gamepad ^ Gamepad) //-V524
	{
		UNREFERENCED_PARAMETER(Sender);
		UNREFERENCED_PARAMETER(Gamepad);

		ScanGamePad();
	}

	void InputManager::OnPointerPressed(_In_ CoreWindow^ Sender, _In_ PointerEventArgs^ Args)
	{
		UNREFERENCED_PARAMETER(Sender);
		Windows::UI::Input::PointerPoint^ pointer = Args->CurrentPoint;

		UpdatePointerDevices(pointer);
	}
	void InputManager::OnPointerMoved(_In_ CoreWindow^ Sender, _In_ PointerEventArgs^ Args)
	{
		UNREFERENCED_PARAMETER(Sender);
		Windows::UI::Input::PointerPoint^ pointer = Args->CurrentPoint;

		if (pointer->IsInContact)
		{
			UpdatePointerDevices(pointer);
		}
	}
	void InputManager::OnPointerReleased(_In_ CoreWindow^ Sender, _In_ PointerEventArgs^ Args)
	{
		UNREFERENCED_PARAMETER(Sender);
		Windows::UI::Input::PointerPoint^ pointer = Args->CurrentPoint;

		RemovePointerDevice(pointer);
	}
	void InputManager::OnPointerEntered(_In_ Windows::UI::Core::CoreWindow ^ Sender, _In_ Windows::UI::Core::PointerEventArgs ^ Args)
	{
		UNREFERENCED_PARAMETER(Sender);
		Windows::UI::Input::PointerPoint^ pointer = Args->CurrentPoint;

		if (pointer->IsInContact)
		{
			UpdatePointerDevices(pointer);
		}
	}
	void InputManager::OnPointerExited(_In_ CoreWindow ^ Sender, _In_ PointerEventArgs ^ Args) //-V524
	{
		UNREFERENCED_PARAMETER(Sender);
		Windows::UI::Input::PointerPoint^ pointer = Args->CurrentPoint;

		RemovePointerDevice(pointer);
	}
	void InputManager::OnPointerWheelChanged(_In_ CoreWindow^ Sender, _In_ PointerEventArgs^ Args) //-V524
	{
		UNREFERENCED_PARAMETER(Sender);
		Windows::UI::Input::PointerPoint^ pointer = Args->CurrentPoint;

		if (pointer->IsInContact)
		{
			UpdatePointerDevices(pointer);
		}
	}

	void InputManager::OnMouseMoved(_In_ MouseDevice^ MouseDevice, _In_ MouseEventArgs^ Args)
	{
		UNREFERENCED_PARAMETER(MouseDevice);

		m_mouseDelta.X = Args->MouseDelta.X;
		m_mouseDelta.Y = Args->MouseDelta.Y;
	}
	void InputManager::UpdatePointerDevices(_In_ PointerPoint^ device)
	{
		std::map<UINT, Windows::UI::Input::PointerPoint^>::iterator it;
		it = m_pointerdevices.find(device->PointerId);

		if (it != m_pointerdevices.end())
		{
			m_pointerdevices[device->PointerId] = device;
		}
		else
		{
			m_pointerdevices.emplace(device->PointerId, device);
		}
	}
	void InputManager::RemovePointerDevice(_In_ PointerPoint ^ device)
	{
		std::map<UINT, Windows::UI::Input::PointerPoint^>::iterator it;

		it = m_pointerdevices.find(device->PointerId);
		if (it != m_pointerdevices.end())
		{
			m_pointerdevices.erase(it);
		}
	}
} // namespace WOtech