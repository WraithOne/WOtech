////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Framecounter.h
///
///			Description:
///
///			Created:	16.04.2016
///			Edited:		06.11.2016
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_FRAMECOUNTER_H
#define WO_FRAMECOUNTER_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"

namespace WOtech
{
	class Interval
	{
	private:
		ULONGLONG initial_;

	public:
		inline Interval() : initial_(GetTickCount64())
		{
		}

		virtual ~Interval()
		{
		}

		inline ULONGLONG value() const
		{
			return GetTickCount64() - initial_;
		}
	};

	
	public ref class Framecounter sealed
	{
	public:
		Framecounter();
		void				update();

		UINT				get();
		Platform::String^	getString();

	private:
		UINT				m_fps;
		UINT				m_fpscount;
		Interval			m_fpsinterval;
		Platform::String^	m_string;
	};
}

#endif