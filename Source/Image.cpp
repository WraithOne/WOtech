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
///			Edited:		20.10.2017
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
	Image::Image()
	{
		m_image = nullptr;
	}

	Image::Image(ID2D1Image* image)
	{
		m_image = image;
	}

	void Image::setImage(ID2D1Image* image)
	{
		m_image = image;
	}

	ID2D1Image* Image::getImage()
	{
		return m_image.Get();
	}
}