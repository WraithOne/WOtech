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
///			Edited:		17.08.2017
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_DEFERREDRENDERER_H
#define WO_DEFERREDRENDERER_H

//////////////
// INCLUDES //
//////////////
#include "IRenderer.h"
#include "3DComponents.h"
#include "DeviceDX11.h"
#include "RenderCommand.h"

namespace WOtech
{
	ref class DeferredRenderer sealed : IRenderer
	{
	public:
		DeferredRenderer(_In_ DeviceDX11^ device);

		virtual void Begin();
		virtual void Submit(_In_ Mesh^ mesh, _In_ Camera^ camera, _In_ Windows::Foundation::Numerics::float4x4 transform);
		virtual void Submit();
		virtual void End();
		virtual void Present();

		virtual DeviceDX11^  getDeviceDX11();

		virtual void Init(_In_ Windows::UI::Color clearColor);

	private:
		CommandQueue m_CommandQueue;
		DeviceDX11^ m_device;

		// Uniform buffer
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_modelCB;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_viewCB;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_pojectionCB;
		
		// ClearColor
		Windows::UI::Color m_clearColor;
	};
}
#endif