////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: DefaultFactory.h
///
///			Description:
///
///			Created:	27.02.2016
///			Edited:		11.11.2016
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_DEFAULTFACTORY_H
#define WO_DEFAULTFACTORY_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include <windows.foundation.numerics.h>

#include "DeviceDX11.h"
#include "3DComponents.h"

namespace WOtech
{
	Mesh^ CreateCube(_In_ float32 size, _In_ MaterialInstance^ material, _In_ DeviceDX11^ device);
	Mesh^ CreateTriangle(_In_ float32 size, _In_ MaterialInstance^ material, _In_ DeviceDX11^ device);
}
#endif