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
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_SYSTEMINFORMATION_H
#define WO_SYSTEMINFORMATION_H

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <DXWrapper.h>

/////////////
// Defines //
/////////////

namespace WOtech
{
	public value class GraphicReport
	{
	public:
		Platform::IBox<WOtech::ADAPTER_DXGI>^ Adapters;
	};
	public value struct AudioReport
	{
		int a;
	};
	public value struct InputReport
	{
		int a;
	};
	public value struct SystemReport
	{
		int a;
	};

	public ref class SystemInformation sealed
	{
	public:
		SystemInformation();
		void GatherInformations();
		Platform::Array<WOtech::ADAPTER_DXGI>^ getGraphicInformations();

	private:
		~SystemInformation();

	private:
	};
}
#endif