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
		for (auto pads : m_gamePad)
		{
			pads = nullptr;
		}
		
		//todo: gamepad reset?!?
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
#pragma warning (disable : 4014)
			{
				Windows::UI::ViewManagement::StatusBar::GetForCurrentView()->HideAsync();
			}
#pragma warning (default : 4014)
		}
		else
		{
			Windows::UI::ViewManagement::ApplicationView::GetForCurrentView()->ExitFullScreenMode();//>SuppressSystemOverlays = false;
			if (Windows::Foundation::Metadata::ApiInformation::IsTypePresent("Windows.UI.ViewManagement.StatusBar"))
#pragma warning (disable : 4014)
			{
				Windows::UI::ViewManagement::StatusBar::GetForCurrentView()->ShowAsync();
			}
#pragma warning (default : 4014)
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

	inline void HandleKeys(_Inout_ WOtech::Keyboard_State* Keystate, _In_ Windows::System::VirtualKey Key, _In_ Boolean Down)
	{
		switch (Key)
		{
		case Windows::System::VirtualKey::None:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::LeftButton:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::RightButton:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::Cancel:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::MiddleButton:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::XButton1:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::XButton2:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::Back:
			Keystate->Back = Down;
			break;
		case Windows::System::VirtualKey::Tab:
			Keystate->Tab = Down;
			break;
		case Windows::System::VirtualKey::Clear:
			//m_keyboardState. = Down;
			break;
		case Windows::System::VirtualKey::Enter:
			Keystate->Enter = Down;
			break;
		case Windows::System::VirtualKey::Shift:
			//m_keyboardState. = Down;
			break;
		case Windows::System::VirtualKey::Control:
			//m_keyboardState. = Down;
			break;
		case Windows::System::VirtualKey::Menu:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::Pause:
			Keystate->Pause = Down;
			break;
		case Windows::System::VirtualKey::CapitalLock:
			Keystate->CapsLock = Down;
			break;
		case Windows::System::VirtualKey::Kana:
			Keystate->Kana = Down;
			break;
		//case Windows::System::VirtualKey::Hangul:
			//Keystate-> = Down;
			//	break;
		case Windows::System::VirtualKey::Junja:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::Final:
			break;
		//case Windows::System::VirtualKey::Hanja:
			//Keystate-> = Down;
			//break;
		case Windows::System::VirtualKey::Kanji:
			Keystate->Kanji = Down;
			break;
		case Windows::System::VirtualKey::Escape:
			Keystate->Escape = Down;
			break;
		case Windows::System::VirtualKey::Convert:
			Keystate->ImeConvert = Down;
			break;
		case Windows::System::VirtualKey::NonConvert:
			Keystate->ImeNoConvert = Down;
			break;
		case Windows::System::VirtualKey::Accept:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::ModeChange:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::Space:
			Keystate->Space = Down;
			break;
		case Windows::System::VirtualKey::PageUp:
			Keystate->PageUp = Down;
			break;
		case Windows::System::VirtualKey::PageDown:
			Keystate->PageDown = Down;
			break;
		case Windows::System::VirtualKey::End:
			Keystate->End = Down;
			break;
		case Windows::System::VirtualKey::Home:
			Keystate->Home = Down;
			break;
		case Windows::System::VirtualKey::Left:
			Keystate->Left = Down;
			break;
		case Windows::System::VirtualKey::Up:
			Keystate->Up = Down;
			break;
		case Windows::System::VirtualKey::Right:
			Keystate->Right = Down;
			break;
		case Windows::System::VirtualKey::Down:
			Keystate->Down = Down;
			break;
		case Windows::System::VirtualKey::Select:
			Keystate->Select = Down;
			break;
		case Windows::System::VirtualKey::Print:
			Keystate->Print = Down;
			break;
		case Windows::System::VirtualKey::Execute:
			Keystate->Execute = Down;
			break;
		case Windows::System::VirtualKey::Snapshot:
			Keystate->PrintScreen = Down;
			break;
		case Windows::System::VirtualKey::Insert:
			Keystate->Insert = Down;
			break;
		case Windows::System::VirtualKey::Delete:
			Keystate->Delete = Down;
			break;
		case Windows::System::VirtualKey::Help:
			Keystate->Help = Down;
			break;
		case Windows::System::VirtualKey::Number0:
			Keystate->D0 = Down;
			break;
		case Windows::System::VirtualKey::Number1:
			Keystate->D1 = Down;
			break;
		case Windows::System::VirtualKey::Number2:
			Keystate->D2 = Down;
			break;
		case Windows::System::VirtualKey::Number3:
			Keystate->D3 = Down;
			break;
		case Windows::System::VirtualKey::Number4:
			Keystate->D4 = Down;
			break;
		case Windows::System::VirtualKey::Number5:
			Keystate->D5 = Down;
			break;
		case Windows::System::VirtualKey::Number6:
			Keystate->D6 = Down;
			break;
		case Windows::System::VirtualKey::Number7:
			Keystate->D7 = Down;
			break;
		case Windows::System::VirtualKey::Number8:
			Keystate->D8 = Down;
			break;
		case Windows::System::VirtualKey::Number9:
			Keystate->D9 = Down;
			break;
		case Windows::System::VirtualKey::A:
			Keystate->A = Down;
			break;
		case Windows::System::VirtualKey::B:
			Keystate->B = Down;
			break;
		case Windows::System::VirtualKey::C:
			Keystate->C = Down;
			break;
		case Windows::System::VirtualKey::D:
			Keystate->D = Down;
			break;
		case Windows::System::VirtualKey::E:
			Keystate->E = Down;
			break;
		case Windows::System::VirtualKey::F:
			Keystate->F = Down;
			break;
		case Windows::System::VirtualKey::G:
			Keystate->G = Down;
			break;
		case Windows::System::VirtualKey::H:
			Keystate->H = Down;
			break;
		case Windows::System::VirtualKey::I:
			Keystate->I = Down;
			break;
		case Windows::System::VirtualKey::J:
			Keystate->J = Down;
			break;
		case Windows::System::VirtualKey::K:
			Keystate->K = Down;
			break;
		case Windows::System::VirtualKey::L:
			Keystate->L = Down;
			break;
		case Windows::System::VirtualKey::M:
			Keystate->M = Down;
			break;
		case Windows::System::VirtualKey::N:
			Keystate->N = Down;
			break;
		case Windows::System::VirtualKey::O:
			Keystate->O = Down;
			break;
		case Windows::System::VirtualKey::P:
			Keystate->P = Down;
			break;
		case Windows::System::VirtualKey::Q:
			Keystate->Q = Down;
			break;
		case Windows::System::VirtualKey::R:
			Keystate->R = Down;
			break;
		case Windows::System::VirtualKey::S:
			Keystate->S = Down;
			break;
		case Windows::System::VirtualKey::T:
			Keystate->T = Down;
			break;
		case Windows::System::VirtualKey::U:
			Keystate->U = Down;
			break;
		case Windows::System::VirtualKey::V:
			Keystate->V = Down;
			break;
		case Windows::System::VirtualKey::W:
			Keystate->W = Down;
			break;
		case Windows::System::VirtualKey::X:
			Keystate->X = Down;
			break;
		case Windows::System::VirtualKey::Y:
			Keystate->Y = Down;
			break;
		case Windows::System::VirtualKey::Z:
			Keystate->Z = Down;
			break;
		case Windows::System::VirtualKey::LeftWindows:
			Keystate->LeftWindows = Down;
			break;
		case Windows::System::VirtualKey::RightWindows:
			Keystate->RightWindows = Down;
			break;
		case Windows::System::VirtualKey::Application:
			Keystate->Apps = Down;
			break;
		case Windows::System::VirtualKey::Sleep:
			Keystate->Sleep = Down;
			break;
		case Windows::System::VirtualKey::NumberPad0:
			Keystate->NumPad0 = Down;
			break;
		case Windows::System::VirtualKey::NumberPad1:
			Keystate->NumPad1 = Down;
			break;
		case Windows::System::VirtualKey::NumberPad2:
			Keystate->NumPad2 = Down;
			break;
		case Windows::System::VirtualKey::NumberPad3:
			Keystate->NumPad3 = Down;
			break;
		case Windows::System::VirtualKey::NumberPad4:
			Keystate->NumPad4 = Down;
			break;
		case Windows::System::VirtualKey::NumberPad5:
			Keystate->NumPad5 = Down;
			break;
		case Windows::System::VirtualKey::NumberPad6:
			Keystate->NumPad6 = Down;
			break;
		case Windows::System::VirtualKey::NumberPad7:
			Keystate->NumPad7 = Down;
			break;
		case Windows::System::VirtualKey::NumberPad8:
			Keystate->NumPad8 = Down;
			break;
		case Windows::System::VirtualKey::NumberPad9:
			Keystate->NumPad9 = Down;
			break;
		case Windows::System::VirtualKey::Multiply:
			Keystate->Multiply = Down;
			break;
		case Windows::System::VirtualKey::Add:
			Keystate->Add = Down;
			break;
		case Windows::System::VirtualKey::Separator:
			Keystate->Separator = Down;
			break;
		case Windows::System::VirtualKey::Subtract:
			Keystate->Subtract = Down;
			break;
		case Windows::System::VirtualKey::Decimal:
			Keystate->Decimal = Down;
			break;
		case Windows::System::VirtualKey::Divide:
			Keystate->Divide = Down;
			break;
		case Windows::System::VirtualKey::F1:
			Keystate->F1 = Down;
			break;
		case Windows::System::VirtualKey::F2:
			Keystate->F2 = Down;
			break;
		case Windows::System::VirtualKey::F3:
			Keystate->F3 = Down;
			break;
		case Windows::System::VirtualKey::F4:
			Keystate->F4 = Down;
			break;
		case Windows::System::VirtualKey::F5:
			Keystate->F5 = Down;
			break;
		case Windows::System::VirtualKey::F6:
			Keystate->F6 = Down;
			break;
		case Windows::System::VirtualKey::F7:
			Keystate-> F7= Down;
			break;
		case Windows::System::VirtualKey::F8:
			Keystate->F8 = Down;
			break;
		case Windows::System::VirtualKey::F9:
			Keystate-> F9= Down;
			break;
		case Windows::System::VirtualKey::F10:
			Keystate->F10 = Down;
			break;
		case Windows::System::VirtualKey::F11:
			Keystate->F11 = Down;
			break;
		case Windows::System::VirtualKey::F12:
			Keystate->F12 = Down;
			break;
		case Windows::System::VirtualKey::F13:
			Keystate->F13 = Down;
			break;
		case Windows::System::VirtualKey::F14:
			Keystate->F14 = Down;
			break;
		case Windows::System::VirtualKey::F15:
			Keystate->F15 = Down;
			break;
		case Windows::System::VirtualKey::F16:
			Keystate->F16 = Down;
			break;
		case Windows::System::VirtualKey::F17:
			Keystate->F17 = Down;
			break;
		case Windows::System::VirtualKey::F18:
			Keystate->F18 = Down;
			break;
		case Windows::System::VirtualKey::F19:
			Keystate->F19 = Down;
			break;
		case Windows::System::VirtualKey::F20:
			Keystate->F20 = Down;
			break;
		case Windows::System::VirtualKey::F21:
			Keystate->F21 = Down;
			break;
		case Windows::System::VirtualKey::F22:
			Keystate->F22 = Down;
			break;
		case Windows::System::VirtualKey::F23:
			Keystate->F23 = Down;
			break;
		case Windows::System::VirtualKey::F24:
			Keystate->F24 = Down;
			break;
		case Windows::System::VirtualKey::NavigationView:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::NavigationMenu:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::NavigationUp:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::NavigationDown:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::NavigationLeft:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::NavigationRight:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::NavigationAccept:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::NavigationCancel:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::NumberKeyLock:
			Keystate->NumLock = Down;
			break;
		case Windows::System::VirtualKey::Scroll:
			Keystate-> Scroll= Down;
			break;
		case Windows::System::VirtualKey::LeftShift:
			Keystate->LeftShift = Down;
			break;
		case Windows::System::VirtualKey::RightShift:
			Keystate->RightShift = Down;
			break;
		case Windows::System::VirtualKey::LeftControl:
			Keystate->LeftControl = Down;
			break;
		case Windows::System::VirtualKey::RightControl:
			Keystate->RightControl = Down;
			break;
		case Windows::System::VirtualKey::LeftMenu:
			Keystate->LeftAlt = Down;
			break;
		case Windows::System::VirtualKey::RightMenu:
			Keystate->RightAlt = Down;
			break;
		case Windows::System::VirtualKey::GoBack:
			Keystate->BrowserBack = Down;
			break;
		case Windows::System::VirtualKey::GoForward:
			Keystate->BrowserForward = Down;
			break;
		case Windows::System::VirtualKey::Refresh:
			Keystate->BrowserRefresh = Down;
			break;
		case Windows::System::VirtualKey::Stop:
			Keystate->BrowserStop = Down;
			break;
		case Windows::System::VirtualKey::Search:
			Keystate->BrowserSearch = Down;
			break;
		case Windows::System::VirtualKey::Favorites:
			Keystate->BrowserFavorites = Down;
			break;
		case Windows::System::VirtualKey::GoHome:
			Keystate->BrowserHome = Down;
			break;
		case Windows::System::VirtualKey::GamepadA:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadB:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadX:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadY:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadRightShoulder:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadLeftShoulder:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadLeftTrigger:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadRightTrigger:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadDPadUp:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadDPadDown:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadDPadLeft:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadDPadRight:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadMenu:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadView:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickButton:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickButton:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickUp:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickDown:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickRight:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickLeft:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickUp:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickDown:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickRight:
			//Keystate-> = Down;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickLeft:
			//Keystate-> = Down;
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
	void InputManager::OnGamepadRemoved(_In_ Object ^ Sender, _In_  Gamepad ^ Gamepad)
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
	void InputManager::OnPointerExited(_In_ CoreWindow ^ Sender, _In_ PointerEventArgs ^ Args)
	{
		UNREFERENCED_PARAMETER(Sender);
		Windows::UI::Input::PointerPoint^ pointer = Args->CurrentPoint;

		RemovePointerDevice(pointer);
	}
	void InputManager::OnPointerWheelChanged(_In_ CoreWindow^ Sender, _In_ PointerEventArgs^ Args)
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