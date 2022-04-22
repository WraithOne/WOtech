////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: IRenderer.h
///
///			Description:
///
///			Created:	07.05.2014
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_IRENDERER_H
#define WO_IRENDERER_H

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <VertexTypes.h>

namespace WOtech
{
	// Forward decl.
	ref class Mesh;
	ref class Camera;
	ref class DeviceDX11;

	public interface class IRenderer
	{
	public:
		virtual void Begin() = 0;
		virtual void Submit(_In_ Mesh^ mesh, _In_ Camera^ camera) = 0;
		virtual void Submit() = 0;
		virtual void End() = 0;
		virtual void Present() = 0;

		virtual DeviceDX11^ getDeviceDX11() = 0;

		virtual void Init() = 0;
	};
}
#endif
