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
#ifndef WO_RENDERER_H
#define WO_RENDERER_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "DXWrapper.h"
#include "3DComponents.h"
#include "DeviceDX11.h"

namespace WOtech
{
	struct RenderCommand
	{
		Mesh^ mesh;
		RendererUniforms uniforms;
	};

	typedef std::vector<RenderCommand> CommandQueue;

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
