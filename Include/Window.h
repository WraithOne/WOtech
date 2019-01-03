////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Window.h
///
///			Description:
///
///			Created:	14.01.2018
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_WINDOW_H
#define WO_WINDOW_H

//////////////
// INCLUDES //
//////////////
#include <pch.h>

namespace WOtech
{
	public ref class Window sealed
	{
	public:
		Window();

	internal:
		Windows::UI::Core::CoreWindow^ getCoreWindow();

	private:
		Platform::Agile<Windows::UI::Core::CoreWindow> m_corewindow;
	};
} // namespace WOtech
#endif