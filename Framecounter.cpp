////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: Framecounter.cpp
///
///			Created:	06.09.2014
///			Edited:		06.11.2016
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Framecounter.h"

using namespace Platform;

namespace WOtech
{
	Framecounter::Framecounter()
	{
		m_fps = 0;
		m_fpscount = 0;
	}

	void Framecounter::update()
	{
		m_fpscount++;

		if (m_fpsinterval.value() > 1000)
		{
			m_fps = m_fpscount;

			m_fpscount = 0;

			m_fpsinterval = Interval();
		}
		std::wstring wstring = L"FPS: " + std::to_wstring(m_fps);

		m_string = ref new String(wstring.c_str());
	}

	UINT Framecounter::get()
	{
		return m_fps;
	}

	String^ Framecounter::getString()
	{
		return m_string;
	}
}