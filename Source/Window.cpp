////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Window.cpp
///
///			Description:
///
///			Created:	14.01.2018
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Include\Window.h"


namespace WOtech
{
	Window::Window()
	{
		m_corewindow = Windows::UI::Core::CoreWindow::GetForCurrentThread();
	}
	Windows::UI::Core::CoreWindow^ Window::getCoreWindow()
	{
		return m_corewindow.Get();
	}
}