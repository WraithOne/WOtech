////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: TextBlock.cpp
///
///			Description:
///
///			Created:	05.09.2014
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <2DComponents.h>
#include <SpriteBatch.h>
#include <Utilities.h>
#include <DXWrapper.h>

namespace WOtech
{
	void TextBlock::CreateText(_In_ WOtech::Font^ font, _In_ WOtech::SpriteBatch^ spriteBatch)
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
	void TextBlock::CreateText(_In_ Font^ font, _In_ WOtech::SpriteBatch^ spriteBatch, _In_ float32 size, _In_ Platform::String^ text, _In_ WOtech::FONT_STYLE style, _In_ Windows::UI::Color color, _In_ Windows::Foundation::Point position, _In_ Windows::Foundation::Size layoutsize)
	{
		m_font = font;

		m_size = size;
		m_text = text;
		m_style = style;
		m_position = position;
		m_layoutbox = layoutsize;

		makeBrush(spriteBatch);

		m_brush->SetColor(WOtech::DXWrapper::wrapColorD2D(color));

		makeText();
	}

	void TextBlock::setSize(_In_ float32 size)
	{
		if (size != m_size)
		{
			m_size = size;

			makeText();
		}
	}

	void TextBlock::setText(_In_ Platform::String^ text)
	{
		if (text != m_text)
		{
			m_text = text;

			makeText();
		}
	}

	void TextBlock::setPosition(_In_ float32 x, _In_ float32 y)
	{
		m_position.X = x;
		m_position.Y = y;
	}
	void TextBlock::setPosition(_In_ Windows::Foundation::Point position)
	{
		m_position = position;
	}

	void TextBlock::setRotation(_In_ float32 degree)
	{
		m_rotation = degree;
	}

	void TextBlock::setRotationinRadian(_In_ float32 radian)
	{
		m_rotation = RadiantoDegree(radian);
	}

	void TextBlock::setRotationinVector(_In_ float32 x, _In_ float32 y)
	{
		m_rotation = VectortoDegree(x, y);
	}

	void TextBlock::setColor(_In_ float32 r, _In_ float32 g, _In_ float32 b, _In_ float32 a)
	{
		if (m_brush)
		{
			m_brush->SetColor(D2D1::ColorF(r, g, b));
		}
	}
	void TextBlock::setColor(_In_ Windows::UI::Color color)
	{
		if (m_brush)
		{
			m_brush->SetColor(WOtech::DXWrapper::wrapColorD2D(color));
		}
	}

	void TextBlock::setStyle(_In_ WOtech::FONT_STYLE style)
	{
		if (style != m_style)
		{
			m_style = style;

			makeText();
		}
	}

	void TextBlock::setLayoutBox(_In_ float32 w, _In_ float32 h)
	{
		if (w != m_layoutbox.Width && h != m_layoutbox.Height)
		{
			m_layoutbox.Width = w;
			m_layoutbox.Height = h;

			makeText();
		}
	}
	void TextBlock::setLayoutBox(_In_ Windows::Foundation::Size layoutboxsize)
	{
		if (layoutboxsize.Width != m_layoutbox.Width && layoutboxsize.Height != m_layoutbox.Height)
		{
			m_layoutbox = layoutboxsize;

			makeText();
		}
	}

	TextBlock::~TextBlock()
	{
		// todo: Content Manager
	}

	void TextBlock::makeText()
	{
		HRESULT hr;

		if (!m_font->getColletion()) //todo: make it nice
			ThrowIfFailed(E_FAIL);

		m_layout = nullptr;
		m_format = nullptr;

		if (m_wFactory == NULL)
		{
			hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &m_wFactory);
			ThrowIfFailed(hr);
		}

		hr = m_wFactory->CreateTextFormat(m_font->getFontname()->Data(), m_font->getColletion(), DWRITE_FONT_WEIGHT_NORMAL, WOtech::DXWrapper::wraptFontStyle(m_style), DWRITE_FONT_STRETCH_NORMAL, m_size, L"", &m_format);
		ThrowIfFailed(hr);

		hr = m_wFactory->CreateTextLayout(m_text->Data(), static_cast<uint32>(m_text->Length()), m_format.Get(), m_layoutbox.Width, m_layoutbox.Height, &m_layout);
		ThrowIfFailed(hr);
	} //todo: memory leak? ->growing memory by calling it often

	void TextBlock::makeBrush(_In_ WOtech::SpriteBatch^ spriteBatch)
	{
		HRESULT hr;

		if (!spriteBatch)
		{
			ThrowIfFailed(E_FAIL);
		}

		hr = spriteBatch->GetDeviceContext()->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f), &m_brush);
		ThrowIfFailed(hr);
	}

	IDWriteTextLayout* TextBlock::getLayout()
	{
		return m_layout.Get();
	}
	ID2D1SolidColorBrush* TextBlock::getBrush()
	{
		return m_brush.Get();
	};
	Windows::Foundation::Point TextBlock::getPosition()
	{
		return m_position;
	};
	float32 TextBlock::getRotation()
	{
		return m_rotation;
	}
	Windows::Foundation::Size TextBlock::getlayoutbox()
	{
		return m_layoutbox;
	}
}//namespace WOtech