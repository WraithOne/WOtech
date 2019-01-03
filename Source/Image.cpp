////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Image.cpp
///
///			Description:
///
///			Created:	20.10.2017
///			Edited:		25.12.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <ContentManager.h>
#include <2DComponents.h>
#include <SpriteBatch.h>

namespace WOtech
{
	Image::Image()
	{
		m_image = nullptr;
		WOtech::ContentManager::Instance->AddImage(this);
	}

	void Image::Reset()
	{
		m_image.Reset();;
	}

	Image::Image(_In_ ID2D1Image* image)
	{
		m_image = image;
		WOtech::ContentManager::Instance->AddImage(this);
	}

	void Image::setImage(_In_ ID2D1Image* image)
	{
		m_image = image;
	}

	ID2D1Image* Image::getImage()
	{
		return m_image.Get();
	}
	Image::~Image()
	{
		WOtech::ContentManager::Instance->RemoveImage(this);
	}
}