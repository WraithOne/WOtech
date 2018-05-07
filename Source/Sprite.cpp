////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Sprite.cpp
///
///			Description:
///
///			Created:	07.05.2014
///			Edited:		07.03.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "2DComponents.h"
#include "SpriteBatch.h"
#include "Utilities.h"
#include "ContentManager.h"
#include "DXWrapper.h"

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
		m_size = { 0.0f,0.0f };
		m_sourceRect = { 0.0f, 0.0f, 0.0f, 0.0f };
		m_rotation = 0.0f;
		m_opacity = 1.0f;
		m_interpolation = BITMAP_INTERPOLATION_MODE::BITMAP_INTERPOLATION_MODE_LINEAR;
		m_flipMode = SPRITE_FLIP_MODE::None;

		WOtech::ContentManager::Instance->AddSprite(this);
	}
	void Sprite::Load(_In_ SpriteBatch^ spriteBatch)
	{
		m_bitmap = (spriteBatch->LoadBitmap(m_fileName))->getBitmap();

		// Set width/height of the source rect
		m_size.Width = m_sourceRect.Width = m_bitmap->GetSize().width;
		m_size.Height = m_sourceRect.Height = m_bitmap->GetSize().height;
	}

	void Sprite::UnLoad()
	{
		m_bitmap.Reset();
	}

	ID2D1Bitmap1* Sprite::getBitmap()
	{
		return m_bitmap.Get();
	}

	Sprite::~Sprite()
	{
		WOtech::ContentManager::Instance->RemoveSprite(this);
	}

	WOtech::RECT Sprite::getSourceRect()
	{
		return m_sourceRect;
	}
	WOtech::RECT Sprite::getDestinationRect()
	{
		return WOtech::RECT{ m_position.X, m_position.Y, m_position.X + m_size.Width, m_position.Y + m_size.Height };
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
	void Sprite::setSize(_In_ float32 width, _In_ float32 height)
	{
		m_size = Size(width, height);
	}
	void Sprite::setSourceRect(_In_ float32 x, _In_ float32 y, _In_ float32 height, _In_ float32 width)
	{
		m_sourceRect = WOtech::RECT{ x, y, width, height };
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