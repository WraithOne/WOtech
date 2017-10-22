////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Numerics.h
///
///			Description: WOtech Numerics
///
///			Created:	22.10.2017
///			Edited:		22.10.2017
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_NUMERICS_H
#define WO_NUMERICS_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"

namespace WOtech
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Represents a rectangle defined by the coordinates of two points </summary>
	///
	/// <remarks>	WraithOne, 22.10.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public value class RECT
	{
	public:
		/// <summary>	The x-coordinate of the upper-left corner of the rectangle. < / summary>
		float X;
		/// <summary>	The y-coordinate of the upper-left corner of the rectangle. < / summary>
		float Y;
		/// <summary>	The x-coordinate of the lower-right corner of the rectangle. < / summary>
		float Width;
		/// <summary>	The y-coordinate of the lower-right corner of the rectangle. < / summary>
		float Height;
	};
}
#endif
