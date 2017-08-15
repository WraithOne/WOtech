////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: DeviceDX11.cpp
///
///			Description:
///
///			Created:	06.05.2014
///			Edited:		15.08.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "DeviceDX11.h"
#include "Utilities.h"
#include "SystemManager.h"
#include <windows.ui.xaml.media.dxinterop.h>

using namespace D2D1;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml::Controls;
using namespace Platform;
using namespace WOtech::DXWrapper;

namespace WOtech
{
	DeviceDX11::DeviceDX11() : m_d3dRenderTargetSize(), m_outputSize()
	{
		m_viewport = { 0 };
		m_featureLevel = D3D_FEATURE_LEVEL_9_1;

		m_nativeOrientation = DisplayOrientations::None;
		m_currentOrientation = DisplayOrientations::None;
		m_dpi = -1.0f;
		m_compositionScaleX = 1.0;
		m_compositionScaleY = 1.0f;

		m_overlaySupportExists = false;
		m_initialCreationCompleted = false;

		// add to SystemManager

		SystemManager::Instance->AddDeviceDX11(this);
	}

	DeviceDX11::~DeviceDX11()
	{
		SystemManager::Instance->RemoveDeviceDX11(this);
	}

	void DeviceDX11::Create()
	{
		// Create Device resources
		CreateDevices();

		// set current window to device resources
		Windows::UI::Core::CoreWindow^ window = Windows::UI::Core::CoreWindow::GetForCurrentThread();
		setWindow(window);
	}

	void DeviceDX11::Present()
	{
		HRESULT hr;

		PIXBEGINEVENTCONTEXT(m_context.Get(), PIX_COLOR_DEFAULT, L"DeviceDX11::Present");

		// The first argument instructs DXGI to block until VSync, putting the application
		// to sleep until the next VSync. This ensures we don't waste any cycles rendering
		// frames that will never be displayed to the screen.
		hr = m_swapChain->Present(1, 0);

		// Discard the contents of the render target.
		// This is a valid operation only when the existing contents will be entirely
		// overwritten. If dirty or scroll rects are used, this call should be removed.
		m_context->DiscardView(m_backBuffer.Get());

		if (m_depthStencilView)
		{
			// Discard the contents of the depth stencil.
			m_context->DiscardView(m_depthStencilView.Get());
		}
			
		// If the device was removed either by a disconnection or a driver upgrade, we
		// must recreate all device resources.
		if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
		{
			HandleDeviceLost();
		}
		else
		{
			ThrowIfFailed(hr);
		}

		PIXENDEVENT();
	}
	void DeviceDX11::Clear(_In_ Color color)
	{
		Clear(color, CLEAR_FLAG::CLEAR_DEPTH, 1.0f, 0);
	}
	void DeviceDX11::Clear(_In_ Color color, _In_ CLEAR_FLAG clearFlags, _In_ float32 depth, _In_ uint8 stencil)
	{
		D2D1_COLOR_F d2d1color = wrapColor(color);
		float32 ColorRGBA[4] = { d2d1color.r / 256.0f, d2d1color.g / 256.0f, d2d1color.b / 256.0f, 1.0f };
		
		PIXBEGINEVENTCONTEXT(m_context.Get(), PIX_COLOR_DEFAULT, L"DEviceDX11::Clear");

		m_context->ClearRenderTargetView(m_backBuffer.Get(), ColorRGBA);
		m_context->ClearDepthStencilView(m_depthStencilView.Get(), wrapClearFlag(clearFlags), depth, stencil);
		m_context->OMSetRenderTargets(1, m_backBuffer.GetAddressOf(), m_depthStencilView.Get());

		m_context->RSSetViewports(1, &m_viewport);
		PIXENDEVENT();
	}

