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
///			Edited:		15.04.2017
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_DEFAULTFACTORY_H
#define WO_DEFAULTFACTORY_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"

namespace WOtech
{
	/////////////////////////////////////////////////////////////////////////
	// Forward declarations
	ref class DeviceDX11;
	ref class Material;
	ref class MaterialInstance;
	ref class Mesh;

	public ref class DefaultFactory sealed
	{
	public:
		static Material^ CreateBasicMaterial(_In_ WOtech::DeviceDX11^ device);
		static Mesh^ CreateCube(_In_ float size, _In_ WOtech::MaterialInstance^ material, _In_ WOtech::DeviceDX11^ device);
		static Mesh^ CreateTriangle(_In_ float size, _In_ WOtech::MaterialInstance^ material, _In_ WOtech::DeviceDX11^ device);
	};
}
#endif