////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: InputHardwarebackbutton.cpp
///
///			Description:
///
///			Created:	24.08.2016
///			Edited:		12.03.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Input.h"

namespace WOtech
{
	Platform::Boolean InputManager::HardwarebackbuttonConnceted()
	{
		if (Windows::Foundation::Metadata::ApiInformation::IsTypePresent("Windows.Phone.UI.Input.HardwareButtons"))
			return true;

		return false;
	}

	void InputManager::HardwarebackbuttonUse(_In_ Platform::Boolean Comfirm)
	{
		if (Comfirm)
		{
			// Hardware back button is only available on some device families such as Phone.
			if (Windows::Foundation::Metadata::ApiInformation::IsTypePresent("Windows.Phone.UI.Input.HardwareButtons"))
			{
				Windows::Phone::UI::Input::HardwareButtons::BackPressed += ref new Windows::Foundation::EventHandler<Windows::Phone::UI::Input::BackPressedEventArgs^>(this, &InputManager::OnHardwareBackButtonPressed);

				m_hwbbConfirmed = true;
			}
		}
		else
		{
			// Hardware back button is only available on some device families such as Phone.
			if (Windows::Foundation::Metadata::ApiInformation::IsTypePresent("Windows.Phone.UI.Input.HardwareButtons"))
			{
				m_hwbbConfirmed = false;
			}
		}
	}

	Platform::Boolean InputManager::HardwarebackbuttonInUse()
	{
		return m_hwbbConfirmed;
	}

	Platform::Boolean InputManager::HardwarebackbuttonPressed()
	{
		if (m_hwbbPressed)
		{
			m_hwbbPressed = false;
			return true;
		}

		return false;
	}
}// namespace WOtech