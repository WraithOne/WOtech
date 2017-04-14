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
///			Edited:		12.04.2017
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

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI;
using namespace Microsoft::WRL;
using namespace WOtech::DXWrapper;

namespace WOtech
{
	///////////////////////////////////////////////////////////////
	// SpriteBatch
	///////////////////////////////////////////////////////////////
	SpriteBatch::SpriteBatch(_In_ DeviceDX11^ renderer)
	{
		m_deviceDX11 = renderer;

		Initialize();

		// add to SystemManager
		SystemManager::Instance->AddSpriteBatch(this);
	}

	void SpriteBatch::Initialize()
	{
		if (m_deviceDX11 == nullptr)
		{
			ThrowIfFailed(E_FAIL);
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
			hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory3), &options, &m_factory);// D2D1_FACTORY_TYPE_SINGLE_THREADED
			ThrowIfFailed(hr);
		}

		// Create the DirectWriter Factory
		if (m_Wfactory == nullptr)
		{
			hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &m_Wfactory);
			ThrowIfFailed(hr);
		}

		// Create the D2D Divice
		if (m_device == nullptr)
		{
			hr = m_factory->CreateDevice(m_deviceDX11->getDXGIDevice(), m_device.ReleaseAndGetAddressOf());
			ThrowIfFailed(hr);
		}

		// Create the D2D DeviceContext
		if (m_deviceContext == nullptr)
		{
			hr = m_device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, m_deviceContext.ReleaseAndGetAddressOf());
			ThrowIfFailed(hr);
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
		ThrowIfFailed(hr);

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
		ThrowIfFailed(hr);

		// create Rectanglebrush
		hr = m_deviceContext->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f), m_rectangleBrush.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);

		// Create Outlinebrush
		hr = m_deviceContext->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), m_outlineBrush.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);

		// Create fontbrush
		hr = m_deviceContext->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), m_fontBrush.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);

		// Create Gridbrush
		CreateGrid();
	}
	void SpriteBatch::ReleaseRendertarget()
	{
		m_deviceContext->SetTarget(nullptr);
		m_targetBitmap = nullptr;
	}

	void SpriteBatch::BeginDraw()
	{
		m_sortMode = SpriteSortMode::Immediate;
		m_deviceContext->BeginDraw();
	}
	void SpriteBatch::BeginDraw(_In_ SpriteSortMode sortmode)
	{
		m_sortMode = sortmode;
		m_deviceContext->BeginDraw();
	}
	void SpriteBatch::EndDraw()
	{
		if (m_sortMode != SpriteSortMode::Immediate)
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

	void SpriteBatch::CreateGrid()
	{
		HRESULT hr;

		// Create a compatible render target.
		ComPtr<ID2D1BitmapRenderTarget> pCompatibleRenderTarget;
		hr = m_deviceContext->CreateCompatibleRenderTarget(D2D1::SizeF(10.0f, 10.0f), &pCompatibleRenderTarget);
		ThrowIfFailed(hr);

		if (SUCCEEDED(hr))
		{
			// Draw a pattern.
			ComPtr<ID2D1SolidColorBrush> pGridBrush;
			hr = pCompatibleRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(0.93f, 0.94f, 0.96f, 1.0f)), &pGridBrush);
			ThrowIfFailed(hr);

			if (SUCCEEDED(hr))
			{
				pCompatibleRenderTarget->BeginDraw();
				pCompatibleRenderTarget->FillRectangle(D2D1::RectF(0.0f, 0.0f, 10.0f, 1.0f), pGridBrush.Get());
				pCompatibleRenderTarget->FillRectangle(D2D1::RectF(0.0f, 0.1f, 1.0f, 10.0f), pGridBrush.Get());
				pCompatibleRenderTarget->EndDraw();

				// Retrieve the bitmap from the render target.
				ComPtr<ID2D1Bitmap> pGridBitmap;
				hr = pCompatibleRenderTarget->GetBitmap(pGridBitmap.ReleaseAndGetAddressOf());
				ThrowIfFailed(hr);

				if (SUCCEEDED(hr))
				{
					// Create the bitmap brush.
					hr = m_deviceContext->CreateBitmapBrush(pGridBitmap.Get(), D2D1::BitmapBrushProperties(D2D1_EXTEND_MODE_WRAP, D2D1_EXTEND_MODE_WRAP), &m_gridBrush);
					ThrowIfFailed(hr);
				}
			}
		}
	}

	void SpriteBatch::DrawText(_In_ Text^ text)
	{
		if (text)
		{
			auto rect = WOtech::DXWrapper::RECT{ text->getPosition().X, text->getPosition().Y, text->getlayoutbox().Width, text->getlayoutbox().Height };
			setRotation(rect, text->getRotation());
			m_deviceContext->DrawTextLayout(D2D1::Point2F(text->getPosition().X, text->getPosition().Y), text->getLayout(), text->getBrush());
		}
	}
	void SpriteBatch::DrawFont(_In_ Font^ font, _In_ float32 fontSize, _In_ WOtech::DXWrapper::RECT layoutbox, _In_ FONT_STYLE style, _In_ Color color, _In_ float32 rotation, _In_ String^ text)
	{
		HRESULT hr;

		// Set Color
		m_fontBrush->SetColor(wrapColor(color));

		// Create text format
		IDWriteTextFormat* temp = nullptr;
		hr = m_Wfactory->CreateTextFormat(font->getFontname()->Data(), font->getColletion(), DWRITE_FONT_WEIGHT_NORMAL, wraptFontStyle(style), DWRITE_FONT_STRETCH_NORMAL, fontSize, L"", &temp);
		ThrowIfFailed(hr);

		// Create the Destination Rect
		D2D1_RECT_F destRect = D2D1::RectF(layoutbox.X, layoutbox.Y, layoutbox.X + layoutbox.Width, layoutbox.Y + layoutbox.Height);

		// Set Rotation
		setRotation(layoutbox, rotation);

		// Draw the text
		m_deviceContext->DrawText(text->Data(), text->Length(), temp, destRect, m_fontBrush.Get()); // todo: Analyzer -> temp cannot be 0

		SafeRelease(&temp);
	}

	void SpriteBatch::DrawSprite(_In_ Sprite^ sprite)
	{
		// Create a Rect to hold Position and Size of the Sprite
		auto rect = WOtech::DXWrapper::RECT{ sprite->getDestinationRect().X, sprite->getDestinationRect().Y, sprite->getSourceRect().Width, sprite->getSourceRect().Height };

		// Set Rotation
		setRotation(rect, sprite->getRotation());

		auto spriteREct = sprite->getDestinationRect();
		D2D1_RECT_F destRect;
		//Flipmode
		switch (sprite->getFlipMode())
		{
		case WOtech::SPRITE_FLIP_MODE::None:
			destRect = wrapRect(sprite->getDestinationRect());
			break;
		case WOtech::SPRITE_FLIP_MODE::Horizontal:
			destRect = D2D1::RectF(spriteREct.X + (spriteREct.Width - spriteREct.X), spriteREct.Y, spriteREct.X, spriteREct.Height);
			break;
		case WOtech::SPRITE_FLIP_MODE::Vertical:
			destRect = D2D1::RectF(spriteREct.X, spriteREct.Height, spriteREct.Width, spriteREct.Y);
			break;
		case WOtech::SPRITE_FLIP_MODE::Both:
			destRect = wrapRect(sprite->getDestinationRect());
			break;
		default:
			break;
		}
		// Draw the Sprite
		m_deviceContext->DrawBitmap(sprite->getBitmap(), wrapRect(sprite->getDestinationRect()), sprite->getOpacity(), wrapBitmapInterpolationMode(sprite->getInterpolation()), wrapRect(sprite->getSourceRect()));
	}
	void SpriteBatch::DrawSprite(_In_ Sprite^ sprite, _In_ WOtech::DXWrapper::RECT srcRect, _In_ WOtech::DXWrapper::RECT destRect, _In_ float32 opacity, _In_ float32 rotation, _In_ SPRITE_FLIP_MODE flipmode)
	{
		auto rect = WOtech::DXWrapper::RECT{ destRect.X, destRect.Y, destRect.Width, destRect.Height };// - .x , -.y

		// Set Rotation
		setRotation(rect, rotation);

		//Flipmode
		D2D1_RECT_F temp;

		switch (flipmode)
		{
		case WOtech::SPRITE_FLIP_MODE::None:
			temp = wrapRect(destRect);
			break;
		case WOtech::SPRITE_FLIP_MODE::Horizontal:
			temp = D2D1::RectF(destRect.X + destRect.Width, destRect.Y, destRect.X, destRect.Height);
			break;
		case WOtech::SPRITE_FLIP_MODE::Vertical:
			temp = D2D1::RectF(destRect.X, destRect.Y + destRect.Height, destRect.X + destRect.Width, destRect.Y);
			break;
		case WOtech::SPRITE_FLIP_MODE::Both:
			temp = D2D1::RectF(destRect.X + destRect.Width, destRect.Y + destRect.Height, destRect.X, destRect.Y);
			break;
		default:
			break;
		}

		// Draw the Sprite
		m_deviceContext->DrawBitmap(sprite->getBitmap(), wrapRect(destRect), opacity, wrapBitmapInterpolationMode(sprite->getInterpolation()), wrapRect(srcRect));
	}
	void SpriteBatch::DrawAnimatedSprite(_In_ AnimatedSprite^ animatedsprite, _In_ String^ name)
	{
		// Create a Rect to hold Position and Size of the Sprite
		auto rect = WOtech::DXWrapper::RECT{ animatedsprite->getPosition().X, animatedsprite->getPosition().Y, animatedsprite->getFrameSize(name).Width, animatedsprite->getFrameSize(name).Height };

		// Create the Destination Rect
		D2D1_RECT_F destRect = D2D1::RectF(animatedsprite->getPosition().X, animatedsprite->getPosition().Y, animatedsprite->getPosition().X + animatedsprite->getFrameSize(name).Width, animatedsprite->getPosition().Y + animatedsprite->getFrameSize(name).Height);

		//Flipmode
		D2D1_RECT_F temp;
		auto source = animatedsprite->getFrame(name);
		switch (animatedsprite->getFlipMode())
		{
		case WOtech::SPRITE_FLIP_MODE::None:
			temp = wrapRect(source);
			break;
		case WOtech::SPRITE_FLIP_MODE::Horizontal:
			temp = D2D1::RectF(source.Width, source.Y, source.X + 15.0f, source.Height);
			break;
		case WOtech::SPRITE_FLIP_MODE::Vertical:
			temp = D2D1::RectF(source.X, source.Height, source.Width, source.Y);
			break;
		case WOtech::SPRITE_FLIP_MODE::Both:
			temp = D2D1::RectF(source.Width, source.Height, source.X, source.Y);
			break;
		default:
			break;
		}

		// Set Rotation
		setRotation(rect, animatedsprite->getRotation());

		// Draw the AnimatedSprite
		m_deviceContext->DrawBitmap(animatedsprite->getBitmap(), destRect, animatedsprite->getOpacity(), wrapBitmapInterpolationMode(animatedsprite->getInterpolation()), temp);//wrapRect(animatedsprite->getFrame(name))
	}

	void SpriteBatch::DrawGrid(_In_ WOtech::DXWrapper::RECT area, _In_ Color color, _In_ float32 rotation)
	{
		UNREFERENCED_PARAMETER(color);// todo
		UNREFERENCED_PARAMETER(rotation); // todo

		// Draw Grid
		m_deviceContext->FillRectangle(D2D1::RectF(area.X, area.Y, area.X + area.Width, area.Y + area.Height), m_gridBrush.Get());
	}
	void SpriteBatch::DrawCircle(_In_ CIRCLE circle)
	{
		// Set Transformation
		m_deviceContext->SetTransform(m_deviceDX11->get2DOrientation());

		// Set Outline Color
		m_outlineBrush->SetColor(wrapColor(circle.color));

		// Draw Circle
		m_deviceContext->DrawEllipse(D2D1::Ellipse(wrapPoint(circle.position), circle.radius, circle.radius), m_outlineBrush.Get(), circle.tickness);
	}
	void SpriteBatch::DrawCircleOutlined(_In_ CIRCLE_OUTLINED circleOutlined)
	{
		// Set Transformation
		m_deviceContext->SetTransform(m_deviceDX11->get2DOrientation());

		// Set Circle Color
		m_circleBrush->SetColor(wrapColor(circleOutlined.color));

		// Set Outline Color
		m_outlineBrush->SetColor(wrapColor(circleOutlined.outlinecolor));

		// Draw Circle
		m_deviceContext->FillEllipse(D2D1::Ellipse(wrapPoint(circleOutlined.position), circleOutlined.radius, circleOutlined.radius), m_circleBrush.Get());
		m_deviceContext->DrawEllipse(D2D1::Ellipse(wrapPoint(circleOutlined.position), circleOutlined.radius - circleOutlined.tickness / 2, circleOutlined.radius - circleOutlined.tickness / 2), m_outlineBrush.Get(), circleOutlined.tickness);
	}
	void SpriteBatch::DrawCircleFilled(_In_ CIRCLE_FILLED circleFilled)
	{
		// Set Transformation
		m_deviceContext->SetTransform(m_deviceDX11->get2DOrientation());

		// Set Circle Color
		m_circleBrush->SetColor(wrapColor(circleFilled.color));

		// Draw Circle
		m_deviceContext->FillEllipse(D2D1::Ellipse(wrapPoint(circleFilled.position), circleFilled.radius, circleFilled.radius), m_circleBrush.Get());
	}
	void SpriteBatch::DrawRectangle(_In_ RECTANGLE rectangle)
	{
		// Set Rotation
		setRotation(rectangle.area, rectangle.rotation);

		// Set outline Color
		m_outlineBrush->SetColor(wrapColor(rectangle.color));

		// Draw the Rectangle
		m_deviceContext->DrawRectangle(D2D1::RectF(rectangle.area.X, rectangle.area.Y, rectangle.area.X + rectangle.area.Width, rectangle.area.Y + rectangle.area.Height), m_outlineBrush.Get(), rectangle.tickness);
	}
	void SpriteBatch::DrawRectangleOutlined(_In_ RECTANGLE_OUTLINED rectangleOutlined)
	{
		// Set Rotation
		setRotation(rectangleOutlined.area, rectangleOutlined.rotation);

		// Set Rectangle Color
		m_rectangleBrush->SetColor(wrapColor(rectangleOutlined.color));

		// Set Outline Color
		m_outlineBrush->SetColor(wrapColor(rectangleOutlined.outlinecolor));

		// Draw the Rectangle
		m_deviceContext->FillRectangle(D2D1::RectF(rectangleOutlined.area.X, rectangleOutlined.area.Y, rectangleOutlined.area.X + rectangleOutlined.area.Width, rectangleOutlined.area.Y + rectangleOutlined.area.Height), m_rectangleBrush.Get());
		m_deviceContext->DrawRectangle(D2D1::RectF(rectangleOutlined.area.X + rectangleOutlined.tickness / 2, rectangleOutlined.area.Y + rectangleOutlined.tickness / 2, (rectangleOutlined.area.X + rectangleOutlined.area.Width) - rectangleOutlined.tickness / 2, (rectangleOutlined.area.Y + rectangleOutlined.area.Height) - rectangleOutlined.tickness / 2), m_outlineBrush.Get(), rectangleOutlined.tickness);
	}
	void SpriteBatch::DrawRectangleFilled(_In_ RECTANGLE_FILLED rectangleFilled)
	{
		// Set Rotation
		setRotation(rectangleFilled.area, rectangleFilled.rotation);

		// Set Rectangle Color
		m_rectangleBrush->SetColor(wrapColor(rectangleFilled.color));

		// Draw the Rectangle
		m_deviceContext->FillRectangle(D2D1::RectF(rectangleFilled.area.X, rectangleFilled.area.Y, rectangleFilled.area.X + rectangleFilled.area.Width, rectangleFilled.area.Y + rectangleFilled.area.Height), m_rectangleBrush.Get());
	}

	void SpriteBatch::DrawGeometry(_In_ Geometry^ geometry, _In_ FLOAT strokeWidth)
	{
		m_deviceContext->DrawGeometry(geometry->getGeometry(), geometry->getBrush(), strokeWidth);
	}

	ID2D1DeviceContext2* SpriteBatch::GetDeviceContext()
	{
		return m_deviceContext.Get();
	}

	ID2D1Factory3 * SpriteBatch::getFactory()
	{
		return m_factory.Get();
	}

	Size SpriteBatch::getLogicalSize()
	{
		return m_deviceDX11->getLogicalSize();
	}

	void SpriteBatch::setRotation(_In_ WOtech::DXWrapper::RECT area, _In_ float32 rotation)
	{
		float32 halfheight = area.Height / 2;
		float32 halfwidth = area.Width / 2;
		Windows::Foundation::Size logicalSize = m_deviceDX11->getLogicalSize();

		D2D1_POINT_2F  spriteCenter = D2D1::Point2F(logicalSize.Width - (area.X + halfwidth), logicalSize.Height - (area.Y + halfheight));

		D2D1_MATRIX_3X2_F rotationMatrix = D2D1::Matrix3x2F::Rotation(rotation, spriteCenter);

		m_deviceContext->SetTransform(rotationMatrix * m_deviceDX11->get2DOrientation());
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
		m_Wfactory.Reset();
		m_factory.Reset();
		m_deviceContext.Reset();
		m_device.Reset();
	}
}//namespace WOtech