////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Renderer.h
///
///			Description:
///
///			Created:	07.05.2014
///			Edited:		10.08.2017
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_IRENDERER_H
#define WO_IRENDERER_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"

namespace WOtech
{
	// Forward decl.
	ref class Mesh;
	ref class Camera;
	ref class DeviceDX11;

	public interface class IRenderer
	{
	public:
		void Begin();
		void Submit(_In_ Mesh^ mesh, _In_ Camera^ camera, _In_ Windows::Foundation::Numerics::float4x4 transform);
		void Submit();
		void End();
		void Present();

		DeviceDX11^ getDeviceDX11();

		void Init(_In_ Windows::UI::Color clearColor);
	};
}
#endif
