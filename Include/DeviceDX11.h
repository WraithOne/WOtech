////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: DeviceDX11.h
///
///			Created:	31.03.2016
///			Edited:		19.02.2017
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

		void Create(_In_ Windows::UI::Core::CoreWindow^ window);

		void Clear(_In_ Windows::UI::Color color);
		void Clear(_In_ Windows::UI::Color color, _In_ WOtech::DXWrapper::CLEAR_FLAG ClearFlags, _In_ float32 Depth, _In_ uint8 Stencil);

		void Present();
		void ValidateDevice();
		void HandleDeviceLost();
		void Trim();

		// SETTERS
		void SetWindow(_In_ Windows::UI::Core::CoreWindow^ window);
		void SetLogicalSize(_In_ Windows::Foundation::Size logicalSize);
		void SetCurrentOrientation(_In_ Windows::Graphics::Display::DisplayOrientations currentOrientation);
		void SetDpi(_In_ float32 dpi);
		void SetCompositionScale(_In_ float32 compositionScaleX, _In_ float32 compositionScaleY);

		
		void setDepthStencil(_In_ Platform::Boolean Enable);
		void setWireframe(_In_ Platform::Boolean Enable);
		void setViewPort(_In_ float32 Width, _In_ float32 Height, _In_ float32 Mindept, _In_ float32 Maxdept, _In_ float32 Topleftx, _In_ float32 Toplefty);

		// GETTERS
		uint32 getSampleCount();
		uint32 getSampleQuality();

		float32	getDPI();

		Windows::Foundation::Size getLogicalSize();
		Windows::Foundation::Size getRenderTargetSize();

	internal:
		void setRenderTarget(_In_ ID3D11RenderTargetView* Target);

		void EnumerateAdapters(_Out_ std::list<IDXGIAdapter*>* adapterList);
		void EnumerateOutputs(_In_ IDXGIAdapter* adapter, _Out_ std::list<IDXGIOutput*>* outputList);
		void EnumerateDisplayModes(_In_ IDXGIOutput* output, _Out_ std::list<DXGI_MODE_DESC*>* displayModeList);

		IDXGIFactory2*				getFactory();
		ID3D11Device2*				getDevice();
		IDXGIDevice3*				getDXGIDevice();
		ID3D11DeviceContext2*		GetContext();

		IDXGISurface2*				getSurface();

		ID3D11DepthStencilState*	getDepthStencilState();
		ID3D11RasterizerState1*		getRasterizerState();
		D3D11_VIEWPORT				getViewPort();

		D2D1::Matrix3x2F			get2DOrientation();
		DirectX::XMFLOAT4X4			get3DOrientation();

	private:
		~DeviceDX11();
		void CreateDevices();
		void CreateWindowSizeDependentResources();
		DXGI_MODE_ROTATION			ComputeDisplayRotation();

	private:
		// Reference to Window
		Platform::Agile<Windows::UI::Core::CoreWindow>	m_window;

		Microsoft::WRL::ComPtr<ID3D11Device2>			m_device;
		Microsoft::WRL::ComPtr<IDXGIDevice3>			m_dxgiDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext2>	m_context;
		Microsoft::WRL::ComPtr<IDXGIFactory2>			m_factory;

		Microsoft::WRL::ComPtr<IDXGISwapChain1>			m_swapChain;

		Microsoft::WRL::ComPtr<IDXGISurface2>			m_dxgiBackBuffer;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_backBuffer;

		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_depthStencilView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			m_depthStencilBuffer;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState>	m_depthStencilState;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState1>	m_rasterizerState;

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

		uint32											m_sampleQuality;
		uint32											m_sampleCount;

		Platform::Boolean								m_overlaySupportExists;
		Platform::Boolean								m_initialCreationCompleted;
	};// class DeviceDX11
}

#endif