	void DeviceDX11::EnumerateAdapters(_Out_ std::list<IDXGIAdapter*>* adapterList)
	{
		ComPtr<IDXGIAdapter> pAdapter;
		HRESULT hr = E_FAIL;

		uint32 flags = 0;
#ifdef _DEBUG
		flags = DXGI_CREATE_FACTORY_DEBUG;
#endif

		// Create a DXGIFactory object.
		if (m_factory == NULL)
		{
			hr = CreateDXGIFactory2(flags, __uuidof(IDXGIFactory2), &m_factory);
			ThrowIfFailed(hr);
		}

		std::list<IDXGIAdapter*> temp;

		for (UINT i = 0; (hr = m_factory->EnumAdapters(i, &pAdapter)) != DXGI_ERROR_NOT_FOUND; ++i)
		{
			ThrowIfFailed(hr);
			temp.push_back(pAdapter.Get());
		}
		adapterList = &temp;
	}
	void DeviceDX11::EnumerateOutputs(_In_ IDXGIAdapter* adapter, _Out_ std::list<IDXGIOutput*>* outputList)
	{
		uint32 i = 0;
		ComPtr<IDXGIOutput> pOutput;
		std::list<IDXGIOutput*> temp;

		while (adapter->EnumOutputs(i, &pOutput) != DXGI_ERROR_NOT_FOUND)
		{
			temp.push_back(pOutput.Get());
			++i;
		}
		outputList = &temp;
	}
	void DeviceDX11::EnumerateDisplayModes(_In_ IDXGIOutput* output, _Out_ std::list<DXGI_MODE_DESC*>* displayModeList)
	{
		HRESULT hr;

		uint32 numModes = 0;
		DXGI_FORMAT format = DXGI_FORMAT_B8G8R8A8_UNORM;
		uint32 flags = DXGI_ENUM_MODES_INTERLACED;

		// Get the number of elements
		hr = output->GetDisplayModeList(format, flags, &numModes, NULL);
		ThrowIfFailed(hr);
		DXGI_MODE_DESC* displayModes = new DXGI_MODE_DESC[numModes];

		hr = output->GetDisplayModeList(format, flags, &numModes, displayModes);
		ThrowIfFailed(hr);

		for (uint32 i = 0; i <= numModes; i++)
		{
			DXGI_MODE_DESC* temp = NULL;

			temp = &displayModes[i];
			displayModeList->push_back(temp);
		}
	}

