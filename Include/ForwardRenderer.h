////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: ForwardRenderer.h
///
///			Description:
///
///			Created:	07.05.2014
///			Edited:		18.02.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_FORWARDRENDERER_H
#define WO_FORWARDRENDERER_H

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
	public ref class ForwardRenderer sealed : public IRenderer
	{
	public:
		ForwardRenderer(_In_ DeviceDX11^ device);

		virtual void Begin();
		virtual void Submit(_In_ Mesh^ mesh, _In_ Camera^ camera);
		virtual void Submit();
		virtual void End();
		virtual void Present();

		virtual DeviceDX11^ getDeviceDX11();

		virtual void Init();

	private:
		DeviceDX11^			m_device;

		Platform::Boolean	m_beginRender;

		// Render command queue
		CommandQueue		m_CommandQueue;
	};
}
#endif
