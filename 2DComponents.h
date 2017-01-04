////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: 2DComponents.h
///
///			Created:	06.04.2016
///			Edited:		27.11.2016
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_2DCOMPONENTS_H
#define WO_2DCOMPONENTS_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "DXWrapper.h"

namespace WOtech
{
	// Forward Declaration
	ref class SpriteBatch;

	public enum class SPRITE_FLIP_MODE
	{
		None,
		Horizontal,
		Vertical,
		Both
	};

	public value struct CIRCLE
	{
		Windows::Foundation::Point	position;
		float32						radius;
		Windows::UI::Color			color;
		float32						tickness;
		float32						rotation;
	};

	public value struct CIRCLE_OUTLINED
	{
		Windows::Foundation::Point	position;
		float32						radius;
		Windows::UI::Color			color;
		float32						tickness;
		Windows::UI::Color			outlinecolor;
		float32						rotation;
	};

	public value struct CIRCLE_FILLED
	{
		Windows::Foundation::Point	position;
		float32						radius;
		Windows::UI::Color			color;
		float32						rotation;
	};

	public value struct RECTANGLE
	{
		WOtech::DXWrapper::RECT		area;
		Windows::UI::Color			color;
		float32						tickness;
		float32						rotation;
	};

	public value struct RECTANGLE_OUTLINED
	{
		WOtech::DXWrapper::RECT		area;
		Windows::UI::Color			color;
		float32						tickness;
		Windows::UI::Color			outlinecolor;
		float32						rotation;
	};

	public value struct RECTANGLE_FILLED
	{
		WOtech::DXWrapper::RECT		area;
		Windows::UI::Color			color;
		float32						rotation;
	};

	public value struct ANIMATION
	{
		Platform::String^			Name;
		uint32						Framecount;
		float32						Frametime;
		float32						Lastime;
		uint32						ActualFrame;
		Windows::Foundation::Size	FrameSize;
		Windows::Foundation::Point	SourcePosition;
	};

	public ref class Sprite sealed
	{
	public:
		Sprite(_In_ Platform::String^ filename);

		void Load(_In_ WOtech::SpriteBatch^ spriteBatch);

		//Setter
		void setPosition(_In_ float32 x, _In_ float32 y);
		void setSize(_In_ float32 width, _In_ float32 height);
		void setSourceRect(_In_ float32 x, _In_ float32 y, _In_ float32 height, _In_ float32 width);
		void setOpacity(_In_ float32 opacity);
		void setRotation(_In_ float32 degree);
		void setRotationinRadian(_In_ float32 radian);
		void setFlipMode(_In_ SPRITE_FLIP_MODE flipmode);
		void setInterpolation(_In_ WOtech::DXWrapper::BITMAP_INTERPOLATION_MODE interpolation);

		//Getter
		WOtech::DXWrapper::RECT							getSourceRect();
		WOtech::DXWrapper::RECT							getDestinationRect();

		Windows::Foundation::Point						getPosition();
		Windows::Foundation::Size						getSize();
		float32											getOpacity();
		float32											getRotation();
		SPRITE_FLIP_MODE								getFlipMode();
		WOtech::DXWrapper::BITMAP_INTERPOLATION_MODE	getInterpolation();

	internal:
		ID2D1Bitmap*									getBitmap();

	private:
		~Sprite();

	private:
		Platform::String^								m_fileName;
		Microsoft::WRL::ComPtr<ID2D1Bitmap>				m_Bitmap;

		WOtech::DXWrapper::RECT							m_sourceRect;
		Windows::Foundation::Point						m_position;
		Windows::Foundation::Size						m_size;
		float32											m_rotation;
		float32											m_opacity;
		SPRITE_FLIP_MODE								m_flipMode;
		WOtech::DXWrapper::BITMAP_INTERPOLATION_MODE	m_interpolation;
	};// class Sprite

	public ref class AnimatedSprite sealed
	{
	public:
		AnimatedSprite(_In_ Platform::String^ filename);

		void Load(_In_ WOtech::SpriteBatch^ spriteBatch);

		Platform::Boolean AddAnimation(_In_ Platform::String^ name, _In_ uint32 framecount, _In_ float32 frametime, _In_ Windows::Foundation::Size framesize, _In_ Windows::Foundation::Point sourceposition);
		void Update(_In_ Platform::String^ name, _In_ float32 elapsed);
		void Restart(_In_ Platform::String^ name);

		//Setter
		void setPosition(_In_ float32 x, _In_ float32 y);
		void setSize(_In_ float32 width, _In_ float32 height);
		void setOpacity(_In_ float32 opacity);
		void setRotation(_In_ float32 degree);
		void setRotationinRadian(_In_ float32 radian);
		void setFlipMode(_In_ SPRITE_FLIP_MODE flipmode);
		void setInterpolation(_In_ WOtech::DXWrapper::BITMAP_INTERPOLATION_MODE interpolation);

		//Getter
		Windows::Foundation::Point						getPosition();
		Windows::Foundation::Size						getSize();
		Windows::Foundation::Size						getFrameSize(_In_ Platform::String^ name);
		WOtech::DXWrapper::RECT							getFrame(_In_ Platform::String^ name);
		float32											getOpacity();
		float32											getRotation();
		SPRITE_FLIP_MODE								getFlipMode();
		DXWrapper::BITMAP_INTERPOLATION_MODE			getInterpolation();

	internal:
		ID2D1Bitmap*									getBitmap();

	private:
		~AnimatedSprite();

	private:
		Platform::String^								m_fileName;
		Microsoft::WRL::ComPtr<ID2D1Bitmap>				m_Bitmap;

		std::list<ANIMATION>							m_animationList;

		Windows::Foundation::Point						m_position;
		Windows::Foundation::Size						m_size;
		float32											m_rotation;
		SPRITE_FLIP_MODE								m_flipMode;
		float32											m_opacity;
		WOtech::DXWrapper::BITMAP_INTERPOLATION_MODE	m_interpolation;
	};

