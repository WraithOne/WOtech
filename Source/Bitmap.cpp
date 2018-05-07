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
///			Edited:		07.05.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Include\Utilities.h"
#include <ContentManager.h>
#include <2DComponents.h>
#include <SpriteBatch.h>

using namespace Microsoft::WRL;
using namespace Windows::Storage;
using namespace Windows::ApplicationModel;
using namespace Platform;

namespace WOtech
{
	Bitmap::Bitmap()
	{
		m_bitmap = nullptr;

		WOtech::ContentManager::Instance->AddBitmap(this);
	}

	Bitmap::Bitmap(_In_ WOtech::SpriteBatch^ spriteBatch, _In_ UINT width, _In_ UINT height)
	{
		auto size = D2D1::SizeU(width, height);
		auto properties = D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));

		spriteBatch->GetDeviceContext()->CreateBitmap(size, nullptr, 0, &properties, m_bitmap.ReleaseAndGetAddressOf());

		WOtech::ContentManager::Instance->AddBitmap(this);
	}

	Bitmap::Bitmap(_In_ WOtech::SpriteBatch^ spriteBatch, _In_  Platform::String^ fileName)
	{
		m_bitmap = (spriteBatch->LoadBitmap(fileName))->getBitmap();

		WOtech::ContentManager::Instance->AddBitmap(this);
	}

	void Bitmap::Reset()
	{
		m_bitmap.Reset();
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
		WOtech::ContentManager::Instance->AddBitmap(this);
	}

	void Bitmap::setBitmap(_In_ ID2D1Bitmap1* bitmap)
	{
		m_bitmap = bitmap;
	}
	ID2D1Bitmap1* Bitmap::getBitmap()
	{
		return m_bitmap.Get();
	}
	Bitmap::~Bitmap()
	{
		WOtech::ContentManager::Instance->RemoveBitmap(this);
	}
}