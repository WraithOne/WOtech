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
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <DeviceDX11.h>
#include <Utilities.h>
#include <SystemManager.h>

namespace WOtech
{
	DeviceDX11::DeviceDX11(_In_ WOtech::Window^ window) : m_d3dRenderTargetSize(), m_outputSize()
	{
		m_window = window;

		m_recreateSwapChain = true;

		m_swapChainFormat = DXGI_FORMAT_B8G8R8A8_UNORM; // This is the most common swap chain format.
		m_backBufferCount = 2;

		m_viewport = { 0 };
		m_featureLevel = D3D_FEATURE_LEVEL_11_0;

		m_nativeOrientation = Windows::Graphics::Display::DisplayOrientations::None;
		m_currentOrientation = Windows::Graphics::Display::DisplayOrientations::None;

		m_compositionScaleX = 1.0f;
		m_compositionScaleY = 1.0f;

		m_dpi = -1.0f;

		m_presentParameters = { 0 };
		m_sampleCount = 1;
		m_sampleQuality = 0;

		m_stereo = false;

		// add to SystemManager
		SystemManager::Instance->AddDeviceDX11(this);
	}

	void DeviceDX11::Create()
	{
		// Create Device resources
		CreateDevices();

		auto window = m_window->getCoreWindow();
		Windows::Graphics::Display::DisplayInformation^ currentDisplayInformation = Windows::Graphics::Display::DisplayInformation::GetForCurrentView();

		m_logicalSize = Windows::Foundation::Size(window->Bounds.Width, window->Bounds.Height);
		m_nativeOrientation = currentDisplayInformation->NativeOrientation;
		m_currentOrientation = currentDisplayInformation->CurrentOrientation;
		m_dpi = currentDisplayInformation->LogicalDpi;

		CreateWindowSizeDependentResources();
	}

	void DeviceDX11::Clear(_In_ Windows::UI::Color color)
	{
		Clear(color, CLEAR_FLAG::CLEAR_DEPTH, 1.0f, 0);
	}
	void DeviceDX11::Clear(_In_ Windows::UI::Color color, _In_ CLEAR_FLAG clearFlags, _In_ float32 depth, _In_ uint8 stencil)
	{
		m_context->RSSetViewports(1, &m_viewport);

		ID3D11RenderTargetView *const targets[1] = { m_renderTargetView.Get() };// todo: make it backbuffer count
		m_context->OMSetRenderTargets(1, targets, m_depthStencilView.Get());

		m_context->ClearRenderTargetView(m_renderTargetView.Get(), WOtech::DXWrapper::wrapColorD3D(color));
		m_context->ClearDepthStencilView(m_depthStencilView.Get(), WOtech::DXWrapper::wrapClearFlag(clearFlags), depth, stencil);
	}

