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
///			Edited:		13.11.2016
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_FORWARDRENDERER_H
#define WO_FORWARDRENDERER_H

//////////////
// INCLUDES //
//////////////
#include "IRenderer.h"

namespace WOtech
{
	public ref class ForwardRenderer sealed : public IRenderer
	{
	public:
		ForwardRenderer(DeviceDX11^ device);

		virtual void Begin();
		virtual void Submit(Mesh^ mesh, Camera^ camera, Windows::Foundation::Numerics::float4x4 transform);
		virtual void Submit();
		virtual void End();
		virtual void Present();

		virtual DeviceDX11^ getDeviceDX11();

		virtual void Init();

	private:
		CommandQueue m_CommandQueue;
		DeviceDX11^ m_device;

		// Uniform buffer
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_worldCB;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_viewCB;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_pojectionCB;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_modelCB;
	};
}
#endif
