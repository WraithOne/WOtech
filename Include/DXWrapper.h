////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: DXWrapper.h
///
///			Description: Wrapper Enums/structs/funcitons for DirectX
///
///			Created:	06.11.2016
///			Edited:		22.10.2017
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_DXWRAPPER_H
#define WO_DXWRAPPER_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Utilities.h"
#include "VertexTypes.h"
#include "2DComponents.h"
#include "3DComponents.h"
#include "AudioComponents.h"

namespace WOtech
{
	namespace DXWrapper
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts Windows::UI::Color into D2D1_COLOR_F. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="color"> Describes a color in terms of alpha, red, green, and blue channels. </param>
		///
		/// <returns>	D2D1_COLOR_F, Describes the red, green, blue, and alpha components of a color. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline D2D1_COLOR_F wrapColorD2D(_In_ Windows::UI::Color color)
		{
			return D2D1::ColorF(static_cast<float>(color.R), static_cast<float>(color.G), static_cast<float>(color.B), static_cast<float>(color.A));
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts Windows::UI::Color into XMVECTORF32. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="color"> Describes a color in terms of alpha, red, green, and blue channels. </param>
		///
		/// <returns>	XMVECTORF32, Describes the red, green, blue, and alpha components of a color. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DirectX::XMVECTORF32 wrapColorD3D(_In_ Windows::UI::Color color)
		{
			DirectX::XMVECTORF32 out = { static_cast<float>(color.R) / 256.0f, static_cast<float>(color.G) / 256.0f, static_cast<float>(color.B) / 256.0f, static_cast<float>(color.A) / 256.0f };
			return out;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts WOtech::RECT into D2D1_RECT_F. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="rect">	Represents a rectangle defined by the coordinates of the upper-left corner (left, top) and the coordinates of the lower-right corner (right, bottom). </param>
		///
		/// <returns>	D2D1_RECT_F, Represents a rectangle defined by the coordinates of the upper-left corner (left, top) and the coordinates of the lower-right corner (right, bottom). </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline D2D1_RECT_F wrapRect(_In_ WOtech::RECT rect)
		{
			return D2D1::RectF(rect.X, rect.Y, rect.Width, rect.Height);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts Windows::Foundation::Size. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="size">	Represents number values that specify a height and width. </param>
		///
		/// <returns>	D2D1_SIZE_F, Stores an ordered pair of floats, typically the width and height of a rectangle. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline D2D1_SIZE_F wrapSize(_In_ Windows::Foundation::Size size)
		{
			return D2D1::SizeF(size.Width, size.Height);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts Windows::Foundation::Point. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="point"> Represents x - and y - coordinate values that define a point in a two - dimensional plane.. </param>
		///
		/// <returns>	D2D1_POINT_2F, Represents an x-coordinate and y-coordinate pair in two-dimensional space. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline D2D1_POINT_2F wrapPoint(_In_ Windows::Foundation::Point point)
		{
			return D2D1::Point2F(point.X, point.Y);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts FONT_STYLE. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="fontstyle"> Represents the style of a font face as normal, italic, or oblique. </param>
		///
		/// <returns>	A DWRITE_FONT_STYLE. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DWRITE_FONT_STYLE wraptFontStyle(_In_ FONT_STYLE fontstyle)
		{
			switch (fontstyle)
			{
			case FONT_STYLE::FONT_STYLE_ITALIC:
				return DWRITE_FONT_STYLE_ITALIC;
				break;
			case FONT_STYLE::FONT_STYLE_NORMAL:
				return DWRITE_FONT_STYLE_NORMAL;
				break;
			case FONT_STYLE::FONT_STYLE_OBLIQUE:
				return DWRITE_FONT_STYLE_OBLIQUE;
				break;
			default:
				return DWRITE_FONT_STYLE_NORMAL;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts BITMAP_INTERPOLATION_MODE. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="bitmapinterpolationmode"> Specifies the algorithm that is used when images are scaled or rotated. </param>
		///
		/// <returns>	A D2D1_BITMAP_INTERPOLATION_MODE. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline D2D1_BITMAP_INTERPOLATION_MODE wrapBitmapInterpolationMode(_In_ const BITMAP_INTERPOLATION_MODE bitmapinterpolationmode)
		{
			switch (bitmapinterpolationmode)
			{
			case BITMAP_INTERPOLATION_MODE::BITMAP_INTERPOLATION_MODE_LINEAR:
				return D2D1_BITMAP_INTERPOLATION_MODE_LINEAR;
				break;
			case BITMAP_INTERPOLATION_MODE::BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR:
				return D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
				break;
			case BITMAP_INTERPOLATION_MODE::BITMAP_INTERPOLATION_MODE_FORCE_DWORD:
				return D2D1_BITMAP_INTERPOLATION_MODE_FORCE_DWORD;
				break;
			default:
				return D2D1_BITMAP_INTERPOLATION_MODE_LINEAR;
				break;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts FIGURE_BEGIN. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="figurebegin">	Indicates whether a specific figure is filled or hollow.  </param>
		///
		/// <returns>	A D2D1_FIGURE_BEGIN. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline D2D1_FIGURE_BEGIN wrapFigureBegin(_In_ FIGURE_BEGIN figurebegin)
		{
			switch (figurebegin)
			{
			case WOtech::FIGURE_BEGIN::FIGURE_BEGIN_FILLED:
				return D2D1_FIGURE_BEGIN::D2D1_FIGURE_BEGIN_FILLED;
				break;
			case WOtech::FIGURE_BEGIN::FIGURE_BEGIN_HALLOW:
				return D2D1_FIGURE_BEGIN::D2D1_FIGURE_BEGIN_HOLLOW;
				break;
			default:
				return D2D1_FIGURE_BEGIN();
				break;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts FIGURE_END. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="figureend">	Indicates whether a specific figure is open or closed.  </param>
		///
		/// <returns>	A D2D1_FIGURE_END. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline D2D1_FIGURE_END wrapFigureEnd(_In_ FIGURE_END figureend)
		{
			switch (figureend)
			{
			case WOtech::FIGURE_END::FIGURE_END_OPEN:
				return D2D1_FIGURE_END::D2D1_FIGURE_END_OPEN;
				break;
			case WOtech::FIGURE_END::FIGURE_END_CLOSED:
				return D2D1_FIGURE_END::D2D1_FIGURE_END_CLOSED;
				break;
			default:
				return D2D1_FIGURE_END();
				break;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts BEZIER_SEGMENT. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="beziersegment">	Represents a cubic bezier segment drawn between two points. </param>
		///
		/// <returns>	A D2D1_BEZIER_SEGMENT. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline D2D1_BEZIER_SEGMENT wrapBezierSegment(_In_ BEZIER_SEGMENT beziersegment)
		{
			return D2D1::BezierSegment(wrapPoint(beziersegment.point1), wrapPoint(beziersegment.point2), wrapPoint(beziersegment.point3));
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts SWEEP_DIRECTION. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="sweepdirection">	Defines the direction that an elliptical arc is drawn.  </param>
		///
		/// <returns>	A D2D1_SWEEP_DIRECTION. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline D2D1_SWEEP_DIRECTION wrapSweepDirection(_In_ SWEEP_DIRECTION sweepdirection)
		{
			switch (sweepdirection)
			{
			case WOtech::SWEEP_DIRECTION::D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE:
				return D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE;
				break;
			case WOtech::SWEEP_DIRECTION::D2D1_SWEEP_DIRECTION_CLOCKWISE:
				return D2D1_SWEEP_DIRECTION_CLOCKWISE;
				break;
			default:
				return D2D1_SWEEP_DIRECTION();
				break;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts ARC_SIZE. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="arcsize">	Specifies whether an arc should be greater than 180 degrees. </param>
		///
		/// <returns>	A D2D1_ARC_SIZE. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline D2D1_ARC_SIZE wrapArcSize(_In_ ARC_SIZE arcsize)
		{
			switch (arcsize)
			{
			case WOtech::ARC_SIZE::D2D1_ARC_SIZE_SMALL:
				return D2D1_ARC_SIZE_SMALL;
				break;
			case WOtech::ARC_SIZE::D2D1_ARC_SIZE_LARGE:
				return D2D1_ARC_SIZE_LARGE;
				break;
			default:
				return D2D1_ARC_SIZE();
				break;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts ARC_SEGMENT. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="arcsegment">	Describes an elliptical arc between two points. </param>
		///
		/// <returns>	A D2D1_ARC_SEGMENT. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline D2D1_ARC_SEGMENT wrapArcSegment(_In_ ARC_SEGMENT arcsegment)
		{
			return D2D1::ArcSegment(wrapPoint(arcsegment.point), wrapSize(arcsegment.size), arcsegment.rotationAngle, wrapSweepDirection(arcsegment.sweepDirection), wrapArcSize(arcsegment.arcSize));
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts FORMAT_DXGI. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="formatDXGI">	Resource data formats, including fully-typed and typeless formats. A list of modifiers at the bottom of the page more fully describes each format type. </param>
		///
		/// <returns>	A DXGI_FORMAT. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DXGI_FORMAT wrapDXGIFormat(_In_ FORMAT_DXGI formatDXGI)
		{
			switch (formatDXGI)
			{
			case FORMAT_DXGI::FORMAT_UNKNOWN:
				return DXGI_FORMAT_UNKNOWN;
				break;
			case FORMAT_DXGI::FORMAT_R32G32B32A32_TYPELESS:
				return DXGI_FORMAT_R32G32B32A32_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_R32G32B32A32_FLOAT:
				return DXGI_FORMAT_R32G32B32A32_FLOAT;
				break;
			case FORMAT_DXGI::FORMAT_R32G32B32A32_UINT:
				return DXGI_FORMAT_R32G32B32A32_UINT;
				break;
			case FORMAT_DXGI::FORMAT_R32G32B32A32_SINT:
				return DXGI_FORMAT_R32G32B32A32_SINT;
				break;
			case FORMAT_DXGI::FORMAT_R32G32B32_TYPELESS:
				return DXGI_FORMAT_R32G32B32_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_R32G32B32_FLOAT:
				return DXGI_FORMAT_R32G32B32_FLOAT;
				break;
			case FORMAT_DXGI::FORMAT_R32G32B32_UINT:
				return DXGI_FORMAT_R32G32B32_UINT;
				break;
			case FORMAT_DXGI::FORMAT_R32G32B32_SINT:
				return DXGI_FORMAT_R32G32B32_SINT;
				break;
			case FORMAT_DXGI::FORMAT_R16G16B16A16_TYPELESS:
				return DXGI_FORMAT_R16G16B16A16_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_R16G16B16A16_FLOAT:
				return DXGI_FORMAT_R16G16B16A16_FLOAT;
				break;
			case FORMAT_DXGI::FORMAT_R16G16B16A16_UNORM:
				return DXGI_FORMAT_R16G16B16A16_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_R16G16B16A16_UINT:
				return DXGI_FORMAT_R16G16B16A16_UINT;
				break;
			case FORMAT_DXGI::FORMAT_R16G16B16A16_SNORM:
				return DXGI_FORMAT_R16G16B16A16_SNORM;
				break;
			case FORMAT_DXGI::FORMAT_R16G16B16A16_SINT:
				return DXGI_FORMAT_R16G16B16A16_SINT;
				break;
			case FORMAT_DXGI::FORMAT_R32G32_TYPELESS:
				return DXGI_FORMAT_R32G32_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_R32G32_FLOAT:
				return DXGI_FORMAT_R32G32_FLOAT;
				break;
			case FORMAT_DXGI::FORMAT_R32G32_UINT:
				return DXGI_FORMAT_R32G32_UINT;
				break;
			case FORMAT_DXGI::FORMAT_R32G32_SINT:
				return DXGI_FORMAT_R32G32_SINT;
				break;
			case FORMAT_DXGI::FORMAT_R32G8X24_TYPELESS:
				return DXGI_FORMAT_R32G8X24_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_D32_FLOAT_S8X24_UINT:
				return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
				break;
			case FORMAT_DXGI::FORMAT_R32_FLOAT_X8X24_TYPELESS:
				return DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_X32_TYPELESS_G8X24_UINT:
				return DXGI_FORMAT_X32_TYPELESS_G8X24_UINT;
				break;
			case FORMAT_DXGI::FORMAT_R10G10B10A2_TYPELESS:
				return DXGI_FORMAT_R10G10B10A2_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_R10G10B10A2_UNORM:
				return DXGI_FORMAT_R10G10B10A2_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_R10G10B10A2_UINT:
				return DXGI_FORMAT_R10G10B10A2_UINT;
				break;
			case FORMAT_DXGI::FORMAT_R11G11B10_FLOAT:
				return DXGI_FORMAT_R11G11B10_FLOAT;
				break;
			case FORMAT_DXGI::FORMAT_R8G8B8A8_TYPELESS:
				return DXGI_FORMAT_R8G8B8A8_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_R8G8B8A8_UNORM:
				return DXGI_FORMAT_R8G8B8A8_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_R8G8B8A8_UNORM_SRGB:
				return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
				break;
			case FORMAT_DXGI::FORMAT_R8G8B8A8_UINT:
				return DXGI_FORMAT_R8G8B8A8_UINT;
				break;
			case FORMAT_DXGI::FORMAT_R8G8B8A8_SNORM:
				return DXGI_FORMAT_R8G8B8A8_SNORM;
				break;
			case FORMAT_DXGI::FORMAT_R8G8B8A8_SINT:
				return DXGI_FORMAT_R8G8B8A8_SINT;
				break;
			case FORMAT_DXGI::FORMAT_R16G16_TYPELESS:
				return DXGI_FORMAT_R16G16_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_R16G16_FLOAT:
				return DXGI_FORMAT_R16G16_FLOAT;
				break;
			case FORMAT_DXGI::FORMAT_R16G16_UNORM:
				return DXGI_FORMAT_R16G16_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_R16G16_UINT:
				return DXGI_FORMAT_R16G16_UINT;
				break;
			case FORMAT_DXGI::FORMAT_R16G16_SNORM:
				return DXGI_FORMAT_R16G16_SNORM;
				break;
			case FORMAT_DXGI::FORMAT_R16G16_SINT:
				return DXGI_FORMAT_R16G16_SINT;
				break;
			case FORMAT_DXGI::FORMAT_R32_TYPELESS:
				return DXGI_FORMAT_R32_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_D32_FLOAT:
				return DXGI_FORMAT_D32_FLOAT;
				break;
			case FORMAT_DXGI::FORMAT_R32_FLOAT:
				return DXGI_FORMAT_R32_FLOAT;
				break;
			case FORMAT_DXGI::FORMAT_R32_UINT:
				return DXGI_FORMAT_R32_UINT;
				break;
			case FORMAT_DXGI::FORMAT_R32_SINT:
				return DXGI_FORMAT_R32_SINT;
				break;
			case FORMAT_DXGI::FORMAT_R24G8_TYPELESS:
				return DXGI_FORMAT_R24G8_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_D24_UNORM_S8_UINT:
				return DXGI_FORMAT_D24_UNORM_S8_UINT;
				break;
			case FORMAT_DXGI::FORMAT_R24_UNORM_X8_TYPELESS:
				return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_X24_TYPELESS_G8_UINT:
				return DXGI_FORMAT_X24_TYPELESS_G8_UINT;
				break;
			case FORMAT_DXGI::FORMAT_R8G8_TYPELESS:
				return DXGI_FORMAT_R8G8_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_R8G8_UNORM:
				return DXGI_FORMAT_R8G8_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_R8G8_UINT:
				return DXGI_FORMAT_R8G8_UINT;
				break;
			case FORMAT_DXGI::FORMAT_R8G8_SNORM:
				return DXGI_FORMAT_R8G8_SNORM;
				break;
			case FORMAT_DXGI::FORMAT_R8G8_SINT:
				return DXGI_FORMAT_R8G8_SINT;
				break;
			case FORMAT_DXGI::FORMAT_R16_TYPELESS:
				return DXGI_FORMAT_R16_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_R16_FLOAT:
				return DXGI_FORMAT_R16_FLOAT;
				break;
			case FORMAT_DXGI::FORMAT_D16_UNORM:
				return DXGI_FORMAT_D16_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_R16_UNORM:
				return DXGI_FORMAT_R16_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_R16_UINT:
				return DXGI_FORMAT_R16_UINT;
				break;
			case FORMAT_DXGI::FORMAT_R16_SNORM:
				return DXGI_FORMAT_R16_SNORM;
				break;
			case FORMAT_DXGI::FORMAT_R16_SINT:
				return DXGI_FORMAT_R16_SINT;
				break;
			case FORMAT_DXGI::FORMAT_R8_TYPELESS:
				return DXGI_FORMAT_R8_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_R8_UNORM:
				return DXGI_FORMAT_R8_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_R8_UINT:
				return DXGI_FORMAT_R8_UINT;
				break;
			case FORMAT_DXGI::FORMAT_R8_SNORM:
				return DXGI_FORMAT_R8_SNORM;
				break;
			case FORMAT_DXGI::FORMAT_R8_SINT:
				return DXGI_FORMAT_R8_SINT;
				break;
			case FORMAT_DXGI::FORMAT_A8_UNORM:
				return DXGI_FORMAT_A8_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_R1_UNORM:
				return DXGI_FORMAT_R1_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_R9G9B9E5_SHAREDEXP:
				return DXGI_FORMAT_R9G9B9E5_SHAREDEXP;
				break;
			case FORMAT_DXGI::FORMAT_R8G8_B8G8_UNORM:
				return DXGI_FORMAT_R8G8_B8G8_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_G8R8_G8B8_UNORM:
				return DXGI_FORMAT_G8R8_G8B8_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_BC1_TYPELESS:
				return DXGI_FORMAT_BC1_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_BC1_UNORM:
				return DXGI_FORMAT_BC1_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_BC1_UNORM_SRGB:
				return DXGI_FORMAT_BC1_UNORM_SRGB;
				break;
			case FORMAT_DXGI::FORMAT_BC2_TYPELESS:
				return DXGI_FORMAT_BC2_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_BC2_UNORM:
				return DXGI_FORMAT_BC2_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_BC2_UNORM_SRGB:
				return DXGI_FORMAT_BC2_UNORM_SRGB;
				break;
			case FORMAT_DXGI::FORMAT_BC3_TYPELESS:
				return DXGI_FORMAT_BC3_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_BC3_UNORM:
				return DXGI_FORMAT_BC3_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_BC3_UNORM_SRGB:
				return DXGI_FORMAT_BC3_UNORM_SRGB;
				break;
			case FORMAT_DXGI::FORMAT_BC4_TYPELESS:
				return DXGI_FORMAT_BC4_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_BC4_UNORM:
				return DXGI_FORMAT_BC4_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_BC4_SNORM:
				return DXGI_FORMAT_BC4_SNORM;
				break;
			case FORMAT_DXGI::FORMAT_BC5_TYPELESS:
				return DXGI_FORMAT_BC5_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_BC5_UNORM:
				return DXGI_FORMAT_BC5_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_BC5_SNORM:
				return DXGI_FORMAT_BC5_SNORM;
				break;
			case FORMAT_DXGI::FORMAT_B5G6R5_UNORM:
				return DXGI_FORMAT_B5G6R5_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_B5G5R5A1_UNORM:
				return DXGI_FORMAT_B5G5R5A1_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_B8G8R8A8_UNORM:
				return DXGI_FORMAT_B8G8R8A8_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_B8G8R8X8_UNORM:
				return DXGI_FORMAT_B8G8R8X8_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
				return DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_B8G8R8A8_TYPELESS:
				return DXGI_FORMAT_B8G8R8A8_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_B8G8R8A8_UNORM_SRGB:
				return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
				break;
			case FORMAT_DXGI::FORMAT_B8G8R8X8_TYPELESS:
				return DXGI_FORMAT_B8G8R8X8_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_B8G8R8X8_UNORM_SRGB:
				return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
				break;
			case FORMAT_DXGI::FORMAT_BC6H_TYPELESS:
				return DXGI_FORMAT_BC6H_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_BC6H_UF16:
				return DXGI_FORMAT_BC6H_UF16;
				break;
			case FORMAT_DXGI::FORMAT_BC6H_SF16:
				return DXGI_FORMAT_BC6H_SF16;
				break;
			case FORMAT_DXGI::FORMAT_BC7_TYPELESS:
				return DXGI_FORMAT_BC7_TYPELESS;
				break;
			case FORMAT_DXGI::FORMAT_BC7_UNORM:
				return DXGI_FORMAT_BC7_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_BC7_UNORM_SRGB:
				return DXGI_FORMAT_BC7_UNORM_SRGB;
				break;
			case FORMAT_DXGI::FORMAT_AYUV:
				return DXGI_FORMAT_AYUV;
				break;
			case FORMAT_DXGI::FORMAT_Y410:
				return DXGI_FORMAT_Y410;
				break;
			case FORMAT_DXGI::FORMAT_Y416:
				return DXGI_FORMAT_Y416;
				break;
			case FORMAT_DXGI::FORMAT_NV12:
				return DXGI_FORMAT_NV12;
				break;
			case FORMAT_DXGI::FORMAT_P010:
				return DXGI_FORMAT_P010;
				break;
			case FORMAT_DXGI::FORMAT_P016:
				return DXGI_FORMAT_P016;
				break;
			case FORMAT_DXGI::FORMAT_420_OPAQUE:
				return DXGI_FORMAT_420_OPAQUE;
				break;
			case FORMAT_DXGI::FORMAT_YUY2:
				return DXGI_FORMAT_YUY2;
				break;
			case FORMAT_DXGI::FORMAT_Y210:
				return DXGI_FORMAT_Y210;
				break;
			case FORMAT_DXGI::FORMAT_Y216:
				return DXGI_FORMAT_Y216;
				break;
			case FORMAT_DXGI::FORMAT_NV11:
				return DXGI_FORMAT_NV11;
				break;
			case FORMAT_DXGI::FORMAT_AI44:
				return DXGI_FORMAT_AI44;
				break;
			case FORMAT_DXGI::FORMAT_IA44:
				return DXGI_FORMAT_IA44;
				break;
			case FORMAT_DXGI::FORMAT_P8:
				return DXGI_FORMAT_P8;
				break;
			case FORMAT_DXGI::FORMAT_A8P8:
				return DXGI_FORMAT_A8P8;
				break;
			case FORMAT_DXGI::FORMAT_B4G4R4A4_UNORM:
				return DXGI_FORMAT_B4G4R4A4_UNORM;
				break;
			case FORMAT_DXGI::FORMAT_P208:
				return DXGI_FORMAT_P208;
				break;
			case FORMAT_DXGI::FORMAT_V208:
				return DXGI_FORMAT_V208;
				break;
			case FORMAT_DXGI::FORMAT_V408:
				return DXGI_FORMAT_V408;
				break;
			case FORMAT_DXGI::FORMAT_FORCE_UINT:
				return DXGI_FORMAT_FORCE_UINT;
				break;
			default:
				return DXGI_FORMAT_UNKNOWN;
				break;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts MODE_ROTATION_DXGI. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="moderotationDXGI">	Flags that indicate how the back buffers should be rotated to fit the physical rotation of a monitor. </param>
		///
		/// <returns>	A DXGI_MODE_ROTATION. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DXGI_MODE_ROTATION wrapDXGIModeRotation(_In_ MODE_ROTATION_DXGI moderotationDXGI)
		{
			switch (moderotationDXGI)
			{
			case WOtech::MODE_ROTATION_DXGI::DXGI_MODE_ROTATION_UNSPECIFIED:
				return DXGI_MODE_ROTATION::DXGI_MODE_ROTATION_UNSPECIFIED;
				break;
			case WOtech::MODE_ROTATION_DXGI::DXGI_MODE_ROTATION_IDENTITY:
				return DXGI_MODE_ROTATION::DXGI_MODE_ROTATION_IDENTITY;
				break;
			case WOtech::MODE_ROTATION_DXGI::DXGI_MODE_ROTATION_ROTATE90:
				return DXGI_MODE_ROTATION::DXGI_MODE_ROTATION_ROTATE90;
				break;
			case WOtech::MODE_ROTATION_DXGI::DXGI_MODE_ROTATION_ROTATE180:
				return DXGI_MODE_ROTATION::DXGI_MODE_ROTATION_ROTATE180;
				break;
			case WOtech::MODE_ROTATION_DXGI::DXGI_MODE_ROTATION_ROTATE270:
				return DXGI_MODE_ROTATION::DXGI_MODE_ROTATION_ROTATE270;
				break;
			default:
				return DXGI_MODE_ROTATION::DXGI_MODE_ROTATION_UNSPECIFIED;
				break;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts MODE_SCANLINE_ORDER_DXGI. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="modescanlineorderDXGI">	Flags indicating the method the raster uses to create an image on a surface.. </param>
		///
		/// <returns>	A DXGI_MODE_SCANLINE_ORDER. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DXGI_MODE_SCANLINE_ORDER warpDXGIModeScanlineOrder(_In_ MODE_SCANLINE_ORDER_DXGI modescanlineorderDXGI)
		{
			switch (modescanlineorderDXGI)
			{
			case WOtech::MODE_SCANLINE_ORDER_DXGI::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED:
				return DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
				break;
			case WOtech::MODE_SCANLINE_ORDER_DXGI::DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE:
				return DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
				break;
			case WOtech::MODE_SCANLINE_ORDER_DXGI::DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST:
				return DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST;
				break;
			case WOtech::MODE_SCANLINE_ORDER_DXGI::DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST:
				return DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST;
				break;
			default:
				return DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
				break;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts MODE_SCALING_DXGI. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="modescalingmodeDXGI">	The modescalingmode dxgi. </param>
		///
		/// <returns>	A DXGI_MODE_SCALING. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DXGI_MODE_SCALING warpDXGIModeScaling(_In_ MODE_SCALING_DXGI modescalingmodeDXGI)
		{
			switch (modescalingmodeDXGI)
			{
			case WOtech::MODE_SCALING_DXGI::DXGI_MODE_SCALING_UNSPECIFIED:
				return DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;
				break;
			case WOtech::MODE_SCALING_DXGI::DXGI_MODE_SCALING_CENTERED:
				return DXGI_MODE_SCALING::DXGI_MODE_SCALING_CENTERED;
				break;
			case WOtech::MODE_SCALING_DXGI::DXGI_MODE_SCALING_STRETCHED:
				return DXGI_MODE_SCALING::DXGI_MODE_SCALING_STRETCHED;
				break;
			default:
				return DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;
				break;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts CLEAR_FLAG. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="clearflag">	The clearflag. </param>
		///
		/// <returns>	A D3D11_CLEAR_FLAG. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline D3D11_CLEAR_FLAG wrapClearFlag(_In_ CLEAR_FLAG clearflag)
		{
			switch (clearflag)
			{
			case CLEAR_FLAG::CLEAR_DEPTH:
				return D3D11_CLEAR_DEPTH;
				break;
			case CLEAR_FLAG::CLEAR_STENCIL:
				return D3D11_CLEAR_STENCIL;
				break;
			default:
				return D3D11_CLEAR_DEPTH;
				break;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts INPUT_CLASSIFICATION. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="inputclassification">	The inputclassification. </param>
		///
		/// <returns>	A D3D11_INPUT_CLASSIFICATION. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline D3D11_INPUT_CLASSIFICATION wrapInputClassification(_In_ INPUT_CLASSIFICATION inputclassification)
		{
			switch (inputclassification)
			{
			case INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA:
				return D3D11_INPUT_PER_VERTEX_DATA;
				break;
			case INPUT_CLASSIFICATION::D3D11_INPUT_PER_INSTANCE_DATA:
				return D3D11_INPUT_PER_INSTANCE_DATA;
				break;
			default:
				return D3D11_INPUT_PER_VERTEX_DATA;
				break;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts Platform::Array<INPUT_ELEMENT_DESC>^ . </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="inputelementdesc">	The inputelementdesc. </param>
		///
		/// <returns>	Null if it fails, else a pointer to a D3D11_INPUT_ELEMENT_DESC. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline D3D11_INPUT_ELEMENT_DESC* wrapInputElementDesc(_In_ const Platform::Array<INPUT_ELEMENT_DESC>^ inputelementdesc)
		{
			const UINT size = inputelementdesc->Length;

			D3D11_INPUT_ELEMENT_DESC* InputElementDESC = new D3D11_INPUT_ELEMENT_DESC[size];

			for (unsigned int i = 0; i < size; i++)
			{
				InputElementDESC[i].AlignedByteOffset = static_cast<UINT>(inputelementdesc[i].AlignedByteOffset);// DATA type!!!! buffer OVERFLOW
				InputElementDESC[i].Format = wrapDXGIFormat(inputelementdesc[i].Format);
				InputElementDESC[i].InputSlot = inputelementdesc[i].InputSlot;
				InputElementDESC[i].InputSlotClass = wrapInputClassification(inputelementdesc[i].InputSlotClass);
				InputElementDESC[i].InstanceDataStepRate = inputelementdesc[i].InstanceDataStepRate;
				InputElementDESC[i].SemanticIndex = inputelementdesc[i].SemanticIndex;

				std::string semanticName = WOtech::utf8_encode(inputelementdesc[i].SemanticName->Data());
				InputElementDESC[i].SemanticName = semanticName.data();
			}

			return InputElementDESC;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts Windows::Foundation::Numerics::float4x4 to DirectX::XMFLOAT4X4. </summary>
		///
		/// <remarks>	WraithOne, 02.09.2017. </remarks>
		///
		/// <param name="matrix">	A 4x4 matrix, used for 3D transforms. </param>
		///
		/// <returns>	DirectX::XMFLOAT4X4. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DirectX::XMFLOAT4X4 wrapFloat4x4(_In_ Windows::Foundation::Numerics::float4x4 matrix)
		{
			return DirectX::XMFLOAT4X4(matrix.m11, matrix.m12, matrix.m13, matrix.m14,
				matrix.m21, matrix.m22, matrix.m23, matrix.m24,
				matrix.m31, matrix.m32, matrix.m33, matrix.m34,
				matrix.m41, matrix.m42, matrix.m43, matrix.m44);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts DirectX::XMFLOAT4X4 to WOtech::FLAOT4x4 </summary>
		///
		/// <remarks>	WraithOne, 02.09.2017. </remarks>
		///
		/// <param name="matrix">	A 4*4 floating point matrix. </param>
		///
		/// <returns>	A 4x4 matrix, used for 3D transforms. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline WOtech::FLOAT4x4 wrapXMFloat4x4(_In_ DirectX::XMFLOAT4X4 matrix)
		{
			WOtech::FLOAT4x4 temp =
			{
				matrix._11, matrix._12, matrix._13, matrix._14,
				matrix._21, matrix._22, matrix._23, matrix._24,
				matrix._31, matrix._32, matrix._33, matrix._34,
				matrix._41, matrix._42, matrix._43, matrix._44
			};

			return temp;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts WOtech::FLOAT4x4 to DirectX::XMFLOAT4X4 </summary>
		///
		/// <remarks>	WraithOne, 02.09.2017. </remarks>
		///
		/// <param name="matrix">	A 4*4 floating point matrix. </param>
		///
		/// <returns>	A 4x4 matrix, used for 3D transforms. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DirectX::XMFLOAT4X4 wrapWOFloat4x4(_In_ WOtech::FLOAT4x4 matrix)
		{
			DirectX::XMFLOAT4X4 temp =
			{
				matrix.M11, matrix.M12, matrix.M13, matrix.M14,
				matrix.M21, matrix.M22, matrix.M23, matrix.M24,
				matrix.M31, matrix.M32, matrix.M33, matrix.M34,
				matrix.M41, matrix.M42, matrix.M43, matrix.M44
			};

			return temp;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts WOtech::FLOAT2 to DirectX::XMVECTOR </summary>
		///
		/// <remarks>	WraithOne, 02.09.2017. </remarks>
		///
		/// <param name="matrix">	A 4*4 floating point matrix. </param>
		///
		/// <returns>	A 4x4 matrix, used for 3D transforms. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DirectX::XMVECTOR XMLoadFloat2(_In_ WOtech::FLOAT2 vector)
		{
			DirectX::XMFLOAT2 output = { vector.X, vector.Y };

			return DirectX::XMLoadFloat2(&output);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts WOtech::FLOAT3 to DirectX::XMVECTOR </summary>
		///
		/// <remarks>	WraithOne, 02.09.2017. </remarks>
		///
		/// <param name="matrix">	A 4*4 floating point matrix. </param>
		///
		/// <returns>	A 4x4 matrix, used for 3D transforms. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DirectX::XMVECTOR XMLoadFloat3(_In_ WOtech::FLOAT3 vector)
		{
			DirectX::XMFLOAT3 output = { vector.X, vector.Y , vector.Z };

			return DirectX::XMLoadFloat3(&output);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts WOtech::FLOAT4 to DirectX::XMVECTOR </summary>
		///
		/// <remarks>	WraithOne, 02.09.2017. </remarks>
		///
		/// <param name="matrix">	WOtech::FLOAT4. </param>
		///
		/// <returns>	DirectX::XMVECTOR. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DirectX::XMVECTOR XMLoadFloat4(_In_ WOtech::FLOAT4 vector)
		{
			DirectX::XMFLOAT4 output = { vector.X, vector.Y , vector.Z , vector.W };

			return DirectX::XMLoadFloat4(&output);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts Wotech::XMFLOAT4x4 to DirectX::XMMATRIX </summary>
		///
		/// <remarks>	WraithOne, 02.09.2017. </remarks>
		///
		/// <param name="matrix">	A 4*4 floating point matrix. </param>
		///
		/// <returns>	A 4x4 matrix, used for 3D transforms. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DirectX::XMMATRIX XMLoadFloat4x4(_In_ WOtech::FLOAT4x4 matrix)
		{
			DirectX::XMFLOAT4X4 output =
			{
				matrix.M11, matrix.M12, matrix.M13, matrix.M14,
				matrix.M21, matrix.M22, matrix.M23, matrix.M24,
				matrix.M31, matrix.M32, matrix.M33, matrix.M34,
				matrix.M41, matrix.M42, matrix.M43, matrix.M44
			};

			return DirectX::XMLoadFloat4x4(&output);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts DirectX::XMMATRIX to WOtech::FLOAT4x4. </summary>
		///
		/// <remarks>	WraithOne, 14.10.2017. </remarks>
		///
		/// <param name="matrix">	DirectX::XMMATRIX. </param>
		///
		/// <returns>	WOtech::FLOAT4x4 </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline WOtech::FLOAT4x4 wrapXMMATRIX(_In_ const DirectX::XMMATRIX& matrix)
		{
			DirectX::XMFLOAT4X4 out;
			DirectX::XMStoreFloat4x4(&out, matrix);
			return wrapXMFloat4x4(out);
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts WOtech::AUDIO_PROCESSOR to XAUDIO2_PROCESSOR. </summary>
		///
		/// <remarks>	WraithOne, 06.10.2017. </remarks>
		///
		/// <param name="processor">	WOtech::AUDIO_PROCESSOR. </param>
		///
		/// <returns>	XAUDIO2_PROCESSOR </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline XAUDIO2_PROCESSOR wrapAUDIO_PROCESSOR(_In_ WOtech::AUDIO_PROCESSOR processor)
		{
			switch (processor)
			{
			case WOtech::AUDIO_PROCESSOR::PROCESSOR1:
				return Processor1;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR2:
				return Processor2;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR3:
				return Processor3;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR4:
				return Processor4;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR5:
				return Processor5;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR6:
				return Processor6;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR7:
				return Processor7;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR8:
				return Processor8;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR9:
				return Processor9;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR10:
				return Processor10;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR11:
				return Processor11;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR12:
				return Processor12;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR13:
				return Processor13;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR14:
				return Processor14;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR15:
				return Processor15;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR16:
				return Processor16;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR17:
				return Processor17;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR18:
				return Processor18;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR19:
				return Processor19;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR20:
				return Processor20;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR21:
				return Processor21;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR22:
				return Processor22;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR23:
				return Processor23;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR24:
				return Processor24;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR25:
				return Processor25;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR26:
				return Processor26;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR27:
				return Processor27;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR28:
				return Processor28;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR29:
				return Processor29;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR30:
				return Processor30;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR31:
				return Processor31;
				break;
			case WOtech::AUDIO_PROCESSOR::PROCESSOR32:
				return Processor32;
				break;
			case WOtech::AUDIO_PROCESSOR::ANY_PROCESSOR:
				return XAUDIO2_ANY_PROCESSOR;
				break;
			case WOtech::AUDIO_PROCESSOR::DEFAULT_PROCESSOR:
				return XAUDIO2_DEFAULT_PROCESSOR;
				break;
			default:
				return XAUDIO2_DEFAULT_PROCESSOR;
				break;
			}
		}
	}
}
#endif