////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: Inputhardwarebackbutton.cpp
///
///			Created:	24.08.2016
///			Edited:		25.01.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Input.h"

using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Devices::Input;
using namespace Windows::Gaming::Input;
using namespace Windows::Foundation::Collections;
using namespace Windows::Foundation::Metadata;
using namespace Platform;

namespace WOtech
{
	Boolean InputManager::HardwarebackbuttonConnceted()
	{
		if (ApiInformation::IsTypePresent("Windows.Phone.UI.Input.HardwareButtons"))
			return true;

		return false;
	}

	void InputManager::HardwarebackbuttonUse(_In_ Boolean Comfirm)
	{
		if (Comfirm)
		{
			// Hardware back button is only available on some device families such as Phone.
			if (ApiInformation::IsTypePresent("Windows.Phone.UI.Input.HardwareButtons"))
			{
				Windows::Phone::UI::Input::HardwareButtons::BackPressed += ref new EventHandler<Windows::Phone::UI::Input::BackPressedEventArgs^>(this, &InputManager::OnHardwareBackButtonPressed);

				m_hwbbConfirmed = true;
			}
		}
		else
		{
			// Hardware back button is only available on some device families such as Phone.
			if (ApiInformation::IsTypePresent("Windows.Phone.UI.Input.HardwareButtons"))
			{
				m_hwbbConfirmed = false;
			}
		}
			
	}

	Boolean InputManager::HardwarebackbuttonInUse()
	{
		return m_hwbbConfirmed;
	}

	Boolean InputManager::HardwarebackbuttonPressed()
	{
		if (m_hwbbPressed)
		{
			m_hwbbPressed = false;
			return true;
		}

		return false;
	}
}// namespace WOtech