	void DeviceDX11::Present()
	{
		HRESULT hr;

		hr = m_swapChain->Present1(1, 0, &m_presentParameters);

		m_context->DiscardView1(m_renderTargetView.Get(), nullptr, 0);

		if (m_depthStencilView)
		{
			m_context->DiscardView1(m_depthStencilView.Get(), nullptr, 0);
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
	}
	void DeviceDX11::ValidateDevice()
	{
		HRESULT hr;

		Microsoft::WRL::ComPtr<IDXGIDevice3> dxgiDevice;
		ThrowIfFailed(m_device.As(&dxgiDevice));

		Microsoft::WRL::ComPtr<IDXGIAdapter> deviceAdapter;
		ThrowIfFailed(dxgiDevice->GetAdapter(&deviceAdapter));

		Microsoft::WRL::ComPtr<IDXGIFactory2> deviceFactory;
		ThrowIfFailed(deviceAdapter->GetParent(IID_PPV_ARGS(&deviceFactory)));

		Microsoft::WRL::ComPtr<IDXGIAdapter1> previousDefaultAdapter;
		ThrowIfFailed(deviceFactory->EnumAdapters1(0, &previousDefaultAdapter));

		DXGI_ADAPTER_DESC previousDesc;
		ThrowIfFailed(previousDefaultAdapter->GetDesc(&previousDesc));

		// Next, get the information for the current default adapter.

		Microsoft::WRL::ComPtr<IDXGIFactory2> currentFactory;
		ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&currentFactory)));

		Microsoft::WRL::ComPtr<IDXGIAdapter1> currentDefaultAdapter;
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

	void DeviceDX11::setLogicalSize(_In_ Windows::Foundation::Size logicalSize)
	{
		if (m_logicalSize != logicalSize)
		{
			m_logicalSize = logicalSize;
			CreateWindowSizeDependentResources();
		}
	}
	void DeviceDX11::setCurrentOrientation(_In_ Windows::Graphics::Display::DisplayOrientations currentOrientation)
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
			auto window = m_window->getCoreWindow();

			// When the display DPI changes, the logical size of the window (measured in Dips) also changes and needs to be updated.
			m_logicalSize = Windows::Foundation::Size(window->Bounds.Width, window->Bounds.Height);

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

	void DeviceDX11::setSampling(_In_ uint32 count, _In_ uint32 quality)
	{
		uint32 maxquality = 0U;

		m_sampleCount = InRange(count, 1U, 4U);//  Direct3D 11 video cards are guaranteed to support up to 4, minimum is 1

		ThrowIfFailed(m_device->CheckMultisampleQualityLevels(m_swapChainFormat, m_sampleCount, &maxquality));
		m_sampleQuality = InRange(quality, 0U, maxquality);

		RecreateSwapChain();
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

		hr = m_device->CreateDepthStencilState(&depthStencilStateDesc, &m_depthStencilState);
		ThrowIfFailed(hr);
	}
	void DeviceDX11::setWireframe(_In_ Platform::Boolean enable)
	{
		HRESULT hr;

		// Setup rasterizer state.
		D3D11_RASTERIZER_DESC2 rasterizerDesc;
		ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC1));

		if (enable == false)
			rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		else
			rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
		rasterizerDesc.CullMode = D3D11_CULL_BACK;
		rasterizerDesc.FrontCounterClockwise = false;
		rasterizerDesc.DepthBias = 0;
		rasterizerDesc.DepthBiasClamp = 0.0f;
		rasterizerDesc.SlopeScaledDepthBias = 0.0f;
		rasterizerDesc.DepthClipEnable = true;
		rasterizerDesc.ScissorEnable = false;
		rasterizerDesc.MultisampleEnable = false;// todo: multisampling?
		rasterizerDesc.AntialiasedLineEnable = false;
		rasterizerDesc.ForcedSampleCount = 0;
		rasterizerDesc.ConservativeRaster = D3D11_CONSERVATIVE_RASTERIZATION_MODE_OFF;

		// Create the rasterizer state object.
		hr = m_device->CreateRasterizerState2(&rasterizerDesc, m_rasterizerState.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);

		m_context->RSSetState(m_rasterizerState.Get());
	}
	void DeviceDX11::setViewPort(_In_ float32 topleftx, _In_ float32 toplefty, _In_ float32 width, _In_ float32 height, _In_ float32 mindept, _In_ float32 maxdept, _In_ Platform::Boolean useActualOriantation)
	{
		float32 boundsMAX = static_cast<float32>(D3D11_VIEWPORT_BOUNDS_MAX);
		float32 boundsMIN = static_cast<float32>(D3D11_VIEWPORT_BOUNDS_MIN);
		// Range Check
		float32 temptopleftx = WOtech::InRange(topleftx, boundsMIN, boundsMAX);
		float32 temptoplefty = WOtech::InRange(toplefty, boundsMIN, boundsMAX);
		float32 tempwidth = WOtech::InRange(width, boundsMIN, boundsMAX);
		float32 tempheight = WOtech::InRange(height, boundsMIN, boundsMAX);
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

		m_context->RSSetViewports(1, &viewPort);
	}

	void DeviceDX11::setStereoSwapChain(_In_ Platform::Boolean enable)
	{
		m_stereo = enable;

		RecreateSwapChain();
	}

	uint32 DeviceDX11::getSampleCount()
	{
		return m_sampleCount;
	}
	uint32 DeviceDX11::getSampleQuality()
	{
		return m_sampleQuality;
	}

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

	Platform::Boolean DeviceDX11::isStereoSwapChain()
	{
		return m_stereo;
	}

	void DeviceDX11::PIXBeginEvent(_In_ Platform::String ^ name)
	{
		if (m_userAnnotation)
		{
			m_userAnnotation->BeginEvent(name->Data());
		}
	}
	void DeviceDX11::PIXEndEvent()
	{
		if (m_userAnnotation)
		{
			m_userAnnotation->EndEvent();
		}
	}
	void DeviceDX11::PIXSetMarker(_In_ Platform::String ^ name)
	{
		if (m_userAnnotation)
		{
			m_userAnnotation->SetMarker(name->Data());
		}
	}

	void DeviceDX11::EnumerateAdapters(_Out_ std::list<IDXGIAdapter4*>* adapterList)
	{
		Microsoft::WRL::ComPtr<IDXGIAdapter1> pAdapter;
		HRESULT hr = E_FAIL;

		uint32 flags = 0;
#ifdef _DEBUG
		flags = DXGI_CREATE_FACTORY_DEBUG;
#endif

		// Create a DXGIFactory object.
		if (m_factory == NULL)
		{
			hr = CreateDXGIFactory2(flags, __uuidof(IDXGIFactory5), &m_factory);
			ThrowIfFailed(hr);
		}

		std::list<IDXGIAdapter4*> tempList;

		for (UINT i = 0; (hr = m_factory->EnumAdapters1(i, &pAdapter)) != DXGI_ERROR_NOT_FOUND; ++i)
		{
			ThrowIfFailed(hr);
			Microsoft::WRL::ComPtr<IDXGIAdapter4> temp;
			pAdapter.As(&temp);

			tempList.push_back(temp.Get());
		}
		adapterList = &tempList;
	}
	void DeviceDX11::EnumerateOutputs(_In_ IDXGIAdapter4* adapter, _Out_ std::list<IDXGIOutput6*>* outputList)
	{
		uint32 i = 0;
		Microsoft::WRL::ComPtr<IDXGIOutput> pOutput;
		Microsoft::WRL::ComPtr<IDXGIOutput6> temp;
		std::list<IDXGIOutput6*> tempList;

		while (adapter->EnumOutputs(i, &pOutput) != DXGI_ERROR_NOT_FOUND)
		{
			pOutput.As(&temp);
			tempList.push_back(temp.Get());
			++i;
		}
		outputList = &tempList;
	}
	void DeviceDX11::EnumerateDisplayModes(_In_ IDXGIOutput6* output, _Out_ std::list<DXGI_MODE_DESC1*>* displayModeList)
	{
		HRESULT hr;

		uint32 numModes = 0;
		DXGI_FORMAT format = DXGI_FORMAT_B8G8R8A8_UNORM;
		uint32 flags = DXGI_ENUM_MODES_INTERLACED;

		// Get the number of elements
		hr = output->GetDisplayModeList1(format, flags, &numModes, NULL);
		ThrowIfFailed(hr);
		DXGI_MODE_DESC1* displayModes = new DXGI_MODE_DESC1[numModes];

		hr = output->GetDisplayModeList1(format, flags, &numModes, displayModes);
		ThrowIfFailed(hr);

		for (uint32 i = 0; i <= numModes; i++)
		{
			DXGI_MODE_DESC1* temp = NULL;

			temp = &displayModes[i];
			displayModeList->push_back(temp);
		}
	}

	void DeviceDX11::setRenderTarget(_In_ ID3D11RenderTargetView* Target)
	{
		if (Target)
		{
			m_context->OMSetRenderTargets(1, &Target, m_depthStencilView.Get());
		}
	}

	void DeviceDX11::setPresentationParams(_In_ DXGI_PRESENT_PARAMETERS params)
	{
		m_presentParameters = params;
	}

	IDXGIFactory5*				DeviceDX11::getFactory()
	{
		return m_factory.Get();
	}
	ID3D11Device5*				DeviceDX11::getDevice()
	{
		return m_device.Get();
	}
	IDXGIDevice4*				DeviceDX11::getDXGIDevice()
	{
		return m_dxgiDevice.Get();
	}
	ID3D11DeviceContext4*		DeviceDX11::getContext()
	{
		return m_context.Get();
	}

	ID3D11RenderTargetView1*	DeviceDX11::getRenderTarget()
	{
		return m_renderTargetView.Get();
	}
	IDXGISurface2*				DeviceDX11::getSurface()
	{
		return m_dxgiBackBuffer.Get();
	}

	ID3D11DepthStencilState*	DeviceDX11::getDepthStencilState()
	{
		return m_depthStencilState.Get();
	}
	ID3D11RasterizerState2*		DeviceDX11::getRasterizerState()
	{
		return m_rasterizerState.Get();
	}
	D3D11_VIEWPORT				DeviceDX11::getViewPort()
	{
		return m_viewport;
	}

	D2D1::Matrix3x2F			DeviceDX11::get2DOrientation()
	{
		return m_orientationTransform2D;
	}
	DirectX::XMFLOAT4X4			DeviceDX11::get3DOrientation()
	{
		return m_orientationTransform3D;
	}

	DXGI_PRESENT_PARAMETERS DeviceDX11::getPresentationParams()
	{
		return m_presentParameters;
	}

	void DeviceDX11::CreateDevices()
	{
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

		Microsoft::WRL::ComPtr<ID3D11Device> device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;

		HRESULT hr;

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

		if (FAILED(hr))
		{
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
		}

		// Store pointers to the Direct3D 11.1 API device ,immediate context and DXGI device.
		hr = device.As(&m_device);
		ThrowIfFailed(hr);

		hr = context.As(&m_context);
		ThrowIfFailed(hr);

		hr = m_device.As(&m_dxgiDevice);
		ThrowIfFailed(hr);

#if defined(_DEBUG)
		hr = m_context.As(&m_userAnnotation);
		ThrowIfFailed(hr);
#endif
	}
	void DeviceDX11::CreateWindowSizeDependentResources()
	{
		HRESULT hr;

		// Clear the previous window size specific context.
		ID3D11RenderTargetView* nullViews[] = { nullptr };
		m_context->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);

		m_renderTargetView.Reset();
		m_depthStencilView.Reset();
		m_depthStencilBuffer.Reset();
		m_dxgiBackBuffer.Reset();

		m_context->Flush();
		m_context->ClearState();

		if (m_recreateSwapChain)
			m_swapChain.Reset();

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
			// If the swap chain already exists, resize it.
			hr = m_swapChain->ResizeBuffers(
				m_backBufferCount,
				static_cast<uint32>(m_d3dRenderTargetSize.Width),
				static_cast<uint32>(m_d3dRenderTargetSize.Height),
				DXGI_FORMAT_B8G8R8A8_UNORM,
				0
			);

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

			// SwapChain doesn´t need to recreated anymore
			m_recreateSwapChain = false;

			// This sequence obtains the DXGI factory that was used to create the Direct3D device above.
			Microsoft::WRL::ComPtr<IDXGIDevice4> dxgiDevice;
			hr = m_device.As(&dxgiDevice);
			ThrowIfFailed(hr);

			Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
			hr = dxgiDevice->GetAdapter(&dxgiAdapter);
			ThrowIfFailed(hr);

			Microsoft::WRL::ComPtr<IDXGIFactory5> dxgiFactory;
			hr = dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));
			ThrowIfFailed(hr);

			DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
			swapChainDesc.Width = static_cast<uint32>(m_d3dRenderTargetSize.Width); // Match the size of the window.
			swapChainDesc.Height = static_cast<uint32>(m_d3dRenderTargetSize.Height);
			swapChainDesc.Format = m_swapChainFormat;
			swapChainDesc.Stereo = m_stereo;
			swapChainDesc.SampleDesc.Count = m_sampleCount; // Don't use multi-sampling.
			swapChainDesc.SampleDesc.Quality = m_sampleQuality;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.BufferCount = m_backBufferCount;
			swapChainDesc.SwapEffect = m_stereo ? DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL : DXGI_SWAP_EFFECT_FLIP_DISCARD; // All Windows Store apps must use this SwapEffect. default: DXGI_SWAP_EFFECT_FLIP_DISCARD Stereo: DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL 
			swapChainDesc.Flags = 0;
			swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE; // When using XAML interop, this value cannot be DXGI_ALPHA_MODE_PREMULTIPLIED.
			swapChainDesc.Scaling = DXGI_SCALING_ASPECT_RATIO_STRETCH;

			auto window = m_window->getCoreWindow();

			Microsoft::WRL::ComPtr<IDXGISwapChain1> dxgiSwapChain;
			hr = dxgiFactory->CreateSwapChainForCoreWindow(
				m_device.Get(),
				reinterpret_cast<IUnknown*>(window),
				&swapChainDesc,
				nullptr,
				dxgiSwapChain.GetAddressOf()
			);
			ThrowIfFailed(hr);

			// Convert to IDXGISwapChain4
			hr = dxgiSwapChain.As(&m_swapChain);
			ThrowIfFailed(hr);

			// Ensure that DXGI does not queue more than one frame at a time. This both reduces latency and
			// ensures that the application will only render after each VSync, minimizing power consumption.
			hr = dxgiDevice->SetMaximumFrameLatency(1);
			ThrowIfFailed(hr);
		}

		// Set the proper orientation for the swap chain, and generate 2D and
		// 3D matrix transformations for rendering to the rotated swap chain.
		// Note the rotation angle for the 2D and 3D transforms are different.
		// This is due to the difference in coordinate spaces.  Additionally,
		// the 3D matrix is specified explicitly to avoid rounding errors.

		switch (displayRotation)
		{
		case DXGI_MODE_ROTATION_IDENTITY:
			m_orientationTransform2D = D2D1::Matrix3x2F::Identity();
			m_orientationTransform3D = ScreenRotation::Rotation0;
			break;

		case DXGI_MODE_ROTATION_ROTATE90:
			m_orientationTransform2D =
				D2D1::Matrix3x2F::Rotation(90.0f) *
				D2D1::Matrix3x2F::Translation(m_logicalSize.Height, 0.0f);
			m_orientationTransform3D = ScreenRotation::Rotation270;
			break;

		case DXGI_MODE_ROTATION_ROTATE180:
			m_orientationTransform2D =
				D2D1::Matrix3x2F::Rotation(180.0f) *
				D2D1::Matrix3x2F::Translation(m_logicalSize.Width, m_logicalSize.Height);
			m_orientationTransform3D = ScreenRotation::Rotation180;
			break;

		case DXGI_MODE_ROTATION_ROTATE270:
			m_orientationTransform2D =
				D2D1::Matrix3x2F::Rotation(270.0f) *
				D2D1::Matrix3x2F::Translation(0.0f, m_logicalSize.Width);
			m_orientationTransform3D = ScreenRotation::Rotation90;
			break;

		default:
			throw ref new Platform::FailureException();
		}

		// The Windows phone compositor behaves differently than the compositor on Windows and this API is not needed or supported.
		hr = m_swapChain->SetRotation(displayRotation);
		ThrowIfFailed(hr);

		// Create a render target view of the swap chain back buffer.
		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
		hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
		ThrowIfFailed(hr);

		CD3D11_RENDER_TARGET_VIEW_DESC1 renderTargetViewDesc(D3D11_RTV_DIMENSION_TEXTURE2D, DXGI_FORMAT_B8G8R8A8_UNORM);
		hr = m_device->CreateRenderTargetView1(backBuffer.Get(), &renderTargetViewDesc, m_renderTargetView.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);

		// Create a depth stencil view for use with 3D rendering if needed.
		CD3D11_TEXTURE2D_DESC1 depthStencilDesc(DXGI_FORMAT_D24_UNORM_S8_UINT, static_cast<uint32>(m_d3dRenderTargetSize.Width), static_cast<uint32>(m_d3dRenderTargetSize.Height), 1, 1, D3D11_BIND_DEPTH_STENCIL);

		hr = m_device->CreateTexture2D1(&depthStencilDesc, nullptr, &m_depthStencilBuffer);
		ThrowIfFailed(hr);

		CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
		hr = m_device->CreateDepthStencilView(m_depthStencilBuffer.Get(), &depthStencilViewDesc, &m_depthStencilView);
		ThrowIfFailed(hr);

		// Set Render Target View and depth Stencil View
		ID3D11RenderTargetView *const targets[1] = { m_renderTargetView.Get() };
		m_context->OMSetRenderTargets(ARRAYSIZE(targets), targets, m_depthStencilView.Get());

		// Set RasterizerState
		setWireframe(false);

		// Set the 3D rendering viewport to target the entire window.
		m_viewport = CD3D11_VIEWPORT(0.0f, 0.0f, m_d3dRenderTargetSize.Width, m_d3dRenderTargetSize.Height, 0.0f, 1.0f);

		m_context->RSSetViewports(1, &m_viewport);

		// Create DXGI Buffer for D2D1
		hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&m_dxgiBackBuffer));
		ThrowIfFailed(hr);
	}

	void DeviceDX11::RecreateSwapChain()
	{
		m_recreateSwapChain = true;

		CreateWindowSizeDependentResources();
	}

	DXGI_MODE_ROTATION DeviceDX11::ComputeDisplayRotation()
	{
		DXGI_MODE_ROTATION rotation = DXGI_MODE_ROTATION_UNSPECIFIED;

		// Note: NativeOrientation can only be Landscape or Portrait even though
		// the DisplayOrientations enum has other values.
		switch (m_nativeOrientation)
		{
		case Windows::Graphics::Display::DisplayOrientations::Landscape:
			switch (m_currentOrientation)
			{
			case Windows::Graphics::Display::DisplayOrientations::Landscape:
				rotation = DXGI_MODE_ROTATION_IDENTITY;
				break;

			case Windows::Graphics::Display::DisplayOrientations::Portrait:
				rotation = DXGI_MODE_ROTATION_ROTATE270;
				break;

			case Windows::Graphics::Display::DisplayOrientations::LandscapeFlipped:
				rotation = DXGI_MODE_ROTATION_ROTATE180;
				break;

			case Windows::Graphics::Display::DisplayOrientations::PortraitFlipped:
				rotation = DXGI_MODE_ROTATION_ROTATE90;
				break;
			}
			break;

		case Windows::Graphics::Display::DisplayOrientations::Portrait:
			switch (m_currentOrientation)
			{
			case Windows::Graphics::Display::DisplayOrientations::Landscape:
				rotation = DXGI_MODE_ROTATION_ROTATE90;
				break;

			case Windows::Graphics::Display::DisplayOrientations::Portrait:
				rotation = DXGI_MODE_ROTATION_IDENTITY;
				break;

			case Windows::Graphics::Display::DisplayOrientations::LandscapeFlipped:
				rotation = DXGI_MODE_ROTATION_ROTATE270;
				break;

			case Windows::Graphics::Display::DisplayOrientations::PortraitFlipped:
				rotation = DXGI_MODE_ROTATION_ROTATE180;
				break;
			}
			break;
		}
		return rotation;
	}

	DeviceDX11::~DeviceDX11()
	{
		SystemManager::Instance->RemoveDeviceDX11(this);
	}
}// namespace WOtech