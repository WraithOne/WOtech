////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: 2DComponents.h
///
///			Description:
///
///			Created:	06.04.2016
///			Edited:		23.09.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_2DCOMPONENTS_H
#define WO_2DCOMPONENTS_H

//////////////
// INCLUDES //
//////////////
#include <pch.h>

namespace WOtech
{
	// Forward Declaration
	ref class SpriteBatch;

	public enum class FONT_STYLE
	{
		FONT_STYLE_NORMAL,
		FONT_STYLE_OBLIQUE,
		FONT_STYLE_ITALIC
	};

	public enum class BITMAP_INTERPOLATION_MODE
	{
		BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		BITMAP_INTERPOLATION_MODE_LINEAR,
		BITMAP_INTERPOLATION_MODE_FORCE_DWORD
	};

	public enum class FIGURE_BEGIN
	{
		FIGURE_BEGIN_FILLED,
		FIGURE_BEGIN_HALLOW
	};

	public enum class FIGURE_END
	{
		FIGURE_END_OPEN,
		FIGURE_END_CLOSED
	};

	public value struct BezierSegment
	{
		Windows::Foundation::Point Point1;
		Windows::Foundation::Point Point2;
		Windows::Foundation::Point Point3;
	};

	public enum class SWEEP_DIRECTION
	{
		D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE,
		D2D1_SWEEP_DIRECTION_CLOCKWISE
	};

	public enum class ARC_SIZE
	{
		D2D1_ARC_SIZE_SMALL,
		D2D1_ARC_SIZE_LARGE
	};

	public value struct ArcSegment
	{
		Windows::Foundation::Point	Point;
		Windows::Foundation::Size	Size;
		FLOAT						RotationAngle;
		WOtech::SWEEP_DIRECTION		SweepDirection;
		WOtech::ARC_SIZE			ArcSize;
	};

	public enum class SPRITE_FLIP_MODE
	{
		NONE,
		HORIZONTAL,
		VERTICAL,
		BOTH
	};

	public value struct Circle
	{
		Windows::Foundation::Point	Position;
		float32						Radius;
		Windows::UI::Color			Color;
		float32						Tickness;
		float32						Rotation;
	};

	public value struct CircleOutlined
	{
		Windows::Foundation::Point	Position;
		float32						Radius;
		Windows::UI::Color			Color;
		float32						Tickness;
		Windows::UI::Color			Outlinecolor;
		float32						Rotation;
	};

	public value struct CircleFilled
	{
		Windows::Foundation::Point	Position;
		float32						Radius;
		Windows::UI::Color			Color;
		float32						Rotation;
	};

	public value struct Rectangle
	{
		Windows::Foundation::Rect	Area;
		Windows::UI::Color			Color;
		float32						Tickness;
		float32						Rotation;
	};

	public value struct RectangleOutlined
	{
		Windows::Foundation::Rect	Area;
		Windows::UI::Color			Color;
		float32						Tickness;
		Windows::UI::Color			Outlinecolor;
		float32						Rotation;
	};

	public value struct RectangleFilled
	{
		Windows::Foundation::Rect	Area;
		Windows::UI::Color			Color;
		float32						Rotation;
	};

	public value struct Animation
	{
		Platform::String^			Name;
		uint32						Framecount;
		float32						Frametime;
		float32						Lastime;
		uint32						ActualFrame;
		Windows::Foundation::Size	FrameSize;
		Windows::Foundation::Point	SourcePosition;
	};

	public ref class Image sealed
	{
	public:
		Image();
		void Reset();

	internal:
		Image(_In_ ID2D1Image* image);

		void setImage(_In_ ID2D1Image* image);
		ID2D1Image* getImage();

	private:
		~Image();

	private:
		Microsoft::WRL::ComPtr<ID2D1Image>	m_image;
	};

