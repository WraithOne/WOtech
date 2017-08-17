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
///			Edited:		17.08.2017
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_DEVICEDX11_H
#define WO_DEVICEDX11_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
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
};

namespace WOtech
{
	public ref class DeviceDX11 sealed
	{
	public:
		DeviceDX11();

		void Create();

		void Clear(_In_ Windows::UI::Color color);
		void Clear(_In_ Windows::UI::Color color, _In_ WOtech::DXWrapper::CLEAR_FLAG clearFlags, _In_ float32 depth, _In_ uint8 stencil);

		void Present();
		void ValidateDevice();
		void HandleDeviceLost();
		void Trim();

		// SETTERS
		void setLogicalSize(_In_ Windows::Foundation::Size logicalSize);
		void setCurrentOrientation(_In_ Windows::Graphics::Display::DisplayOrientations currentOrientation);
		void setDpi(_In_ float32 dpi);
		void setCompositionScale(_In_ float32 compositionScaleX, _In_ float32 compositionScaleY);

		void setDepthStencil(_In_ Platform::Boolean enable);
		void setWireframe(_In_ Platform::Boolean enable);
		void setViewPort(_In_ float32 topleftx, _In_ float32 toplefty, _In_ float32 width, _In_ float32 height, _In_ float32 mindept, _In_ float32 maxdept, _In_ Platform::Boolean useActualOriantation);

		// GETTERS
		uint32 getSampleCount();
		uint32 getSampleQuality();

		float32	getDPI();

		Windows::Foundation::Size getLogicalSize();
		Windows::Foundation::Size getRenderTargetSize();

	internal:
		void CreateDevices();
		void CreateWindowSizeDependentResources();

		void setWindow(_In_ Windows::UI::Core::CoreWindow^ window);
		void setRenderTarget(_In_ ID3D11RenderTargetView* target);

		void EnumerateAdapters(_Out_ std::list<IDXGIAdapter*>* adapterList);
		void EnumerateOutputs(_In_ IDXGIAdapter* adapter, _Out_ std::list<IDXGIOutput*>* outputList);
		void EnumerateDisplayModes(_In_ IDXGIOutput* output, _Out_ std::list<DXGI_MODE_DESC*>* displayModeList);

		IDXGIFactory5*				getFactory();
		ID3D11Device4*				getDevice();
		IDXGIDevice4*				getDXGIDevice();
		ID3D11DeviceContext4*		getContext();

		IDXGISurface2*				getSurface();

		ID3D11DepthStencilState*	getDepthStencilState();
		ID3D11RasterizerState1*		getRasterizerState();
		D3D11_VIEWPORT				getViewPort();

		D2D1::Matrix3x2F			get2DOrientation();
		DirectX::XMFLOAT4X4			get3DOrientation();

		DXGI_MODE_ROTATION			ComputeDisplayRotation();
	private:
		~DeviceDX11();

	private:
		// Reference to Window
		Platform::Agile<Windows::UI::Core::CoreWindow>	m_window;

		Microsoft::WRL::ComPtr<ID3D11Device4>			m_device;// todo: update to Version 5 when debug tools supports
		Microsoft::WRL::ComPtr<IDXGIDevice4>			m_dxgiDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext4>	m_context;
		Microsoft::WRL::ComPtr<IDXGIFactory5>			m_factory;

		Microsoft::WRL::ComPtr<IDXGISwapChain4>			m_swapChain;

		Microsoft::WRL::ComPtr<IDXGISurface2>			m_dxgiBackBuffer;
		UINT											m_backBufferCount;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_renderTargetView;

		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_depthStencilView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			m_depthStencilBuffer;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState>	m_depthStencilState;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState2>	m_rasterizerState;

		D3D11_VIEWPORT									m_viewport;
		D3D_FEATURE_LEVEL								m_featureLevel;

		D3D_DRIVER_TYPE									m_driverType;
		DXGI_ADAPTER_DESC								m_currentAdapterDescription;

		Windows::Graphics::Display::DisplayOrientations	m_nativeOrientation;
		Windows::Graphics::Display::DisplayOrientations	m_currentOrientation;

		// Transforms used for display orientation.
		DirectX::XMFLOAT4X4								m_orientationTransform3D;
		D2D1::Matrix3x2F								m_orientationTransform2D;

		float32											m_compositionScaleX;
		float32											m_compositionScaleY;
		Windows::Foundation::Size						m_logicalSize;
		float32											m_dpi;

		Windows::Foundation::Size						m_d3dRenderTargetSize;
		Windows::Foundation::Size						m_outputSize;

		DXGI_PRESENT_PARAMETERS							m_presentParameters;
		uint32											m_sampleQuality;
		uint32											m_sampleCount;

		Platform::Boolean								m_overlaySupportExists;
		Platform::Boolean								m_initialCreationCompleted;
	};// class DeviceDX11
}

#endif