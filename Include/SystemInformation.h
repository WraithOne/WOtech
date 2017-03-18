////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: SystemInformation.h
///
///			Description:
///
///			Created:	18.03.2017
///			Edited:		18.03.2017
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_SYSTEMINFORMATION_H
#define WO_SYSTEMINFORMATION_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"

/////////////
// Defines //
/////////////

namespace WOtech
{
	public ref class SystemInformation sealed
	{
	public:
		SystemInformation();
		void GatherInformations();

	private:
		~SystemInformation();

	private:

	};
}
#endif