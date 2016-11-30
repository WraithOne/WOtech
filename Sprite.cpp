////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: Sprite.cpp
///
///			Created:	07.05.2014
///			Edited:		27.11.2016
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "2DComponents.h"
#include "SpriteBatch.h"
#include "Utilities.h"

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI;
using namespace Windows::Storage;
using namespace Windows::ApplicationModel;
using namespace Microsoft::WRL;
using namespace WOtech::DXWrapper;

namespace WOtech
{
	Sprite::Sprite(_In_ Platform::String^ filename)
	{
		m_fileName = filename;

		// Set default attributes
		m_position = { 0.0f,0.0f };
		m_size = { 10.0f,10.0f };
		m_sourceRect = { 0.0f, 0.0f, 10.0f, 10.0f };
		m_rotation = 0.0f;
		m_opacity = 1.0f;
		m_interpolation = BITMAP_INTERPOLATION_MODE::BITMAP_INTERPOLATION_MODE_LINEAR;
		m_flipMode = SPRITE_FLIP_MODE::None;

		// todo: Content Manager
	}
	void Sprite::Load(_In_ SpriteBatch^ spriteBatch)
	{
		ComPtr<IWICBitmapDecoder> pDecoder;
		ComPtr<IWICBitmapFrameDecode> pSource;
		ComPtr<IWICStream> pStream;
		ComPtr<IWICFormatConverter> pConverter;
		ComPtr<IWICBitmapScaler> pScaler;
		ComPtr<IWICImagingFactory> pWICFactory;

		// Create path/filename string
		String^ path;
		String^ pathfilename;
		StorageFolder^ m_installedLocation = Package::Current->InstalledLocation;
		path = Platform::String::Concat(m_installedLocation->Path, "\\");
		pathfilename = Platform::String::Concat(path, m_fileName);

		HRESULT hr;

		// Create new instance of WICFactory
		hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pWICFactory));
		ThrowIfFailed(hr);

		// Create Decoder
		LPCWSTR Filename = pathfilename->Data();
		hr = pWICFactory->CreateDecoderFromFilename(Filename, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
		ThrowIfFailed(hr);

		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
		ThrowIfFailed(hr);

		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pWICFactory->CreateFormatConverter(&pConverter);
		ThrowIfFailed(hr);

		hr = pConverter->Initialize(pSource.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
		ThrowIfFailed(hr);

		// Clear the Bitmap befor use
		m_Bitmap = nullptr;

		// Create a Direct2D bitmap from the WIC bitmap.
		hr = spriteBatch->GetDeviceContext()->CreateBitmapFromWicBitmap(pConverter.Get(), NULL, &m_Bitmap);
		ThrowIfFailed(hr);

		// Set width/height of the source rect
		m_size.Width = m_sourceRect.X = m_Bitmap->GetSize().width;
		m_size.Height = m_sourceRect.Height = m_Bitmap->GetSize().height;
	}

	ID2D1Bitmap* Sprite::getBitmap()
	{
		return m_Bitmap.Get();
	}

	Sprite::~Sprite()
	{
		// todo: Content Manager
	}

	Rect Sprite::getSourceRect()
	{
		return m_sourceRect;
	}
	Rect Sprite::getDestinationRect()
	{
		return Rect(m_position.X, m_position.Y, m_position.X + m_size.Width, m_position.Y + m_size.Height);
	}
	Point Sprite::getPosition()
	{
		return m_position;
	}
	Size Sprite::getSize()
	{
		return m_size;
	}
	float32 Sprite::getOpacity()
	{
		return m_opacity;
	}
	float32 Sprite::getRotation()
	{
		return m_rotation;
	}
	SPRITE_FLIP_MODE Sprite::getFlipMode()
	{
		return m_flipMode;
	}
	BITMAP_INTERPOLATION_MODE Sprite::getInterpolation()
	{
		return m_interpolation;
	}

	void Sprite::setPosition(_In_ float32 x, _In_ float32 y)
	{
		m_position = Point(x, y);
	}
	void Sprite::setSize(float32 width, float32 height)
	{
		m_size = Size(width, height);
	}
	void Sprite::setSourceRect(_In_ float32 x, _In_ float32 y, _In_ float32 height, _In_ float32 width)
	{
		m_sourceRect = Rect(x, y, width, height);
	}
	void Sprite::setOpacity(_In_ float32 opacity)
	{
		m_opacity = opacity;
	}
	void Sprite::setRotation(_In_ float32 degree)
	{
		m_rotation = degree;
	}
	void Sprite::setRotationinRadian(_In_ float32 radian)
	{
		m_rotation = RadiantoDegree(radian);
	}

	void Sprite::setFlipMode(_In_ SPRITE_FLIP_MODE flipmode)
	{
		m_flipMode = flipmode;
	}

	void Sprite::setInterpolation(_In_ BITMAP_INTERPOLATION_MODE interpolation)
	{
		m_interpolation = interpolation;
	}
}//namespace WOtech