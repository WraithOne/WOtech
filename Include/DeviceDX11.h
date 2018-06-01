////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: DeviceDX11.h
///
///			Description:
///
///			Created:	31.03.2016
///			Edited:		07.01.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_DEVICEDX11_H
#define WO_DEVICEDX11_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Window.h"
#include "DXWrapper.h"

namespace ScreenRotation
{
	// 0-degree Z-rotation
	static const DirectX::XMFLOAT4X4 Rotation0(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	// 90-degree Z-rotation
	static const DirectX::XMFLOAT4X4 Rotation90(
		0.0f, 1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	// 180-degree Z-rotation
	static const DirectX::XMFLOAT4X4 Rotation180(
		-1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	// 270-degree Z-rotation
	static const DirectX::XMFLOAT4X4 Rotation270(
		0.0f, -1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
};// namespace ScreenRotation

namespace WOtech
{
	public ref class DeviceDX11 sealed
	{
	public:
		DeviceDX11(_In_ WOtech::Window^ window);

		void Create();

		void Clear(_In_ Windows::UI::Color color);
		void Clear(_In_ Windows::UI::Color color, _In_ WOtech::CLEAR_FLAG clearFlags, _In_ float32 depth, _In_ uint8 stencil);

		void Present();
		void ValidateDevice();
		void HandleDeviceLost();
		void Trim();

		void setLogicalSize(_In_ Windows::Foundation::Size logicalSize);
		void setCurrentOrientation(_In_ Windows::Graphics::Display::DisplayOrientations currentOrientation);
		void setDpi(_In_ float32 dpi);
		void setCompositionScale(_In_ float32 compositionScaleX, _In_ float32 compositionScaleY);

		void setSampling(_In_ uint32 count, _In_ uint32 quality);
		void setDepthStencil(_In_ Platform::Boolean enable);
		void setWireframe(_In_ Platform::Boolean enable);
		void setViewPort(_In_ float32 topleftx, _In_ float32 toplefty, _In_ float32 width, _In_ float32 height, _In_ float32 mindept, _In_ float32 maxdept, _In_ Platform::Boolean useActualOriantation);
		void setStereoSwapChain(_In_ Platform::Boolean enable);

		uint32						getSampleCount();
		uint32						getSampleQuality();

		float32						getDPI();

		Windows::Foundation::Size	getLogicalSize();
		Windows::Foundation::Size	getRenderTargetSize();

		Platform::Boolean			isStereoSwapChain();

		void PIXBeginEvent(_In_ Platform::String^ name);
		void PIXEndEvent();
		void PIXSetMarker(_In_ Platform::String^ name);

	internal:
		void EnumerateAdapters(_Out_ std::list<IDXGIAdapter4*>* adapterList);
		void EnumerateOutputs(_In_ IDXGIAdapter4* adapter, _Out_ std::list<IDXGIOutput6*>* outputList);
		void EnumerateDisplayModes(_In_ IDXGIOutput6* output, _Out_ std::list<DXGI_MODE_DESC1*>* displayModeList);

		void setRenderTarget(_In_ ID3D11RenderTargetView* target);

		void setPresentationParams(_In_ DXGI_PRESENT_PARAMETERS params);

		IDXGIFactory5*				getFactory();
		ID3D11Device5*				getDevice();
		IDXGIDevice4*				getDXGIDevice();
		ID3D11DeviceContext4*		getContext();

		ID3D11RenderTargetView1*	getRenderTarget();
		IDXGISurface2*				getSurface();

		ID3D11DepthStencilState*	getDepthStencilState();
		ID3D11RasterizerState2*		getRasterizerState();
		D3D11_VIEWPORT				getViewPort();

		D2D1::Matrix3x2F			get2DOrientation();
		DirectX::XMFLOAT4X4			get3DOrientation();

		DXGI_PRESENT_PARAMETERS		getPresentationParams();
	private:
		void CreateDevices();
		void CreateWindowSizeDependentResources();

		void RecreateSwapChain();

		DXGI_MODE_ROTATION			ComputeDisplayRotation();

		~DeviceDX11();

	private:
		WOtech::Window^										m_window;

		Microsoft::WRL::ComPtr<ID3D11Device5>				m_device;
		Microsoft::WRL::ComPtr<IDXGIDevice4>				m_dxgiDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext4>		m_context;
		Microsoft::WRL::ComPtr<IDXGIFactory5>				m_factory;

		Platform::Boolean									m_recreateSwapChain;
		Microsoft::WRL::ComPtr<IDXGISwapChain4>				m_swapChain;
		DXGI_FORMAT											m_swapChainFormat;
		Microsoft::WRL::ComPtr<IDXGISurface2>				m_dxgiBackBuffer;
		UINT												m_backBufferCount;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView1>		m_renderTargetView;

		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		m_depthStencilView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D1>			m_depthStencilBuffer;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState>		m_depthStencilState;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState2>		m_rasterizerState;

		Microsoft::WRL::ComPtr<ID3DUserDefinedAnnotation>	m_userAnnotation;

		D3D11_VIEWPORT										m_viewport;
		D3D_FEATURE_LEVEL									m_featureLevel;

		D3D_DRIVER_TYPE										m_driverType;
		DXGI_ADAPTER_DESC									m_currentAdapterDescription;

		Windows::Graphics::Display::DisplayOrientations		m_nativeOrientation;
		Windows::Graphics::Display::DisplayOrientations		m_currentOrientation;

		DirectX::XMFLOAT4X4									m_orientationTransform3D;
		D2D1::Matrix3x2F									m_orientationTransform2D;

		float32												m_compositionScaleX;
		float32												m_compositionScaleY;
		Windows::Foundation::Size							m_logicalSize;
		float32												m_dpi;

		Windows::Foundation::Size							m_d3dRenderTargetSize;
		Windows::Foundation::Size							m_outputSize;

		DXGI_PRESENT_PARAMETERS								m_presentParameters;
		uint32												m_sampleQuality;
		uint32												m_sampleCount;

		Platform::Boolean									m_stereo;
	};// class DeviceDX11
}// namespace WOtech
#endif