	public ref class Bitmap sealed
	{
	public:
		Bitmap();
		Bitmap(_In_ WOtech::SpriteBatch^ spriteBatch, _In_ UINT width, _In_ UINT height);
		Bitmap(_In_ WOtech::SpriteBatch^ spriteBatch, _In_ Platform::String^ fileName);

		void Reset();

		Windows::Foundation::Size getSize();
		Windows::Foundation::Rect getSourceRECT();

	internal:
		Bitmap(_In_ ID2D1Bitmap1* bitmap);

		void setBitmap(_In_ ID2D1Bitmap1* bitmap);
		ID2D1Bitmap1* getBitmap();
	private:
		~Bitmap();

	private:
		Microsoft::WRL::ComPtr<ID2D1Bitmap1>	m_bitmap;
	};

	public ref class Sprite sealed
	{
	public:
		Sprite(_In_ Platform::String^ filename);

		void Load(_In_ WOtech::SpriteBatch^ spriteBatch);
		void UnLoad();

		//Setter
		void setPosition(_In_ float32 x, _In_ float32 y);
		void setSize(_In_ float32 width, _In_ float32 height);
		void setSourceRect(_In_ float32 x, _In_ float32 y, _In_ float32 height, _In_ float32 width);
		void setOpacity(_In_ float32 opacity);
		void setRotation(_In_ float32 degree);
		void setRotationinRadian(_In_ float32 radian);
		void setFlipMode(_In_ WOtech::SPRITE_FLIP_MODE flipmode);
		void setInterpolation(_In_ WOtech::BITMAP_INTERPOLATION_MODE interpolation);

		//Getter
		Windows::Foundation::Rect			getSourceRect();
		Windows::Foundation::Rect			getDestinationRect();

		Windows::Foundation::Point			getPosition();
		Windows::Foundation::Size			getSize();
		float32								getOpacity();
		float32								getRotation();
		WOtech::SPRITE_FLIP_MODE			getFlipMode();
		WOtech::BITMAP_INTERPOLATION_MODE	getInterpolation();

	internal:
		ID2D1Bitmap1*						getBitmap();

	private:
		~Sprite();

	private:
		Platform::String^						m_fileName;
		Microsoft::WRL::ComPtr<ID2D1Bitmap1>	m_bitmap;

		Windows::Foundation::Rect				m_sourceRect;
		Windows::Foundation::Point				m_position;
		Windows::Foundation::Size				m_size;
		float32									m_rotation;
		float32									m_opacity;
		WOtech::SPRITE_FLIP_MODE				m_flipMode;
		WOtech::BITMAP_INTERPOLATION_MODE		m_interpolation;
	};// class Sprite

	public ref class AnimatedSprite sealed
	{
	public:
		[Windows::Foundation::Metadata::DefaultOverloadAttribute]
		AnimatedSprite(_In_ Platform::String^ filename);
		AnimatedSprite(_In_ WOtech::Bitmap^ bitmap);

		void Load(_In_ WOtech::SpriteBatch^ spriteBatch);
		void UnLoad();

		Platform::Boolean AddAnimation(_In_ Platform::String^ name, _In_ uint32 framecount, _In_ float32 frametime, _In_ Windows::Foundation::Size framesize, _In_ Windows::Foundation::Point sourceposition);
		void Update(_In_ Platform::String^ name, _In_ float32 elapsed);
		void Restart(_In_ Platform::String^ name);

		//Setter
		void setPosition(_In_ float32 x, _In_ float32 y);
		void setScale(_In_ float32 scale);
		void setOpacity(_In_ float32 opacity);
		void setRotation(_In_ float32 degree);
		void setRotationinRadian(_In_ float32 radian);
		void setFlipMode(_In_ SPRITE_FLIP_MODE flipmode);
		void setInterpolation(_In_ WOtech::BITMAP_INTERPOLATION_MODE interpolation);

		//Getter
		Windows::Foundation::Point	getPosition();
		float32						getScale();
		Windows::Foundation::Size	getFrameSize(_In_ Platform::String^ name);
		Windows::Foundation::Rect				getFrame(_In_ Platform::String^ name);
		float32						getOpacity();
		float32						getRotation();
		SPRITE_FLIP_MODE			getFlipMode();
		BITMAP_INTERPOLATION_MODE	getInterpolation();

	internal:
		ID2D1Bitmap*				getBitmap();

	private:
		~AnimatedSprite();

	private:
		Platform::Boolean					m_fromFile;
		Platform::String^					m_fileName;

		Microsoft::WRL::ComPtr<ID2D1Bitmap>	m_bitmap;

		std::list<WOtech::Animation>		m_animationList;

		Windows::Foundation::Point			m_position;
		float32								m_scale;
		float32								m_rotation;
		SPRITE_FLIP_MODE					m_flipMode;
		float32								m_opacity;
		BITMAP_INTERPOLATION_MODE			m_interpolation;
	};