	public ref class Font sealed
	{
	public:
		Font(_In_ Platform::String^ filename);

		void Load();

		// GETTER
		Platform::String^								getFontname();

	internal:
		IDWriteFontCollection*							getColletion();
		IDWriteFontCollection**							getCollectionL();

	private:
		~Font();

	private:
		Platform::String^								m_fileName;
		Microsoft::WRL::ComPtr<IDWriteFontCollection>	m_collection;
	};//class Font

	public ref class Text sealed
	{
	public:
		void CreateText(_In_ WOtech::Font^ font, _In_  WOtech::SpriteBatch^ spriteBatch);
		void CreateText(_In_ WOtech::Font^ font,
			_In_  WOtech::SpriteBatch^ spriteBatch,
			_In_ float32 size,
			_In_ Platform::String^ text,
			_In_ WOtech::DXWrapper::FONT_STYLE style,
			_In_ Windows::UI::Color color,
			_In_ Windows::Foundation::Point position,
			_In_ Windows::Foundation::Size layoutsize);

		// Setters

		void setSize(_In_ float32 size);

		void setText(_In_ Platform::String^ text);

		void setStyle(_In_ WOtech::DXWrapper::FONT_STYLE style);

		void setPosition(_In_ float32 x, _In_ float32 y);
		void setPosition(_In_ Windows::Foundation::Point position);

		void setRotation(_In_ float32 degree);
		void setRotationinRadian(_In_ float32 radian);
		void setRotationinVector(_In_ float32 x, _In_ float32 y);

		void setLayoutBox(_In_ float32 w, _In_ float32 h);
		void setLayoutBox(_In_ Windows::Foundation::Size layoutboxsize);

		void setColor(_In_ float32 r, _In_ float32 g, _In_ float32 b, _In_ float32 a);
		void setColor(_In_ Windows::UI::Color color);

		// Getters
		Windows::Foundation::Point						getPosition();
		float32											getRotation();
		Windows::Foundation::Size						getlayoutbox();

	internal:
		IDWriteTextLayout*								getLayout();
		ID2D1SolidColorBrush*							getBrush();

	private:
		~Text();
		void makeText();
		void makeBrush(_In_ SpriteBatch^ spriteBatch);

	private:
		Microsoft::WRL::ComPtr<IDWriteFactory>			m_Wfactory;

		Microsoft::WRL::ComPtr<IDWriteTextFormat>		m_format;
		Microsoft::WRL::ComPtr<IDWriteTextLayout>		m_layout;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>	m_brush;
		Font^											m_font;

		float32											m_size;
		Platform::String^								m_text;
		WOtech::DXWrapper::FONT_STYLE					m_style;
		Windows::Foundation::Point						m_position;
		float32											m_rotation;
		Windows::Foundation::Size						m_layoutbox;

		Platform::Boolean								m_changed;
	};//class Text

	public ref class Geometry sealed
	{
	public:
		Geometry();
		void Create(SpriteBatch^ spritebatch);

		void OpenGeometry();

		void StartFigure(Windows::Foundation::Point strartposition, WOtech::DXWrapper::FIGURE_BEGIN begin);
		void addArc(WOtech::DXWrapper::ARC_SEGMENT arcsegment);
		void addBezier(WOtech::DXWrapper::BEZIER_SEGMENT beziersegment);
		void addLine(Windows::Foundation::Point lineend);
		void EndFigure(WOtech::DXWrapper::FIGURE_END figureend);

		void CloseGeometry();

		void setColor(Windows::UI::Color color);

	internal:
		ID2D1PathGeometry*								getGeometry();
		ID2D1SolidColorBrush*							getBrush();

	private:
		~Geometry();

	private:
		Microsoft::WRL::ComPtr<ID2D1PathGeometry>		m_geometryPath;
		Microsoft::WRL::ComPtr<ID2D1GeometrySink>		m_geometrySink;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>	m_geometryBrush;
	};
}
#endif
