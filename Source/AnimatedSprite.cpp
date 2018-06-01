////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: AnimatedSprite.cpp
///
///			Description:
///
///			Created:	13.09.2014
///			Edited:		01.06.2018
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
#include <DXWrapper.h>

namespace WOtech
{
	AnimatedSprite::AnimatedSprite(_In_ Platform::String^ filename)
	{
		m_fromFile = true;
		m_fileName = filename;
		m_position = Windows::Foundation::Point(0.0f, 0.0f);
		m_scale = 1.0f;
		m_rotation = 0.0f;
		m_opacity = 1.0f;
		m_interpolation = BITMAP_INTERPOLATION_MODE::BITMAP_INTERPOLATION_MODE_LINEAR;
		m_flipMode = SPRITE_FLIP_MODE::None;

		WOtech::ContentManager::Instance->AddAnimatedSprite(this);
	}

	AnimatedSprite::AnimatedSprite(_In_ WOtech::Bitmap^ bitmap)
	{
		m_fromFile = true;
		m_fileName = "Error not loaded from File";
		m_position = Windows::Foundation::Point(0.0f, 0.0f);
		m_scale = 1.0f;
		m_rotation = 0.0f;
		m_opacity = 1.0f;
		m_interpolation = BITMAP_INTERPOLATION_MODE::BITMAP_INTERPOLATION_MODE_LINEAR;
		m_flipMode = SPRITE_FLIP_MODE::None;

		m_bitmap = bitmap->getBitmap();

		WOtech::ContentManager::Instance->AddAnimatedSprite(this);
	}

	void AnimatedSprite::Load(_In_ WOtech::SpriteBatch^ spriteBatch)
	{
		if (m_fromFile)
		{
			m_bitmap = (spriteBatch->LoadBitmap(m_fileName))->getBitmap();
		}
	}
	void AnimatedSprite::UnLoad()
	{
		m_bitmap.Reset();
	}
	Platform::Boolean AnimatedSprite::AddAnimation(_In_ Platform::String^ name, _In_ uint32 framecount, _In_ float32 frametime, _In_ Windows::Foundation::Size framesize, _In_ Windows::Foundation::Point sourceposition)
	{
		std::list<ANIMATION>::iterator iterator;

		for (iterator = m_animationList.begin(); iterator != m_animationList.end(); ++iterator)
		{
			if (iterator->Name == name)
			{
				//g_pLogfile->Textout("Animation exists");
				return false;
			}
		}
		ANIMATION temp;

		temp.ActualFrame = 0;
		temp.Framecount = framecount;
		temp.FrameSize = framesize;
		temp.Frametime = frametime;
		temp.Lastime = 0.0f;
		temp.Name = name;
		temp.SourcePosition = sourceposition;

		m_animationList.push_back(temp);

		return true;
	}
	void AnimatedSprite::Update(_In_ Platform::String^ name, _In_ float32 elapsed)
	{
		std::list<ANIMATION>::iterator iterator;

		for (iterator = m_animationList.begin(); iterator != m_animationList.end(); ++iterator)
		{
			if (iterator->Name == name)
			{
				iterator->Lastime += elapsed;
				if (iterator->Lastime > iterator->Frametime)
				{
					iterator->ActualFrame++;
					iterator->Lastime = elapsed;

					if (iterator->ActualFrame > iterator->Framecount)
					{
						iterator->ActualFrame = 0;
						iterator->Lastime = 0.0f;
					}		
				}
			}
		}
	}
	void AnimatedSprite::Restart(_In_ Platform::String^ name)
	{
		std::list<ANIMATION>::iterator iterator;

		for (iterator = m_animationList.begin(); iterator != m_animationList.end(); ++iterator)
		{
			if (iterator->Name == name)
			{
				iterator->ActualFrame = 0;
				iterator->Lastime = 0.0f;
			}
		}
	}

	ID2D1Bitmap* AnimatedSprite::getBitmap()
	{
		return m_bitmap.Get();
	}
	AnimatedSprite::~AnimatedSprite()
	{
		WOtech::ContentManager::Instance->RemoveAnimatedSprite(this);
	}
	Windows::Foundation::Point AnimatedSprite::getPosition()
	{
		return m_position;
	}
	float32 AnimatedSprite::getScale()
	{
		return m_scale;
	}
	Windows::Foundation::Size AnimatedSprite::getFrameSize(_In_ Platform::String^ name)
	{
		std::list<ANIMATION>::iterator iterator;

		for (iterator = m_animationList.begin(); iterator != m_animationList.end(); ++iterator)
		{
			if (iterator->Name == name)
			{
				return iterator->FrameSize;
			}
		}
		Windows::Foundation::Size temp;
		temp.Width = 0.0f;
		temp.Height = 0.0f;

		return temp;
	}

	Windows::Foundation::Rect AnimatedSprite::getFrame(_In_ Platform::String^ name)
	{
		std::list<ANIMATION>::iterator iterator;

		for (iterator = m_animationList.begin(); iterator != m_animationList.end(); ++iterator)
		{
			if (iterator->Name == name)
			{
				Windows::Foundation::Rect temp;
				WOtech::ANIMATION animation = *iterator;

				float32 left = animation.SourcePosition.X + (animation.FrameSize.Width * animation.ActualFrame);
				float32 top = animation.SourcePosition.Y;
				temp.X = left;
				temp.Y = top;
				temp.Width = left + animation.FrameSize.Width;
				temp.Height = top + animation.FrameSize.Height;

				return temp;
			}
		}
		return Windows::Foundation::Rect{ 0.0f, 0.0f, 0.0f, 0.0f };
	}
	float32 AnimatedSprite::getOpacity()
	{
		return m_opacity;
	}
	float32 AnimatedSprite::getRotation()
	{
		return m_rotation;
	}
	SPRITE_FLIP_MODE AnimatedSprite::getFlipMode()
	{
		return m_flipMode;
	}
	BITMAP_INTERPOLATION_MODE AnimatedSprite::getInterpolation()
	{
		return m_interpolation;
	}

	void AnimatedSprite::setPosition(_In_ float32 x, _In_  float32 y)
	{
		m_position = { x,y };
	}
	void AnimatedSprite::setScale(_In_ float32 scale)
	{
		m_scale = scale;
	}
	void AnimatedSprite::setOpacity(_In_ float32 opacity)
	{
		m_opacity = opacity;
	}
	void AnimatedSprite::setRotation(_In_ float32 degree)
	{
		m_rotation = degree;
	}
	void AnimatedSprite::setRotationinRadian(_In_ float32 radian)
	{
		m_rotation = WOtech::RadiantoDegree(radian);
	}
	void AnimatedSprite::setFlipMode(_In_ SPRITE_FLIP_MODE flipmode)
	{
		m_flipMode = flipmode;
	}
	void AnimatedSprite::setInterpolation(_In_ BITMAP_INTERPOLATION_MODE interpolation)
	{
		m_interpolation = interpolation;
	}
}//namespace WOtech