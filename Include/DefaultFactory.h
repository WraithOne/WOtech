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
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_DEFAULTFACTORY_H
#define WO_DEFAULTFACTORY_H

//////////////
// INCLUDES //
//////////////

namespace WOtech
{
	/////////////////////////////////////////////////////////////////////////
	// Forward declarations
	ref class DeviceDX11;
	interface class IMaterial;
	ref class BasicMaterial;
	ref class Mesh;

	public ref class DefaultFactory sealed
	{
	public:
		static BasicMaterial^ CreateBasicMaterial(_In_ WOtech::DeviceDX11^ device);
		static Mesh^ CreateCube(_In_ float size, _In_ WOtech::IMaterial^ material, _In_ WOtech::DeviceDX11^ device);
		static Mesh^ CreateTriangle(_In_ float size, _In_ WOtech::IMaterial^ material, _In_ WOtech::DeviceDX11^ device);
	};
}
#endif