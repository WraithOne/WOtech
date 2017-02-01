////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: Text.cpp
///
///			Created:	05.09.2014
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
using namespace WOtech::DXWrapper;

namespace WOtech
{
	void Text::CreateText(_In_ Font^ font, _In_ SpriteBatch^ spriteBatch)
	{
		m_font = font;

		m_size = 16.0f;
		m_text = L"This is a Text";
		m_style = FONT_STYLE::FONT_STYLE_NORMAL;
		m_position = { 0.0f, 0.0f };
		m_layoutbox = { 800.0f, 600.0f };

		makeBrush(spriteBatch);
		makeText();

		// todo: Content Manager
	}
	void Text::CreateText(_In_ Font^ font, _In_ SpriteBatch^ spriteBatch, _In_ float32 size, _In_ String^ text, _In_ FONT_STYLE style, _In_ Color color, _In_ Point position, _In_ Size layoutsize)
	{
		m_font = font;

		m_size = size;
		m_text = text;
		m_style = style;
		m_position = position;
		m_layoutbox = layoutsize;

		makeBrush(spriteBatch);
		
		m_brush->SetColor(wrapColor(color));

		makeText();
	}

	void Text::setSize(_In_ float32 size)
	{
	if (size != m_size)
		{
			m_size = size;

			makeText();
		}
	}

	void Text::setText(_In_ String^ text)
	{
		if (text != m_text)
		{
			m_text = text;

			makeText();
		}
	}

	void Text::setPosition(_In_ float32 x, _In_ float32 y)
	{
		m_position.X = x;
		m_position.Y = y;
	}
	void Text::setPosition(_In_ Point position)
	{
		m_position = position;
	}

	void Text::setRotation(_In_ float32 degree)
	{
		m_rotation = degree;
	}

	void Text::setRotationinRadian(_In_ float32 radian)
	{
		m_rotation = RadiantoDegree(radian);
	}

	void Text::setRotationinVector(_In_ float32 x, _In_ float32 y)
	{
		// todo:!!!!!
	}

	void Text::setColor(_In_ float32 r, _In_ float32 g, _In_ float32 b, _In_ float32 a)
	{
		if (m_brush)
		{
			m_brush->SetColor(D2D1::ColorF(r, g, b));
		}
	}
	void Text::setColor(_In_ Color color)
	{
		if (m_brush)
		{
			m_brush->SetColor(wrapColor(color));
		}
	}

	void Text::setStyle(_In_ FONT_STYLE style)
	{
		if (style != m_style)
		{
			m_style = style;

			makeText();
		}
	}

	void Text::setLayoutBox(_In_ float32 w, _In_ float32 h)
	{
		if (w != m_layoutbox.Width && h != m_layoutbox.Height)
		{
			m_layoutbox.Width = w;
			m_layoutbox.Height = h;

			makeText();
		}
	}
	void Text::setLayoutBox(_In_ Size layoutboxsize)
	{
		if (layoutboxsize.Width != m_layoutbox.Width && layoutboxsize.Height != m_layoutbox.Height)
		{
			m_layoutbox = layoutboxsize;

			makeText();
		}
	}

	Text::~Text()
	{
		// todo: Content Manager
	}

	void Text::makeText()
	{
		HRESULT hr;

		if (!m_font->getColletion()) //todo: make it nice
			ThrowIfFailed(E_FAIL);

		m_layout = nullptr;
		m_format = nullptr;

		if (m_Wfactory == NULL)
		{
			hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &m_Wfactory);
			ThrowIfFailed(hr);
		}

		hr = m_Wfactory->CreateTextFormat(m_font->getFontname()->Data(), m_font->getColletion(), DWRITE_FONT_WEIGHT_NORMAL, wraptFontStyle(m_style), DWRITE_FONT_STRETCH_NORMAL, m_size, L"", &m_format);
		ThrowIfFailed(hr);

		hr = m_Wfactory->CreateTextLayout(m_text->Data(), static_cast<uint32>(m_text->Length()), m_format.Get(), m_layoutbox.Width, m_layoutbox.Height, &m_layout);
		ThrowIfFailed(hr);
	} //todo: memory leak? ->growing memory by calling it often

	void Text::makeBrush(_In_ SpriteBatch^ spriteBatch)
	{
		HRESULT hr;

		if (!spriteBatch)
		{
			ThrowIfFailed(E_FAIL);
		}

		hr = spriteBatch->GetDeviceContext()->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f), &m_brush);
		ThrowIfFailed(hr);
	}

	IDWriteTextLayout* Text::getLayout()
	{
		return m_layout.Get();
	}
	ID2D1SolidColorBrush* Text::getBrush()
	{
		return m_brush.Get();
	};
	Point Text::getPosition()
	{
		return m_position;
	};
	float32 Text::getRotation()
	{
		return m_rotation;
	}
	Size Text::getlayoutbox()
	{
		return m_layoutbox;
	}
}//namespace WOtech