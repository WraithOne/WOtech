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
///			Edited:		07.05.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_2DCOMPONENTS_H
#define WO_2DCOMPONENTS_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Numerics.h"

namespace WOtech
{
	// Forward Declaration
	ref class SpriteBatch;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Represents the style of a font face. </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public enum class FONT_STYLE
	{
		/// <summary>	The characters in a normal, or roman, font are upright.  </summary>
		FONT_STYLE_NORMAL,
		/// <summary>	The characters in an oblique font are artificially slanted. </summary>
		FONT_STYLE_OBLIQUE,
		/// <summary>	The characters in an italic font are truly slanted and appear as they were designed. </summary>
		FONT_STYLE_ITALIC
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Specifies the algorithm that is used when images are scaled or rotated.. </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public enum class BITMAP_INTERPOLATION_MODE
	{
		/// <summary>	Use the exact color of the nearest bitmap pixel to the current rendering pixel. </summary>
		BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		/// <summary>	Interpolate a color from the four bitmap pixels that are the nearest to the rendering pixel. </summary>
		BITMAP_INTERPOLATION_MODE_LINEAR,
		/// <summary>	< / summary>
		BITMAP_INTERPOLATION_MODE_FORCE_DWORD
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Indicates whether a specific figure is filled or hollow.  </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public enum class FIGURE_BEGIN
	{
		/// <summary>	Indicates the figure will be filled by the FillGeometry. </summary>
		FIGURE_BEGIN_FILLED,
		/// <summary>	Indicates the figure will not be filled by the FillGeometry and will only consist of an outline.
		/// 			Moreover, the bounds of a hollow figure are zero. D2D1_FIGURE_BEGIN_HOLLOW should be used for stroking, or for other geometry operations.
		/// </summary>
		FIGURE_BEGIN_HALLOW
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Indicates whether a specific figure is open or closed.  </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public enum class FIGURE_END
	{
		/// <summary>	The figure is open. </summary>
		FIGURE_END_OPEN,
		/// <summary>	The figure is closed. </summary>
		FIGURE_END_CLOSED
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Represents a cubic bezier segment drawn between two points. </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public value struct BEZIER_SEGMENT
	{
		/// <summary>	The first control point for the Bezier segment. </summary>
		Windows::Foundation::Point point1;
		/// <summary>	The second control point for the Bezier segment. </summary>
		Windows::Foundation::Point point2;
		/// <summary>	The end point for the Bezier segment. </summary>
		Windows::Foundation::Point point3;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Defines the direction that an elliptical arc is drawn.  </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public enum class SWEEP_DIRECTION
	{
		/// <summary>	Arcs are drawn in a counterclockwise (negative-angle) direction. </summary>
		D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE,
		/// <summary>	Arcs are drawn in a clockwise (positive-angle) direction.  </summary>
		D2D1_SWEEP_DIRECTION_CLOCKWISE
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Specifies whether an arc should be greater than 180 degrees. </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public enum class ARC_SIZE
	{
		/// <summary>	An arc's sweep should be 180 degrees or less. </summary>
		D2D1_ARC_SIZE_SMALL,
		/// <summary>	An arc's sweep should be 180 degrees or greater. </summary>
		D2D1_ARC_SIZE_LARGE
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Describes an elliptical arc between two points. </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public value struct ARC_SEGMENT
	{
		/// <summary>	The end point of the arc. < / summary>
		Windows::Foundation::Point point;
		/// <summary>	The x-radius and y-radius of the arc. < / summary>
		Windows::Foundation::Size size;
		/// <summary>	A value that specifies how many degrees in the clockwise direction the ellipse is rotated relative to the current coordinate system. < / summary>
		FLOAT rotationAngle;
		/// <summary>	A value that specifies whether the arc sweep is clockwise or counterclockwise. < / summary>
		SWEEP_DIRECTION sweepDirection;
		/// <summary>	A value that specifies whether the given arc is larger than 180 degrees. < / summary>
		ARC_SIZE arcSize;
	};

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
		WOtech::RECT		area;
		Windows::UI::Color	color;
		float32				tickness;
		float32				rotation;
	};

	public value struct RECTANGLE_OUTLINED
	{
		WOtech::RECT		area;
		Windows::UI::Color	color;
		float32				tickness;
		Windows::UI::Color	outlinecolor;
		float32				rotation;
	};

	public value struct RECTANGLE_FILLED
	{
		WOtech::RECT		area;
		Windows::UI::Color	color;
		float32				rotation;
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
		WOtech::RECT getSourceRECT();

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
		void setFlipMode(_In_ SPRITE_FLIP_MODE flipmode);
		void setInterpolation(_In_ BITMAP_INTERPOLATION_MODE interpolation);

		//Getter
		WOtech::RECT				getSourceRect();
		WOtech::RECT				getDestinationRect();

		Windows::Foundation::Point	getPosition();
		Windows::Foundation::Size	getSize();
		float32						getOpacity();
		float32						getRotation();
		SPRITE_FLIP_MODE			getFlipMode();
		BITMAP_INTERPOLATION_MODE	getInterpolation();

	internal:
		ID2D1Bitmap1*				getBitmap();

	private:
		~Sprite();

	private:
		Platform::String^						m_fileName;
		Microsoft::WRL::ComPtr<ID2D1Bitmap1>	m_bitmap;

		WOtech::RECT							m_sourceRect;
		Windows::Foundation::Point				m_position;
		Windows::Foundation::Size				m_size;
		float32									m_rotation;
		float32									m_opacity;
		SPRITE_FLIP_MODE						m_flipMode;
		BITMAP_INTERPOLATION_MODE				m_interpolation;
	};// class Sprite

	public ref class AnimatedSprite sealed
	{
	public:
		[Windows::Foundation::Metadata::DefaultOverloadAttribute]
		AnimatedSprite(_In_ Platform::String^ filename);
		AnimatedSprite(_In_ WOtech::Bitmap^ bitmap);

		void Load(_In_ SpriteBatch^ spriteBatch);
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
		void setInterpolation(_In_ BITMAP_INTERPOLATION_MODE interpolation);

		//Getter
		Windows::Foundation::Point	getPosition();
		float32						getScale();
		Windows::Foundation::Size	getFrameSize(_In_ Platform::String^ name);
		WOtech::RECT				getFrame(_In_ Platform::String^ name);
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

		std::list<ANIMATION>				m_animationList;

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
			_In_ FONT_STYLE style,
			_In_ Windows::UI::Color color,
			_In_ Windows::Foundation::Point position,
			_In_ Windows::Foundation::Size layoutsize);

		// Setters

		void setSize(_In_ float32 size);

		void setText(_In_ Platform::String^ text);

		void setStyle(_In_ FONT_STYLE style);

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
		void Create(SpriteBatch^ spritebatch);

		void OpenGeometry();

		void StartFigure(Windows::Foundation::Point strartposition, FIGURE_BEGIN begin);
		void addArc(ARC_SEGMENT arcsegment);
		void addBezier(BEZIER_SEGMENT beziersegment);
		void addLine(Windows::Foundation::Point lineend);
		void EndFigure(FIGURE_END figureend);

		void CloseGeometry();

		void setColor(Windows::UI::Color color);

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

	public interface class IBatch2D
	{
		float getDepth();
	};

	public ref class Batch2D_Text sealed : public IBatch2D
	{
	public:
		Batch2D_Text(_In_ float depth, _In_ WOtech::TextBlock^ text);
		float virtual getDepth();
		WOtech::TextBlock^ getText();

	private:
		float m_depth;
		WOtech::TextBlock^	m_text;
	};
}
#endif
