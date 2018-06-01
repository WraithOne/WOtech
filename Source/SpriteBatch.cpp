////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: SpriteBatch.cpp
///
///			Description:
///
///			Created:	07.05.2014
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "SpriteBatch.h"
#include "DeviceDX11.h"
#include "SystemManager.h"
#include "Utilities.h"

namespace WOtech
{
	///////////////////////////////////////////////////////////////
	// SpriteBatch
	///////////////////////////////////////////////////////////////
	SpriteBatch::SpriteBatch(_In_ WOtech::DeviceDX11^ renderer)
	{
		m_deviceDX11 = renderer;
		m_beginDraw = false;

		// add to SystemManager
		SystemManager::Instance->AddSpriteBatch(this);
	}

	void SpriteBatch::Initialize()
	{
		if (m_deviceDX11 == nullptr)
		{
			WOtech::ThrowIfFailed(E_FAIL);
		}

		HRESULT hr;

		// Initialize Direct2D resources.
		D2D1_FACTORY_OPTIONS options;
		ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

#if defined(_DEBUG)
		// If the project is in a debug build, enable Direct2D debugging via SDK Layers.
		options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

		// Create the Factory
		if (m_factory == nullptr)
		{
			hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory6), &options, &m_factory);// D2D1_FACTORY_TYPE_SINGLE_THREADED
			WOtech::ThrowIfFailed(hr);
		}

		// Create the DirectWriter Factory
		if (m_dwFactory == nullptr)
		{
			hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory5), &m_dwFactory);
			WOtech::ThrowIfFailed(hr);
		}

		// Create an instance of WICFactory
		if (m_wicFactory == nullptr)
		{
			hr = CoCreateInstance(CLSID_WICImagingFactory1, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)(&m_wicFactory));
			WOtech::ThrowIfFailed(hr);
		}
		
		// Create the D2D Device
		if (m_device == nullptr)
		{
			hr = m_factory->CreateDevice(m_deviceDX11->getDXGIDevice(), m_device.ReleaseAndGetAddressOf());
			WOtech::ThrowIfFailed(hr);
		}

		// Create the D2D DeviceContext
		if (m_deviceContext == nullptr)
		{
			hr = m_device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, m_deviceContext.ReleaseAndGetAddressOf());
			WOtech::ThrowIfFailed(hr);
		}

		m_deviceContext->SetTarget(nullptr);
		m_targetBitmap = nullptr;

		// Create a Direct2D target bitmap associated with the
		// swap chain back buffer and set it as the current target.
		D2D1_BITMAP_PROPERTIES1 bitmapProperties =
			D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
				D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
				m_deviceDX11->getDPI(),
				m_deviceDX11->getDPI());

		hr = m_deviceContext->CreateBitmapFromDxgiSurface(m_deviceDX11->getSurface(), &bitmapProperties, m_targetBitmap.ReleaseAndGetAddressOf());
		WOtech::ThrowIfFailed(hr);

		// Set target to bitmap
		m_deviceContext->SetTarget(m_targetBitmap.Get());

		// Grayscale text anti-aliasing is recommended for all Windows Store apps.
		m_deviceContext->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);

		// Set DPI
		m_deviceContext->SetDpi(m_deviceDX11->getDPI(), m_deviceDX11->getDPI());

		// Set Transformation
		m_deviceContext->SetTransform(m_deviceDX11->get2DOrientation());

		// Create Circlebrush
		hr = m_deviceContext->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f), m_circleBrush.ReleaseAndGetAddressOf());
		WOtech::ThrowIfFailed(hr);

		// create Rectanglebrush
		hr = m_deviceContext->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f), m_rectangleBrush.ReleaseAndGetAddressOf());
		WOtech::ThrowIfFailed(hr);

		// Create Outlinebrush
		hr = m_deviceContext->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), m_outlineBrush.ReleaseAndGetAddressOf());
		WOtech::ThrowIfFailed(hr);

		// Create fontbrush
		hr = m_deviceContext->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), m_fontBrush.ReleaseAndGetAddressOf());
		WOtech::ThrowIfFailed(hr);

		// Create Gridbrush
		CreateGrid(Windows::UI::Colors::White);

		m_installedLocation = Windows::ApplicationModel::Package::Current->InstalledLocation;
	}
	void SpriteBatch::ReleaseRendertarget()
	{
		m_deviceContext->SetTarget(nullptr);
		m_targetBitmap = nullptr;
	}

	WOtech::Bitmap^ SpriteBatch::LoadBitmap(_In_ Platform::String^ fileName)
	{
		HRESULT hr;

		Microsoft::WRL::ComPtr<ID2D1Bitmap1> output;
		Microsoft::WRL::ComPtr<IWICBitmapDecoder> pDecoder;
		Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> pSource;
		Microsoft::WRL::ComPtr<IWICFormatConverter> pConverter;
		
		// Create Path/Filename String
		Platform::String^ path;
		Platform::String^ pathfilename;

		path = Platform::String::Concat(m_installedLocation->Path, "\\");
		pathfilename = Platform::String::Concat(path, fileName);
		LPCWSTR Filename = pathfilename->Data();

		hr = m_wicFactory->CreateDecoderFromFilename(Filename, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
		WOtech::ThrowIfFailed(hr);

		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
		WOtech::ThrowIfFailed(hr);

		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = m_wicFactory->CreateFormatConverter(&pConverter);
		WOtech::ThrowIfFailed(hr);

		hr = pConverter->Initialize(pSource.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
		WOtech::ThrowIfFailed(hr);

		// Create a Direct2D bitmap from the WIC bitmap.
		hr = m_deviceContext->CreateBitmapFromWicBitmap(pConverter.Get(), NULL, output.ReleaseAndGetAddressOf());
		WOtech::ThrowIfFailed(hr);

		return ref new WOtech::Bitmap(output.Get());
	}

	void SpriteBatch::BeginDraw()
	{
		BeginDraw(WOtech::SpriteSortMode::Immediate);
	}
	void SpriteBatch::BeginDraw(_In_ WOtech::SpriteSortMode sortmode)
	{
		if (m_beginDraw)
		{
			throw Platform::Exception::CreateException(E_FAIL, "BeginDraw was called before EndDraw");
		}
		m_sortMode = sortmode;
		m_beginDraw = true;

		m_deviceContext->BeginDraw();
	}
	void SpriteBatch::EndDraw()
	{
		if (!m_beginDraw)
		{
			throw Platform::Exception::CreateException(E_FAIL, "EndDraw was called before BeginDraw");
		}

		m_beginDraw = false;

		if (m_sortMode != WOtech::SpriteSortMode::Immediate)
		{
			SortBatch();

			DrawBatch();
		}
		HRESULT hr;

		hr = m_deviceContext->EndDraw();
		ThrowIfFailed(hr);
	}

	SpriteBatch::~SpriteBatch()
	{
		SystemManager::Instance->RemoveSpriteBatch(this);
	}

	void SpriteBatch::CreateGrid(_In_ Windows::UI::Color color)
	{
		HRESULT hr;

		// Create a compatible render target.
		Microsoft::WRL::ComPtr<ID2D1BitmapRenderTarget> pCompatibleRenderTarget;
		hr = m_deviceContext->CreateCompatibleRenderTarget(D2D1::SizeF(10.0f, 10.0f), &pCompatibleRenderTarget);
		WOtech::ThrowIfFailed(hr);

		if (SUCCEEDED(hr))
		{
			// Draw a pattern.
			Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pGridBrush;
			hr = pCompatibleRenderTarget->CreateSolidColorBrush(WOtech::DXWrapper::wrapColorD2D(color), &pGridBrush);//D2D1::ColorF(D2D1::ColorF(0.93f, 0.94f, 0.96f, 1.0f))
			WOtech::ThrowIfFailed(hr);

			if (SUCCEEDED(hr))
			{
				pCompatibleRenderTarget->BeginDraw();
				pCompatibleRenderTarget->FillRectangle(D2D1::RectF(0.0f, 0.0f, 10.0f, 1.0f), pGridBrush.Get());
				pCompatibleRenderTarget->FillRectangle(D2D1::RectF(0.0f, 0.1f, 1.0f, 10.0f), pGridBrush.Get());
				pCompatibleRenderTarget->EndDraw();

				// Retrieve the bitmap from the render target.
				Microsoft::WRL::ComPtr<ID2D1Bitmap> pGridBitmap;
				hr = pCompatibleRenderTarget->GetBitmap(pGridBitmap.ReleaseAndGetAddressOf());
				WOtech::ThrowIfFailed(hr);

				if (SUCCEEDED(hr))
				{
					// Create the bitmap brush.
					hr = m_deviceContext->CreateBitmapBrush(pGridBitmap.Get(), &m_gridBrush);
					WOtech::ThrowIfFailed(hr);
				}
			}
		}

		m_gridColor = color;
	}

	void SpriteBatch::DrawTextBlock(_In_ WOtech::TextBlock^ text)
	{
		if (text)
		{
			auto rect = Windows::Foundation::Rect{ text->getPosition().X, text->getPosition().Y, text->getlayoutbox().Width, text->getlayoutbox().Height };
			setRotation(rect, text->getRotation());
			m_deviceContext->DrawTextLayout(D2D1::Point2F(text->getPosition().X, text->getPosition().Y), text->getLayout(), text->getBrush());
		}
	}
	void SpriteBatch::DrawString(_In_ WOtech::Font^ font, _In_ float32 fontSize, _In_ Windows::Foundation::Rect layoutbox, _In_ WOtech::FONT_STYLE style, _In_ Windows::UI::Color color, _In_ float32 rotation, _In_ Platform::String^ text)
	{
		HRESULT hr;

		// Set Color
		m_fontBrush->SetColor(WOtech::DXWrapper::wrapColorD2D(color));

		// Create text format
		IDWriteTextFormat* temp = nullptr;
		hr = m_dwFactory->CreateTextFormat(font->getFontname()->Data(), font->getColletion(), DWRITE_FONT_WEIGHT_NORMAL, WOtech::DXWrapper::wraptFontStyle(style), DWRITE_FONT_STRETCH_NORMAL, fontSize, L"", &temp);
		WOtech::ThrowIfFailed(hr);

		// Create the Destination Rect
		D2D1_RECT_F destRect = D2D1::RectF(layoutbox.X, layoutbox.Y, layoutbox.X + layoutbox.Width, layoutbox.Y + layoutbox.Height);

		// Set Rotation
		setRotation(layoutbox, rotation);

		// Draw the text
		m_deviceContext->DrawText(text->Data(), text->Length(), temp, destRect, m_fontBrush.Get()); // todo: Analyzer -> temp cannot be 0

		SafeRelease(&temp);
	}

	void SpriteBatch::DrawBitmap(_In_ WOtech::Bitmap^ bitmap)
	{
		m_deviceContext->DrawBitmap(bitmap->getBitmap());
	}
	void SpriteBatch::DrawBitmap(_In_ WOtech::Bitmap^ bitmap, _In_  Windows::Foundation::Rect srcRect, _In_ Windows::Foundation::Rect destRect, _In_ float32 opacity, _In_ float32 rotation)
	{
		// Create a Rect to hold Position and Size of the Bitmap
		auto rect = Windows::Foundation::Rect{ destRect.X, destRect.Y, srcRect.Width, srcRect.Height };

		// Set Rotation
		setRotation(rect, rotation);
		m_deviceContext->DrawBitmap(bitmap->getBitmap(), WOtech::DXWrapper::wrapRect(destRect), opacity, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, WOtech::DXWrapper::wrapRect(srcRect));//wrapBitmapInterpolationMode(sprite->getInterpolation())
	}

	void SpriteBatch::DrawSprite(_In_ WOtech::Sprite^ sprite)
	{
		// Create a Rect to hold Position and Size of the Sprite
		auto rect = Windows::Foundation::Rect{ sprite->getDestinationRect().X, sprite->getDestinationRect().Y, sprite->getSourceRect().Width, sprite->getSourceRect().Height };

		// Set Rotation
		setRotation(rect, sprite->getRotation());

		auto spriteREct = sprite->getDestinationRect();
		
		// Set Transform
		setTransformation(sprite->getFlipMode());

		// Draw the Sprite
		m_deviceContext->DrawBitmap(sprite->getBitmap(), WOtech::DXWrapper::wrapRect(sprite->getDestinationRect()), sprite->getOpacity(), WOtech::DXWrapper::wrapBitmapInterpolationMode(sprite->getInterpolation()), WOtech::DXWrapper::wrapRect(sprite->getSourceRect()));
	}
	void SpriteBatch::DrawSprite(_In_ WOtech::Sprite^ sprite, _In_ Windows::Foundation::Rect srcRect, _In_ Windows::Foundation::Rect destRect, _In_ float32 opacity, _In_ float32 rotation, _In_ WOtech::SPRITE_FLIP_MODE flipmode)
	{
		auto rect = Windows::Foundation::Rect{ destRect.X, destRect.Y, destRect.Width, destRect.Height };// - .x , -.y

		// Set Rotation
		setRotation(rect, rotation);

		// Set Transform
		setTransformation(flipmode);

		// Draw the Sprite
		m_deviceContext->DrawBitmap(sprite->getBitmap(), WOtech::DXWrapper::wrapRect(destRect), opacity, WOtech::DXWrapper::wrapBitmapInterpolationMode(sprite->getInterpolation()), WOtech::DXWrapper::wrapRect(srcRect));
	}

	void SpriteBatch::DrawAnimatedSprite(_In_ WOtech::AnimatedSprite^ animatedsprite, _In_ Platform::String^ name)
	{
		// Create a Rect to hold Position and Size of the Sprite
		auto rect = Windows::Foundation::Rect{ animatedsprite->getPosition().X, animatedsprite->getPosition().Y, animatedsprite->getFrameSize(name).Width, animatedsprite->getFrameSize(name).Height };

		// Set Rotation
		setRotation(rect, animatedsprite->getRotation());

		// Create the Destination Rect
		D2D1_RECT_F destRect = D2D1::RectF(animatedsprite->getPosition().X, animatedsprite->getPosition().Y, (animatedsprite->getPosition().X + animatedsprite->getFrameSize(name).Width) * animatedsprite->getScale(), (animatedsprite->getPosition().Y + animatedsprite->getFrameSize(name).Height) *  animatedsprite->getScale());

		// Draw the AnimatedSprite
		m_deviceContext->DrawBitmap(animatedsprite->getBitmap(), destRect, animatedsprite->getOpacity(), WOtech::DXWrapper::wrapBitmapInterpolationMode(animatedsprite->getInterpolation()), WOtech::DXWrapper::wrapRect(animatedsprite->getFrame(name)));
	}

	void SpriteBatch::DrawGrid(_In_ Windows::Foundation::Rect area, _In_ Windows::UI::Color color, _In_ float32 rotation)
	{
		// Recolor grid
		if (m_gridColor.ToString() != color.ToString())// Todo : haxx
			CreateGrid(color);

		// Set Rotation
		setRotation({area.X, area.Y, area.X + area.Width, area.Y + area.Height}, rotation);

		// Draw Grid
		m_deviceContext->FillRectangle(D2D1::RectF(area.X, area.Y, area.X + area.Width, area.Y + area.Height), m_gridBrush.Get());
	}
	void SpriteBatch::DrawCircle(_In_ WOtech::CIRCLE circle)
	{
		// Set Transformation
		m_deviceContext->SetTransform(m_deviceDX11->get2DOrientation());

		// Set Outline Color
		m_outlineBrush->SetColor(WOtech::DXWrapper::wrapColorD2D(circle.color));

		// Draw Circle
		m_deviceContext->DrawEllipse(D2D1::Ellipse(WOtech::DXWrapper::wrapPoint(circle.position), circle.radius, circle.radius), m_outlineBrush.Get(), circle.tickness);
	}
	void SpriteBatch::DrawCircleOutlined(_In_ WOtech::CIRCLE_OUTLINED circleOutlined)
	{
		// Set Transformation
		m_deviceContext->SetTransform(m_deviceDX11->get2DOrientation());

		// Set Circle Color
		m_circleBrush->SetColor(WOtech::DXWrapper::wrapColorD2D(circleOutlined.color));

		// Set Outline Color
		m_outlineBrush->SetColor(WOtech::DXWrapper::wrapColorD2D(circleOutlined.outlinecolor));

		// Draw Circle
		m_deviceContext->FillEllipse(D2D1::Ellipse(WOtech::DXWrapper::wrapPoint(circleOutlined.position), circleOutlined.radius, circleOutlined.radius), m_circleBrush.Get());
		m_deviceContext->DrawEllipse(D2D1::Ellipse(WOtech::DXWrapper::wrapPoint(circleOutlined.position), circleOutlined.radius - circleOutlined.tickness / 2, circleOutlined.radius - circleOutlined.tickness / 2), m_outlineBrush.Get(), circleOutlined.tickness);
	}
	void SpriteBatch::DrawCircleFilled(_In_ WOtech::CIRCLE_FILLED circleFilled)
	{
		// Set Transformation
		m_deviceContext->SetTransform(m_deviceDX11->get2DOrientation());

		// Set Circle Color
		m_circleBrush->SetColor(WOtech::DXWrapper::wrapColorD2D(circleFilled.color));

		// Draw Circle
		m_deviceContext->FillEllipse(D2D1::Ellipse(WOtech::DXWrapper::wrapPoint(circleFilled.position), circleFilled.radius, circleFilled.radius), m_circleBrush.Get());
	}

	void SpriteBatch::DrawRectangle(_In_ WOtech::RECTANGLE rectangle)
	{
		// Set Rotation
		setRotation(rectangle.area, rectangle.rotation);

		// Set outline Color
		m_outlineBrush->SetColor(WOtech::DXWrapper::wrapColorD2D(rectangle.color));

		// Draw the Rectangle
		m_deviceContext->DrawRectangle(D2D1::RectF(rectangle.area.X, rectangle.area.Y, rectangle.area.X + rectangle.area.Width, rectangle.area.Y + rectangle.area.Height), m_outlineBrush.Get(), rectangle.tickness);
	}
	void SpriteBatch::DrawRectangleOutlined(_In_ WOtech::RECTANGLE_OUTLINED rectangleOutlined)
	{
		// Set Rotation
		setRotation(rectangleOutlined.area, rectangleOutlined.rotation);

		// Set Rectangle Color
		m_rectangleBrush->SetColor(WOtech::DXWrapper::wrapColorD2D(rectangleOutlined.color));

		// Set Outline Color
		m_outlineBrush->SetColor(WOtech::DXWrapper::wrapColorD2D(rectangleOutlined.outlinecolor));

		// Draw the Rectangle
		m_deviceContext->FillRectangle(D2D1::RectF(rectangleOutlined.area.X, rectangleOutlined.area.Y, rectangleOutlined.area.X + rectangleOutlined.area.Width, rectangleOutlined.area.Y + rectangleOutlined.area.Height), m_rectangleBrush.Get());
		m_deviceContext->DrawRectangle(D2D1::RectF(rectangleOutlined.area.X + rectangleOutlined.tickness / 2, rectangleOutlined.area.Y + rectangleOutlined.tickness / 2, (rectangleOutlined.area.X + rectangleOutlined.area.Width) - rectangleOutlined.tickness / 2, (rectangleOutlined.area.Y + rectangleOutlined.area.Height) - rectangleOutlined.tickness / 2), m_outlineBrush.Get(), rectangleOutlined.tickness);
	}
	void SpriteBatch::DrawRectangleFilled(_In_ WOtech::RECTANGLE_FILLED rectangleFilled)
	{
		// Set Rotation
		setRotation(rectangleFilled.area, rectangleFilled.rotation);

		// Set Rectangle Color
		m_rectangleBrush->SetColor(WOtech::DXWrapper::wrapColorD2D(rectangleFilled.color));

		// Draw the Rectangle
		m_deviceContext->FillRectangle(D2D1::RectF(rectangleFilled.area.X, rectangleFilled.area.Y, rectangleFilled.area.X + rectangleFilled.area.Width, rectangleFilled.area.Y + rectangleFilled.area.Height), m_rectangleBrush.Get());
	}

	void SpriteBatch::DrawGeometry(_In_ WOtech::Geometry^ geometry, _In_ FLOAT strokeWidth)
	{
		m_deviceContext->DrawGeometry(geometry->getGeometry(), geometry->getBrush(), strokeWidth);
	}

	ID2D1DeviceContext5* SpriteBatch::GetDeviceContext()
	{
		return m_deviceContext.Get();
	}

	ID2D1Factory6* SpriteBatch::getFactory()
	{
		return m_factory.Get();
	}

	WOtech::Image^ SpriteBatch::getRenderTarget()
	{
		ID2D1Image* rendertarget = nullptr;

		m_deviceContext->GetTarget(&rendertarget);

		return ref new WOtech::Image(rendertarget);
	}

	Windows::Foundation::Size SpriteBatch::getLogicalSize()
	{
		return m_deviceDX11->getLogicalSize();
	}

	Windows::Foundation::Rect SpriteBatch::getRenderRect()
	{
		auto size = m_deviceContext->GetSize();
		
		return { 0.0f, 0.0f, size.width, size.height };
	}

	void SpriteBatch::setRenderTarget(_In_ WOtech::Image^ rendertarget)
	{
		m_deviceContext->SetTarget(rendertarget->getImage());
	}
	void SpriteBatch::setRenderTarget(_In_ WOtech::Bitmap^ rendertarget)
	{
		m_deviceContext->SetTarget(rendertarget->getBitmap());
	}

	void SpriteBatch::setRotation(_In_ Windows::Foundation::Rect area, _In_ float32 rotation)
	{
		float32 halfheight = area.Height / 2;
		float32 halfwidth = area.Width / 2;
		Windows::Foundation::Size logicalSize = m_deviceDX11->getLogicalSize();

		D2D1_POINT_2F  spriteCenter = D2D1::Point2F(logicalSize.Width - (area.X + halfwidth), logicalSize.Height - (area.Y + halfheight));

		D2D1_MATRIX_3X2_F rotationMatrix = D2D1::Matrix3x2F::Rotation(rotation, spriteCenter);

		m_deviceContext->SetTransform(rotationMatrix * m_deviceDX11->get2DOrientation());
	}
	void SpriteBatch::setTransformation(WOtech::SPRITE_FLIP_MODE flipMode)
	{
		D2D1_MATRIX_3X2_F transformMatrix = D2D1::IdentityMatrix();

		switch (flipMode)
		{
		case WOtech::SPRITE_FLIP_MODE::None:
			
			break;
		case WOtech::SPRITE_FLIP_MODE::Horizontal:
			
			break;
		case WOtech::SPRITE_FLIP_MODE::Vertical:
			
			break;
		case WOtech::SPRITE_FLIP_MODE::Both:
			
			break;
		default:
			break;
		}

		m_deviceContext->SetTransform(transformMatrix * m_deviceDX11->get2DOrientation());
	}

	void SpriteBatch::SortBatch()
	{
		switch (m_sortMode)
		{
		case WOtech::SpriteSortMode::Immediate:
			return;// do nothing because everything is allready drawn
			break;
		case WOtech::SpriteSortMode::Deferred:
			break;
		case WOtech::SpriteSortMode::Texture:
			break;
		case WOtech::SpriteSortMode::BacktoFront:
			break;
		case WOtech::SpriteSortMode::FronttoBack:
			break;
		default:
			return;// this should never happen -.-
			break;
		}
	}
	void SpriteBatch::DrawBatch()
	{
		return; // todo: draw
	}
	void SpriteBatch::Release()
	{
		m_dwFactory.Reset();
		m_factory.Reset();
		m_deviceContext.Reset();
		m_device.Reset();
	}
}//namespace WOtech