	public ref class Font sealed
	{
	public:
		Font(_In_ Platform::String^ filename);

		void Load();
		void UnLoad();

		// GETTER
		Platform::String^		getFontname();

	internal:
		IDWriteFontCollection*	getColletion();
		IDWriteFontCollection**	getCollectionL();

	private:
		~Font();

	private:
		Platform::String^								m_fileName;
		Microsoft::WRL::ComPtr<IDWriteFontCollection>	m_collection;
	};//class Font

	public ref class TextBlock sealed
	{
	public:
		void CreateText(_In_ WOtech::Font^ font, _In_  WOtech::SpriteBatch^ spriteBatch);
		void CreateText(_In_ WOtech::Font^ font,
			_In_  WOtech::SpriteBatch^ spriteBatch,
			_In_ float32 size,
			_In_ Platform::String^ text,
			_In_ WOtech::FONT_STYLE style,
			_In_ Windows::UI::Color color,
			_In_ Windows::Foundation::Point position,
			_In_ Windows::Foundation::Size layoutsize);

		// Setters

		void setSize(_In_ float32 size);

		void setText(_In_ Platform::String^ text);

		void setStyle(_In_ WOtech::FONT_STYLE style);

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
		Windows::Foundation::Point	getPosition();
		float32						getRotation();
		Windows::Foundation::Size	getlayoutbox();

	internal:
		IDWriteTextLayout*			getLayout();
		ID2D1SolidColorBrush*		getBrush();

	private:
		~TextBlock();
		void makeText();
		void makeBrush(_In_ SpriteBatch^ spriteBatch);

	private:
		Microsoft::WRL::ComPtr<IDWriteFactory>			m_wFactory;

		Microsoft::WRL::ComPtr<IDWriteTextFormat>		m_format;
		Microsoft::WRL::ComPtr<IDWriteTextLayout>		m_layout;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>	m_brush;
		Font^											m_font;

		float32											m_size;
		Platform::String^								m_text;
		FONT_STYLE										m_style;
		Windows::Foundation::Point						m_position;
		float32											m_rotation;
		Windows::Foundation::Size						m_layoutbox;

		Platform::Boolean								m_changed;
	};//class Text

	public ref class Geometry sealed
	{
	public:
		Geometry();
		void Create(_In_ SpriteBatch^ spritebatch);

		void OpenGeometry();

		void StartFigure(_In_ Windows::Foundation::Point strartposition, _In_ WOtech::FIGURE_BEGIN begin);
		void addArc(_In_ WOtech::ArcSegment arcsegment);
		void addBezier(_In_ WOtech::BezierSegment beziersegment);
		void addLine(_In_ Windows::Foundation::Point lineend);
		void EndFigure(_In_ WOtech::FIGURE_END figureend);

		void CloseGeometry();

		void setColor(_In_ Windows::UI::Color color);

	internal:
		ID2D1PathGeometry*		getGeometry();
		ID2D1SolidColorBrush*	getBrush();

	private:
		~Geometry();

	private:
		Microsoft::WRL::ComPtr<ID2D1PathGeometry>		m_geometryPath;
		Microsoft::WRL::ComPtr<ID2D1GeometrySink>		m_geometrySink;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>	m_geometryBrush;
	};
}
#endif
