////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Bitmap.cpp
///
///			Description:
///
///			Created:	20.10.2017
///			Edited:		22.10.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include <2DComponents.h>
#include <SpriteBatch.h>

namespace WOtech
{
	Bitmap::Bitmap()
	{
		m_bitmap = nullptr;
	}
	Bitmap::Bitmap(_In_ WOtech::SpriteBatch^ spriteBatch, _In_ UINT width, _In_ UINT height)
	{
		auto size = D2D1::SizeU(width, height);
		auto properties = D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));

		spriteBatch->GetDeviceContext()->CreateBitmap(size, nullptr, 0, &properties, m_bitmap.ReleaseAndGetAddressOf());
	}

	Windows::Foundation::Size Bitmap::getSize()
	{
		auto size = m_bitmap->GetSize();

		return Windows::Foundation::Size(size.width, size.height);
	}

	WOtech::RECT Bitmap::getSourceRECT()
	{
		auto size = m_bitmap->GetSize();
		return WOtech::RECT{ 0.0f, 0.0f, size.width, size.height };
	}

	Bitmap::Bitmap(_In_ ID2D1Bitmap1* bitmap)
	{
		m_bitmap = bitmap;
	}

	void Bitmap::setBitmap(_In_ ID2D1Bitmap1* bitmap)
	{
		m_bitmap = bitmap;
	}
	ID2D1Bitmap1* Bitmap::getBitmap()
	{
		return m_bitmap.Get();
	}
}