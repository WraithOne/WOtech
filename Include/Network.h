////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Network.h
///
///			Description:
///
///			Created:	13.05.2014
///			Edited:		05.01.2021
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_NETWORK_H
#define WO_NETWORK_H

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <Utilities.h>

/////////////
// LINKING //
/////////////

namespace WOtech
{
	public ref class Server sealed
	{
	internal:

	public:
		void Start();
		void Stop();

		void Send();
	private:
	};

	public ref class Client sealed
	{
	internal:

	public:

	private:
	};
}//Namespace WOtech

#endif
