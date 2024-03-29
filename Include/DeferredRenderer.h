////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: DeferredRenderer.h
///
///			Description:
///
///			Created:	07.05.2014
///			Edited:		18.02.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_DEFERREDRENDERER_H
#define WO_DEFERREDRENDERER_H

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <IRenderer.h>
#include <3DComponents.h>
#include <DeviceDX11.h>
#include <RenderCommand.h>

namespace WOtech
{
	ref class DeferredRenderer sealed : IRenderer
	{
	public:
		DeferredRenderer(_In_ DeviceDX11^ device);

		virtual void Begin();
		virtual void Submit(_In_ Mesh^ mesh, _In_ Camera^ camera);
		virtual void Submit();
		virtual void End();
		virtual void Present();

		virtual DeviceDX11^  getDeviceDX11();

		virtual void Init();

	private:
		DeviceDX11^			m_device;

		Platform::Boolean	m_beginRender;

		// Render command queue
		CommandQueue		m_CommandQueue;

		// ClearColor
	};
}
#endif