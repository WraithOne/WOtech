////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: Inputmouse.cpp
///
///			Created:	01.05.2014
///			Edited:		06.11.2016
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Input.h"

using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::Devices::Input;

namespace WOtech
{
	Platform::Boolean InputManager::PenConnected()
	{
		if (m_pointer->PointerDevice->PointerDeviceType == PointerDeviceType::Pen)
			return true;

		return false;
	}

	PointerPosition InputManager::PenLocation()
	{
		PointerPosition position = { 0,0 };
		if (m_pointer)
		{
			position.PointerX = m_pointer->Position.X;
			position.PointerY = m_pointer->Position.Y;
		}

		return position;
	}// InputClass GetMouseLocation

	int32 InputManager::PenWheelPosition()
	{
		int32 wheelposition = 0;
		if (m_pointerProparties)
			wheelposition = m_pointerProparties->MouseWheelDelta;
			
		return wheelposition;
	}// InputClass GetMouseWheelPosition

	Platform::Boolean InputManager::PenPressed()
	{
		if( m_pointer)
			if (m_pointer->IsInContact)
				return true;

		return false;
	}

	Platform::Boolean InputManager::PenButtonDown(_In_ VirtualKey Button)
	{
		if (m_pointerProparties)
		{
			if (Button == VirtualKey::LeftButton)
				if (m_pointerProparties->IsLeftButtonPressed)
					return true;
			if (Button == VirtualKey::MiddleButton)
				if (m_pointerProparties->IsMiddleButtonPressed)
					return true;
			if (Button == VirtualKey::RightButton)
				if (m_pointerProparties->IsRightButtonPressed)
					return true;
			if (Button == VirtualKey::XButton1)
				if (m_pointerProparties->IsXButton1Pressed)
					return true;
			if (Button == VirtualKey::XButton2)
				if (m_pointerProparties->IsXButton2Pressed)
					return true;
		}
			
		return false;
	}// InputClass MouseButtonDown

	Platform::Boolean InputManager::PenButtonUp(_In_ VirtualKey Button)
	{
		if (m_pointerProparties)
		{
			if (Button == VirtualKey::LeftButton)
				if (!m_pointerProparties->IsLeftButtonPressed)
					return true;
			if (Button == VirtualKey::MiddleButton)
				if (!m_pointerProparties->IsMiddleButtonPressed)
					return true;
			if (Button == VirtualKey::RightButton)
				if (!m_pointerProparties->IsRightButtonPressed)
					return true;
			if (Button == VirtualKey::XButton1)
				if (!m_pointerProparties->IsXButton1Pressed)
					return true;
			if (Button == VirtualKey::XButton2)
				if (!m_pointerProparties->IsXButton2Pressed)
					return true;
		}
			
		return false;
	}// InputClass MouseButtonUp
}//namespace WOtech