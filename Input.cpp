////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: Input.cpp
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

	void HandleKeys(_Inout_ WOtech::Keyboard_State* Keystate, _In_ Windows::System::VirtualKey keys, _In_ Boolean down)
	{
		switch (keys)
		{
		case Windows::System::VirtualKey::None:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::LeftButton:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::RightButton:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::Cancel:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::MiddleButton:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::XButton1:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::XButton2:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::Back:
			Keystate->Back = down;
			break;
		case Windows::System::VirtualKey::Tab:
			Keystate->Tab = down;
			break;
		case Windows::System::VirtualKey::Clear:
			//m_keyboardState. = down;
			break;
		case Windows::System::VirtualKey::Enter:
			Keystate->Enter = down;
			break;
		case Windows::System::VirtualKey::Shift:
			//m_keyboardState. = down;
			break;
		case Windows::System::VirtualKey::Control:
			//m_keyboardState. = down;
			break;
		case Windows::System::VirtualKey::Menu:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::Pause:
			Keystate->Pause = down;
			break;
		case Windows::System::VirtualKey::CapitalLock:
			Keystate->CapsLock = down;
			break;
		case Windows::System::VirtualKey::Kana:
			Keystate->Kana = down;
			break;
		//case Windows::System::VirtualKey::Hangul:
			//Keystate-> = down;
			//	break;
		case Windows::System::VirtualKey::Junja:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::Final:
			break;
		//case Windows::System::VirtualKey::Hanja:
			//Keystate-> = down;
			//break;
		case Windows::System::VirtualKey::Kanji:
			Keystate->Kanji = down;
			break;
		case Windows::System::VirtualKey::Escape:
			Keystate->Escape = down;
			break;
		case Windows::System::VirtualKey::Convert:
			Keystate->ImeConvert = down;
			break;
		case Windows::System::VirtualKey::NonConvert:
			Keystate->ImeNoConvert = down;
			break;
		case Windows::System::VirtualKey::Accept:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::ModeChange:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::Space:
			Keystate->Space = down;
			break;
		case Windows::System::VirtualKey::PageUp:
			Keystate->PageUp = down;
			break;
		case Windows::System::VirtualKey::PageDown:
			Keystate->PageDown = down;
			break;
		case Windows::System::VirtualKey::End:
			Keystate->End = down;
			break;
		case Windows::System::VirtualKey::Home:
			Keystate->Home = down;
			break;
		case Windows::System::VirtualKey::Left:
			Keystate->Left = down;
			break;
		case Windows::System::VirtualKey::Up:
			Keystate->Up = down;
			break;
		case Windows::System::VirtualKey::Right:
			Keystate->Right = down;
			break;
		case Windows::System::VirtualKey::Down:
			Keystate->Down = down;
			break;
		case Windows::System::VirtualKey::Select:
			Keystate->Select = down;
			break;
		case Windows::System::VirtualKey::Print:
			Keystate->Print = down;
			break;
		case Windows::System::VirtualKey::Execute:
			Keystate->Execute = down;
			break;
		case Windows::System::VirtualKey::Snapshot:
			Keystate->PrintScreen = down;
			break;
		case Windows::System::VirtualKey::Insert:
			Keystate->Insert = down;
			break;
		case Windows::System::VirtualKey::Delete:
			Keystate->Delete = down;
			break;
		case Windows::System::VirtualKey::Help:
			Keystate->Help = down;
			break;
		case Windows::System::VirtualKey::Number0:
			Keystate->D0 = down;
			break;
		case Windows::System::VirtualKey::Number1:
			Keystate->D1 = down;
			break;
		case Windows::System::VirtualKey::Number2:
			Keystate->D2 = down;
			break;
		case Windows::System::VirtualKey::Number3:
			Keystate->D3 = down;
			break;
		case Windows::System::VirtualKey::Number4:
			Keystate->D4 = down;
			break;
		case Windows::System::VirtualKey::Number5:
			Keystate->D5 = down;
			break;
		case Windows::System::VirtualKey::Number6:
			Keystate->D6 = down;
			break;
		case Windows::System::VirtualKey::Number7:
			Keystate->D7 = down;
			break;
		case Windows::System::VirtualKey::Number8:
			Keystate->D8 = down;
			break;
		case Windows::System::VirtualKey::Number9:
			Keystate->D9 = down;
			break;
		case Windows::System::VirtualKey::A:
			Keystate->A = down;
			break;
		case Windows::System::VirtualKey::B:
			Keystate->B = down;
			break;
		case Windows::System::VirtualKey::C:
			Keystate->C = down;
			break;
		case Windows::System::VirtualKey::D:
			Keystate->D = down;
			break;
		case Windows::System::VirtualKey::E:
			Keystate->E = down;
			break;
		case Windows::System::VirtualKey::F:
			Keystate->F = down;
			break;
		case Windows::System::VirtualKey::G:
			Keystate->G = down;
			break;
		case Windows::System::VirtualKey::H:
			Keystate->H = down;
			break;
		case Windows::System::VirtualKey::I:
			Keystate->I = down;
			break;
		case Windows::System::VirtualKey::J:
			Keystate->J = down;
			break;
		case Windows::System::VirtualKey::K:
			Keystate->K = down;
			break;
		case Windows::System::VirtualKey::L:
			Keystate->L = down;
			break;
		case Windows::System::VirtualKey::M:
			Keystate->M = down;
			break;
		case Windows::System::VirtualKey::N:
			Keystate->N = down;
			break;
		case Windows::System::VirtualKey::O:
			Keystate->O = down;
			break;
		case Windows::System::VirtualKey::P:
			Keystate->P = down;
			break;
		case Windows::System::VirtualKey::Q:
			Keystate->Q = down;
			break;
		case Windows::System::VirtualKey::R:
			Keystate->R = down;
			break;
		case Windows::System::VirtualKey::S:
			Keystate->S = down;
			break;
		case Windows::System::VirtualKey::T:
			Keystate->T = down;
			break;
		case Windows::System::VirtualKey::U:
			Keystate->U = down;
			break;
		case Windows::System::VirtualKey::V:
			Keystate->V = down;
			break;
		case Windows::System::VirtualKey::W:
			Keystate->W = down;
			break;
		case Windows::System::VirtualKey::X:
			Keystate->X = down;
			break;
		case Windows::System::VirtualKey::Y:
			Keystate->Y = down;
			break;
		case Windows::System::VirtualKey::Z:
			Keystate->Z = down;
			break;
		case Windows::System::VirtualKey::LeftWindows:
			Keystate->LeftWindows = down;
			break;
		case Windows::System::VirtualKey::RightWindows:
			Keystate->RightWindows = down;
			break;
		case Windows::System::VirtualKey::Application:
			Keystate->Apps = down;
			break;
		case Windows::System::VirtualKey::Sleep:
			Keystate->Sleep = down;
			break;
		case Windows::System::VirtualKey::NumberPad0:
			Keystate->NumPad0 = down;
			break;
		case Windows::System::VirtualKey::NumberPad1:
			Keystate->NumPad1 = down;
			break;
		case Windows::System::VirtualKey::NumberPad2:
			Keystate->NumPad2 = down;
			break;
		case Windows::System::VirtualKey::NumberPad3:
			Keystate->NumPad3 = down;
			break;
		case Windows::System::VirtualKey::NumberPad4:
			Keystate->NumPad4 = down;
			break;
		case Windows::System::VirtualKey::NumberPad5:
			Keystate->NumPad5 = down;
			break;
		case Windows::System::VirtualKey::NumberPad6:
			Keystate->NumPad6 = down;
			break;
		case Windows::System::VirtualKey::NumberPad7:
			Keystate->NumPad7 = down;
			break;
		case Windows::System::VirtualKey::NumberPad8:
			Keystate->NumPad8 = down;
			break;
		case Windows::System::VirtualKey::NumberPad9:
			Keystate->NumPad9 = down;
			break;
		case Windows::System::VirtualKey::Multiply:
			Keystate->Multiply = down;
			break;
		case Windows::System::VirtualKey::Add:
			Keystate->Add = down;
			break;
		case Windows::System::VirtualKey::Separator:
			Keystate->Separator = down;
			break;
		case Windows::System::VirtualKey::Subtract:
			Keystate->Subtract = down;
			break;
		case Windows::System::VirtualKey::Decimal:
			Keystate->Decimal = down;
			break;
		case Windows::System::VirtualKey::Divide:
			Keystate->Divide = down;
			break;
		case Windows::System::VirtualKey::F1:
			Keystate->F1 = down;
			break;
		case Windows::System::VirtualKey::F2:
			Keystate->F2 = down;
			break;
		case Windows::System::VirtualKey::F3:
			Keystate->F3 = down;
			break;
		case Windows::System::VirtualKey::F4:
			Keystate->F4 = down;
			break;
		case Windows::System::VirtualKey::F5:
			Keystate->F5 = down;
			break;
		case Windows::System::VirtualKey::F6:
			Keystate->F6 = down;
			break;
		case Windows::System::VirtualKey::F7:
			Keystate-> F7= down;
			break;
		case Windows::System::VirtualKey::F8:
			Keystate->F8 = down;
			break;
		case Windows::System::VirtualKey::F9:
			Keystate-> F9= down;
			break;
		case Windows::System::VirtualKey::F10:
			Keystate->F10 = down;
			break;
		case Windows::System::VirtualKey::F11:
			Keystate->F11 = down;
			break;
		case Windows::System::VirtualKey::F12:
			Keystate->F12 = down;
			break;
		case Windows::System::VirtualKey::F13:
			Keystate->F13 = down;
			break;
		case Windows::System::VirtualKey::F14:
			Keystate->F14 = down;
			break;
		case Windows::System::VirtualKey::F15:
			Keystate->F15 = down;
			break;
		case Windows::System::VirtualKey::F16:
			Keystate->F16 = down;
			break;
		case Windows::System::VirtualKey::F17:
			Keystate->F17 = down;
			break;
		case Windows::System::VirtualKey::F18:
			Keystate->F18 = down;
			break;
		case Windows::System::VirtualKey::F19:
			Keystate->F19 = down;
			break;
		case Windows::System::VirtualKey::F20:
			Keystate->F20 = down;
			break;
		case Windows::System::VirtualKey::F21:
			Keystate->F21 = down;
			break;
		case Windows::System::VirtualKey::F22:
			Keystate->F22 = down;
			break;
		case Windows::System::VirtualKey::F23:
			Keystate->F23 = down;
			break;
		case Windows::System::VirtualKey::F24:
			Keystate->F24 = down;
			break;
		case Windows::System::VirtualKey::NavigationView:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::NavigationMenu:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::NavigationUp:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::NavigationDown:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::NavigationLeft:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::NavigationRight:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::NavigationAccept:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::NavigationCancel:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::NumberKeyLock:
			Keystate->NumLock = down;
			break;
		case Windows::System::VirtualKey::Scroll:
			Keystate-> Scroll= down;
			break;
		case Windows::System::VirtualKey::LeftShift:
			Keystate->LeftShift = down;
			break;
		case Windows::System::VirtualKey::RightShift:
			Keystate->RightShift = down;
			break;
		case Windows::System::VirtualKey::LeftControl:
			Keystate->LeftControl = down;
			break;
		case Windows::System::VirtualKey::RightControl:
			Keystate->RightControl = down;
			break;
		case Windows::System::VirtualKey::LeftMenu:
			Keystate->LeftAlt = down;
			break;
		case Windows::System::VirtualKey::RightMenu:
			Keystate->RightAlt = down;
			break;
		case Windows::System::VirtualKey::GoBack:
			Keystate->BrowserBack = down;
			break;
		case Windows::System::VirtualKey::GoForward:
			Keystate->BrowserForward = down;
			break;
		case Windows::System::VirtualKey::Refresh:
			Keystate->BrowserRefresh = down;
			break;
		case Windows::System::VirtualKey::Stop:
			Keystate->BrowserStop = down;
			break;
		case Windows::System::VirtualKey::Search:
			Keystate->BrowserSearch = down;
			break;
		case Windows::System::VirtualKey::Favorites:
			Keystate->BrowserFavorites = down;
			break;
		case Windows::System::VirtualKey::GoHome:
			Keystate->BrowserHome = down;
			break;
		case Windows::System::VirtualKey::GamepadA:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadB:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadX:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadY:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadRightShoulder:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadLeftShoulder:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadLeftTrigger:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadRightTrigger:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadDPadUp:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadDPadDown:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadDPadLeft:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadDPadRight:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadMenu:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadView:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickButton:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickButton:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickUp:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickDown:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickRight:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadLeftThumbstickLeft:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickUp:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickDown:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickRight:
			//Keystate-> = down;
			break;
		case Windows::System::VirtualKey::GamepadRightThumbstickLeft:
			//Keystate-> = down;
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