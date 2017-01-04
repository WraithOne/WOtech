////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: Input.cpp
///
///			Created:	02.05.2014
///			Edited:		22.11.2016
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

	void InputManager::OnKeyDown(_In_ CoreWindow^ Sender, _In_ KeyEventArgs^ Args)
	{
		UNREFERENCED_PARAMETER(Sender);
		m_keyboardKeys = Args->VirtualKey;
	}
	void InputManager::OnKeyUp(_In_ CoreWindow^ Sender, _In_ KeyEventArgs^ Args)
	{
		UNREFERENCED_PARAMETER(Sender);
		m_keyboardKeys = Args->VirtualKey;
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