	void DeviceDX11::ValidateDevice()
	{
		HRESULT hr;

		ComPtr<IDXGIDevice3> dxgiDevice;
		ThrowIfFailed(m_device.As(&dxgiDevice));

		ComPtr<IDXGIAdapter> deviceAdapter;
		ThrowIfFailed(dxgiDevice->GetAdapter(&deviceAdapter));

		ComPtr<IDXGIFactory2> deviceFactory;
		ThrowIfFailed(deviceAdapter->GetParent(IID_PPV_ARGS(&deviceFactory)));

		ComPtr<IDXGIAdapter1> previousDefaultAdapter;
		ThrowIfFailed(deviceFactory->EnumAdapters1(0, &previousDefaultAdapter));

		DXGI_ADAPTER_DESC previousDesc;
		ThrowIfFailed(previousDefaultAdapter->GetDesc(&previousDesc));

		// Next, get the information for the current default adapter.

		ComPtr<IDXGIFactory2> currentFactory;
		ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&currentFactory)));

		ComPtr<IDXGIAdapter1> currentDefaultAdapter;
		ThrowIfFailed(currentFactory->EnumAdapters1(0, &currentDefaultAdapter));

		DXGI_ADAPTER_DESC currentDesc;
		ThrowIfFailed(currentDefaultAdapter->GetDesc(&currentDesc));

		// If the adapter LUIDs don't match, or if the device reports that it has been removed,
		// a new D3D device must be created.

		if (previousDesc.AdapterLuid.LowPart != currentDesc.AdapterLuid.LowPart ||
			previousDesc.AdapterLuid.HighPart != currentDesc.AdapterLuid.HighPart ||
			FAILED(hr = m_device->GetDeviceRemovedReason()))
		{
			// Release references to resources related to the old device.
			dxgiDevice = nullptr;
			deviceAdapter = nullptr;
			deviceFactory = nullptr;
			previousDefaultAdapter = nullptr;

			// Create a new device and swap chain.
			HandleDeviceLost();
		}
	}
	void DeviceDX11::HandleDeviceLost()
	{
		m_swapChain = nullptr;

		// Recreate devices
		CreateDevices();

		// Create resources
		CreateWindowSizeDependentResources();
	}
	void DeviceDX11::Trim()
	{
		m_dxgiDevice->Trim();
	}

	// SETTERS
	void DeviceDX11::setWindow(_In_ Windows::UI::Core::CoreWindow^ window)
	{
		m_window = window;

		DisplayInformation^ currentDisplayInformation = DisplayInformation::GetForCurrentView();

		m_logicalSize = Windows::Foundation::Size(m_window->Bounds.Width, m_window->Bounds.Height);
		m_nativeOrientation = currentDisplayInformation->NativeOrientation;
		m_currentOrientation = currentDisplayInformation->CurrentOrientation;
		m_dpi = currentDisplayInformation->LogicalDpi;

		CreateWindowSizeDependentResources();
	}
	void DeviceDX11::setLogicalSize(_In_ Windows::Foundation::Size logicalSize)
	{
		if (m_logicalSize != logicalSize)
		{
			m_logicalSize = logicalSize;
			CreateWindowSizeDependentResources();
		}
	}
	void DeviceDX11::setCurrentOrientation(_In_ DisplayOrientations currentOrientation)
	{
		if (m_currentOrientation != currentOrientation)
		{
			m_currentOrientation = currentOrientation;
			CreateWindowSizeDependentResources();
		}
	}
	void DeviceDX11::setDpi(_In_ float32 dpi)
	{
		if (dpi != m_dpi)
		{
			m_dpi = dpi;

			// When the display DPI changes, the logical size of the window (measured in Dips) also changes and needs to be updated.
			m_logicalSize = Windows::Foundation::Size(m_window->Bounds.Width, m_window->Bounds.Height);

			CreateWindowSizeDependentResources();
		}
	}
	void DeviceDX11::setCompositionScale(_In_ float32 compositionScaleX, _In_ float32 compositionScaleY)
	{
		if (m_compositionScaleX != compositionScaleX || m_compositionScaleY != compositionScaleY)
		{
			m_compositionScaleX = compositionScaleX;
			m_compositionScaleY = compositionScaleY;
			CreateWindowSizeDependentResources();
		}
	}

	void DeviceDX11::setRenderTarget(_In_ ID3D11RenderTargetView* Target)
	{
		if (Target)
		{
			PIXBEGINEVENTCONTEXT(m_context.Get(), PIX_COLOR_DEFAULT, L"DeviceDX11::setRenderTarget");

			m_context->OMSetRenderTargets(1, &Target, m_depthStencilView.Get());

			PIXENDEVENT();
		}		
	}

	void DeviceDX11::setDepthStencil(_In_ Platform::Boolean enable)
	{
		HRESULT hr;

		// Setup depth/stencil state.
		D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
		ZeroMemory(&depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

		depthStencilStateDesc.DepthEnable = TRUE;
		depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;

		if (enable == false)
			depthStencilStateDesc.StencilEnable = FALSE;
		else
			depthStencilStateDesc.StencilEnable = TRUE;

		PIXBEGINEVENTCONTEXT(m_context.Get(), PIX_COLOR_DEFAULT, L"DeviceDX11::setDepthStencil");

		hr = m_device->CreateDepthStencilState(&depthStencilStateDesc, &m_depthStencilState);
		ThrowIfFailed(hr);

		PIXENDEVENT();
	}
	void DeviceDX11::setWireframe(_In_ Platform::Boolean enable)
	{
		HRESULT hr;

		// Setup rasterizer state.
		D3D11_RASTERIZER_DESC1 rasterizerDesc;
		ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC1));

		rasterizerDesc.AntialiasedLineEnable = false;
		rasterizerDesc.CullMode = D3D11_CULL_BACK;
		rasterizerDesc.DepthBias = 0;
		rasterizerDesc.DepthBiasClamp = 0.0f;
		rasterizerDesc.DepthClipEnable = true;

		if (enable == false)
			rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		else
			rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;

		rasterizerDesc.FrontCounterClockwise = false;
		rasterizerDesc.MultisampleEnable = false;
		rasterizerDesc.ScissorEnable = false;
		rasterizerDesc.SlopeScaledDepthBias = 0.0f;
		rasterizerDesc.ForcedSampleCount = 0;

		PIXBEGINEVENTCONTEXT(m_context.Get(), PIX_COLOR_DEFAULT, L"DeviceDX11::setWireframe");

		// Create the rasterizer state object.
		hr = m_device->CreateRasterizerState1(&rasterizerDesc, m_rasterizerState.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);

		m_context->RSSetState(m_rasterizerState.Get());

		PIXENDEVENT();
	}
	void DeviceDX11::setViewPort(_In_ float32 topleftx, _In_ float32 toplefty, _In_ float32 width, _In_ float32 height, _In_ float32 mindept, _In_ float32 maxdept, _In_ Platform::Boolean useActualOriantation)
	{
		// Range Check
		float32 temptopleftx = WOtech::InRange(topleftx, D3D11_VIEWPORT_BOUNDS_MIN, D3D11_VIEWPORT_BOUNDS_MAX);
		float32 temptoplefty = WOtech::InRange(toplefty, D3D11_VIEWPORT_BOUNDS_MIN, D3D11_VIEWPORT_BOUNDS_MAX);
		float32 tempwidth = WOtech::InRange(width, D3D11_VIEWPORT_BOUNDS_MIN, D3D11_VIEWPORT_BOUNDS_MAX);
		float32 tempheight = WOtech::InRange(height, D3D11_VIEWPORT_BOUNDS_MIN, D3D11_VIEWPORT_BOUNDS_MAX);
		float32 tempmindepth = WOtech::InRange(topleftx, 0.0f, 1.0f);
		float32 tempmaxdepth = WOtech::InRange(topleftx, 0.0f, 1.0f);

		D3D11_VIEWPORT viewPort;
		if (useActualOriantation)
		{
			DXGI_MODE_ROTATION displayRotation = ComputeDisplayRotation();

			Platform::Boolean swapDimensions = displayRotation == DXGI_MODE_ROTATION_ROTATE90 || displayRotation == DXGI_MODE_ROTATION_ROTATE270;
			viewPort.Width = swapDimensions ? tempheight : tempwidth;
			viewPort.Height = swapDimensions ? tempwidth : tempheight;
			viewPort.TopLeftX = swapDimensions ? temptoplefty : temptopleftx;
			viewPort.TopLeftY = swapDimensions ? temptopleftx : temptoplefty;
		}
		else
		{
			viewPort.Width = tempwidth;
			viewPort.Height = tempheight;
			viewPort.TopLeftX = temptopleftx;
			viewPort.TopLeftY = temptoplefty;
		}
		viewPort.MinDepth = tempmindepth;
		viewPort.MaxDepth = tempmaxdepth;

		m_viewport = viewPort;

		PIXBEGINEVENTCONTEXT(m_context.Get(), PIX_COLOR_DEFAULT, L"DeviceDX11::setViewPort");

		m_context->RSSetViewports(1, &viewPort);

		PIXENDEVENT();
	}

	// GETTERS
	IDXGIFactory2* DeviceDX11::getFactory()
	{
		return m_factory.Get();
	}
	ID3D11Device2* DeviceDX11::getDevice()
	{
		return m_device.Get();
	}
	IDXGIDevice3* DeviceDX11::getDXGIDevice()
	{
		return m_dxgiDevice.Get();
	}
	ID3D11DeviceContext2* DeviceDX11::getContext()
	{
		return m_context.Get();
	}

	IDXGISurface2* DeviceDX11::getSurface()
	{
		return m_dxgiBackBuffer.Get();
	}

	ID3D11DepthStencilState* DeviceDX11::getDepthStencilState()
	{
		return m_depthStencilState.Get();
	}
	ID3D11RasterizerState1* DeviceDX11::getRasterizerState()
	{
		return m_rasterizerState.Get();
	}
	D3D11_VIEWPORT DeviceDX11::getViewPort()
	{
		return m_viewport;
	}

	// GETTERS
	float32 DeviceDX11::getDPI()
	{
		return m_dpi;
	}
	Windows::Foundation::Size DeviceDX11::getLogicalSize()
	{
		return m_logicalSize;
	}
	Windows::Foundation::Size DeviceDX11::getRenderTargetSize()
	{
		return m_d3dRenderTargetSize;
	}

	D2D1::Matrix3x2F DeviceDX11::get2DOrientation()
	{
		return m_orientationTransform2D;
	}
	DirectX::XMFLOAT4X4 DeviceDX11::get3DOrientation()
	{
		return m_orientationTransform3D;
	}

	uint32 DeviceDX11::getSampleCount()
	{
		return m_sampleCount;
	}
	uint32 DeviceDX11::getSampleQuality()
	{
		return m_sampleQuality;
	}

	// Private
	void DeviceDX11::CreateDevices()
	{
		PIXBEGINEVENT(PIX_COLOR_DEFAULT, L"DeviceDX11::CreateDevices");

		uint32 creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
		if (SDKLayersAvailable())
		{
			// If the project is in a debug build, enable debugging via SDK Layers with this flag.
			creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
		}
#endif
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		ComPtr<ID3D11Device> device;
		ComPtr<ID3D11DeviceContext> context;

		HRESULT hr;

		PIXBEGINEVENTCONTEXT(m_context.Get(), PIX_COLOR_DEFAULT, L"D3D11CreateDevice HW");

		hr = D3D11CreateDevice(
			nullptr,					// Specify nullptr to use the default adapter.
			D3D_DRIVER_TYPE_HARDWARE,	// Create a device using the hardware graphics driver.
			0,							// Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
			creationFlags,				// Set debug and Direct2D compatibility flags.
			featureLevels,				// List of feature levels this app can support.
			ARRAYSIZE(featureLevels),	// Size of the list above.
			D3D11_SDK_VERSION,			// Always set this to D3D11_SDK_VERSION for Windows Store apps.
			&device,					// Returns the Direct3D device created.
			&m_featureLevel,			// Returns feature level of device created.
			&context					// Returns the device immediate context.
		);

		PIXENDEVENT();

		if (FAILED(hr))
		{
			PIXBEGINEVENTCONTEXT(m_context.Get(), PIX_COLOR_DEFAULT, L"D3D11CreateDevice WARP");

			// If the initialization fails, fall back to the WARP device.
			// For more information on WARP, see:
			// http://go.microsoft.com/fwlink/?LinkId=286690
			hr = D3D11CreateDevice(nullptr,
				D3D_DRIVER_TYPE_WARP, // Create a WARP device instead of a hardware device.
				0,
				creationFlags,
				featureLevels,
				ARRAYSIZE(featureLevels),
				D3D11_SDK_VERSION,
				&device,
				&m_featureLevel,
				&context);
			ThrowIfFailed(hr);

			PIXENDEVENT();
		}

		// Store pointers to the Direct3D 11.1 API device ,immediate context and DXGI device.
		hr = device.As(&m_device);
		ThrowIfFailed(hr);

		hr = context.As(&m_context);
		ThrowIfFailed(hr);

		hr = m_device.As(&m_dxgiDevice);
		ThrowIfFailed(hr);

		PIXENDEVENT();
	}
	void DeviceDX11::CreateWindowSizeDependentResources()
	{
		HRESULT hr;
		
		PIXBEGINEVENT(PIX_COLOR_DEFAULT, L"DeviceDX11::CreateWindowDependentResources");

		PIXBEGINEVENTCONTEXT(m_context.Get(), PIX_COLOR_DEFAULT, L"Clear previous Content");
		// Clear the previous window size specific context.
		ID3D11RenderTargetView* nullViews[] = { nullptr };
		m_context->OMSetRenderTargets(ARRAYSIZE(nullViews), nullViews, m_depthStencilView.Get());
		m_dxgiBackBuffer = nullptr;
		m_backBuffer = nullptr;

		m_context->Flush();
		m_context->ClearState();
		PIXENDEVENT();

		// Calculate the necessary render target size in pixels (for CoreWindow).
		m_outputSize.Width = ConvertDipsToPixels(m_logicalSize.Width, m_dpi);
		m_outputSize.Height = ConvertDipsToPixels(m_logicalSize.Height, m_dpi);

		// Prevent zero size DirectX content from being created.
		m_outputSize.Width = max(m_outputSize.Width, 1);
		m_outputSize.Height = max(m_outputSize.Height, 1);

		// The width and height of the swap chain must be based on the window's
		// natively-oriented width and height. If the window is not in the native
		// orientation, the dimensions must be reversed.
		DXGI_MODE_ROTATION displayRotation = ComputeDisplayRotation();

		Platform::Boolean swapDimensions = displayRotation == DXGI_MODE_ROTATION_ROTATE90 || displayRotation == DXGI_MODE_ROTATION_ROTATE270;
		m_d3dRenderTargetSize.Width = swapDimensions ? m_outputSize.Height : m_outputSize.Width;
		m_d3dRenderTargetSize.Height = swapDimensions ? m_outputSize.Width : m_outputSize.Height;

		if (m_swapChain != nullptr)
		{
			PIXBEGINEVENT(PIX_COLOR_DEFAULT, L" Swapchain->ResizeBuffers");
			// If the swap chain already exists, resize it.
			hr = m_swapChain->ResizeBuffers(
				0, //0= preserv 2 =Double-buffered swap chain.
				static_cast<uint32>(m_d3dRenderTargetSize.Width),
				static_cast<uint32>(m_d3dRenderTargetSize.Height),
				DXGI_FORMAT_B8G8R8A8_UNORM,
				0
			);
			PIXENDEVENT();

			if (hr == DXGI_ERROR_DEVICE_REMOVED)
			{
				// If the device was removed for any reason, a new device and swap chain will need to be created.
				HandleDeviceLost();

				// Everything is set up now. Do not continue execution of this method. HandleDeviceLost will reenter this method
				// and correctly set up the new device.
				return;
			}
			else
			{
				ThrowIfFailed(hr);
			}
		}
		else
		{
			// Otherwise, create a new one using the same adapter as the existing Direct3D device.
			DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };

			swapChainDesc.Width = static_cast<uint32>(m_d3dRenderTargetSize.Width); // Match the size of the window.
			swapChainDesc.Height = static_cast<uint32>(m_d3dRenderTargetSize.Height);
			swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // This is the most common swap chain format.
			swapChainDesc.Stereo = false;
			swapChainDesc.SampleDesc.Count = 1; // Don't use multi-sampling.
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.BufferCount = 2; // Use double-buffering to minimize latency.
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // All Windows Store apps must use this SwapEffect. default: DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL
			swapChainDesc.Flags = 0;
			swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE; // When using XAML interop, this value cannot be DXGI_ALPHA_MODE_PREMULTIPLIED.
			swapChainDesc.Scaling = DXGI_SCALING_NONE;

			// This sequence obtains the DXGI factory that was used to create the Direct3D device above.
			ComPtr<IDXGIDevice3> dxgiDevice;
			ThrowIfFailed(m_device.As(&dxgiDevice));

			ComPtr<IDXGIAdapter> dxgiAdapter;
			ThrowIfFailed(dxgiDevice->GetAdapter(&dxgiAdapter));

			ComPtr<IDXGIFactory2> dxgiFactory;
			ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory)));

			PIXBEGINEVENT(PIX_COLOR_DEFAULT, L"CreateSwapChainForCoreWindow");
			ThrowIfFailed(dxgiFactory->CreateSwapChainForCoreWindow(m_device.Get(),
				reinterpret_cast<IUnknown*>(m_window.Get()),
				&swapChainDesc,
				nullptr,
				&m_swapChain));
			PIXENDEVENT();

			// Ensure that DXGI does not queue more than one frame at a time. This both reduces latency and
			// ensures that the application will only render after each VSync, minimizing power consumption.
			ThrowIfFailed(dxgiDevice->SetMaximumFrameLatency(1));
		}

		// Set the proper orientation for the swap chain, and generate 2D and
		// 3D matrix transformations for rendering to the rotated swap chain.
		// Note the rotation angle for the 2D and 3D transforms are different.
		// This is due to the difference in coordinate spaces.  Additionally,
		// the 3D matrix is specified explicitly to avoid rounding errors.

		switch (displayRotation)
		{
		case DXGI_MODE_ROTATION_IDENTITY:
			m_orientationTransform2D = Matrix3x2F::Identity();
			m_orientationTransform3D = ScreenRotation::Rotation0;
			break;

		case DXGI_MODE_ROTATION_ROTATE90:
			m_orientationTransform2D =
				Matrix3x2F::Rotation(90.0f) *
				Matrix3x2F::Translation(m_logicalSize.Height, 0.0f);
			m_orientationTransform3D = ScreenRotation::Rotation270;
			break;

		case DXGI_MODE_ROTATION_ROTATE180:
			m_orientationTransform2D =
				Matrix3x2F::Rotation(180.0f) *
				Matrix3x2F::Translation(m_logicalSize.Width, m_logicalSize.Height);
			m_orientationTransform3D = ScreenRotation::Rotation180;
			break;

		case DXGI_MODE_ROTATION_ROTATE270:
			m_orientationTransform2D =
				Matrix3x2F::Rotation(270.0f) *
				Matrix3x2F::Translation(0.0f, m_logicalSize.Width);
			m_orientationTransform3D = ScreenRotation::Rotation90;
			break;

		default:
			throw ref new FailureException();
		}

		// The Windows phone compositor behaves differently than the compositor on Windows and this API is not needed or supported.
		hr = m_swapChain->SetRotation(displayRotation);
		ThrowIfFailed(hr);

		// Create a render target view of the swap chain back buffer.
		ComPtr<ID3D11Texture2D> backBuffer;
		hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
		ThrowIfFailed(hr);

		hr = m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_backBuffer);
		ThrowIfFailed(hr);

		// Create a depth stencil view for use with 3D rendering if needed.
		CD3D11_TEXTURE2D_DESC depthStencilDesc(DXGI_FORMAT_D24_UNORM_S8_UINT, static_cast<uint32>(m_d3dRenderTargetSize.Width), static_cast<uint32>(m_d3dRenderTargetSize.Height), 1, 1, D3D11_BIND_DEPTH_STENCIL);

		hr = m_device->CreateTexture2D(&depthStencilDesc, nullptr, &m_depthStencilBuffer);
		ThrowIfFailed(hr);

		CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
		hr = m_device->CreateDepthStencilView(m_depthStencilBuffer.Get(), &depthStencilViewDesc, &m_depthStencilView);
		ThrowIfFailed(hr);

		// Set REnder Target View and depth Stencil View
		m_context->OMSetRenderTargets(1, m_backBuffer.GetAddressOf(), m_depthStencilView.Get());

		// Set RasterizerState
		setWireframe(false);

		// Set the 3D rendering viewport to target the entire window.
		m_viewport = CD3D11_VIEWPORT(0.0f, 0.0f, m_d3dRenderTargetSize.Width, m_d3dRenderTargetSize.Height, 0.0f, 1.0f);

		PIXBEGINEVENTCONTEXT(m_context.Get(), PIX_COLOR_DEFAULT, L"SetViewPort");
		m_context->RSSetViewports(1, &m_viewport);
		PIXENDEVENT();

		// Create DXGI Buffer for D2D1
		hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&m_dxgiBackBuffer));
		ThrowIfFailed(hr);

		PIXENDEVENT();
		
	}
	DXGI_MODE_ROTATION DeviceDX11::ComputeDisplayRotation()
	{
		DXGI_MODE_ROTATION rotation = DXGI_MODE_ROTATION_UNSPECIFIED;

		// Note: NativeOrientation can only be Landscape or Portrait even though
		// the DisplayOrientations enum has other values.
		switch (m_nativeOrientation)
		{
		case DisplayOrientations::Landscape:
			switch (m_currentOrientation)
			{
			case DisplayOrientations::Landscape:
				rotation = DXGI_MODE_ROTATION_IDENTITY;
				break;

			case DisplayOrientations::Portrait:
				rotation = DXGI_MODE_ROTATION_ROTATE270;
				break;

			case DisplayOrientations::LandscapeFlipped:
				rotation = DXGI_MODE_ROTATION_ROTATE180;
				break;

			case DisplayOrientations::PortraitFlipped:
				rotation = DXGI_MODE_ROTATION_ROTATE90;
				break;
			}
			break;

		case DisplayOrientations::Portrait:
			switch (m_currentOrientation)
			{
			case DisplayOrientations::Landscape:
				rotation = DXGI_MODE_ROTATION_ROTATE90;
				break;

			case DisplayOrientations::Portrait:
				rotation = DXGI_MODE_ROTATION_IDENTITY;
				break;

			case DisplayOrientations::LandscapeFlipped:
				rotation = DXGI_MODE_ROTATION_ROTATE270;
				break;

			case DisplayOrientations::PortraitFlipped:
				rotation = DXGI_MODE_ROTATION_ROTATE180;
				break;
			}
			break;
		}
		return rotation;
	}
}// namespace WOtech