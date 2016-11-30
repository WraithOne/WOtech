////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: Renderer.h
///
///			Created:	07.05.2014
///			Edited:		26.11.2016
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

	
	public interface class Renderer
	{
	public:
		void Begin();
		void Submit(Mesh^ mesh, Camera^ camera, Windows::Foundation::Numerics::float4x4 transform);
		void Submit();
		void End();
		void Present();

		DeviceDX11^ getDeviceDX11();

		void Init();
	};
}
#endif
