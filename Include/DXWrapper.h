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
///			Edited:		2$.08.2017
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

namespace WOtech
{
	namespace DXWrapper
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Values that represent Mouses virtual keys. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		public enum class VirtualKey_Mouse
		{
			/// <summary>	Left mouse button. </summary>
			LeftButton,
			/// <summary>	Right mouse button. </summary>
			RightButton,
			/// <summary>	Middle mouse button. </summary>
			MiddleButton,
			/// <summary>	X1 mouse button. </summary>
			X1Button,
			/// <summary>	X2 mouse button. </summary>
			X2Button
		};

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

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Represents a rectangle defined by the coordinates of the upper-left corner (left, top) and the coordinates of the lower-right corner (right, bottom) </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		public value class RECT
		{
		public:
			/// <summary>	The x-coordinate of the upper-left corner of the rectangle. < / summary>
			float X;
			/// <summary>	The y-coordinate of the upper-left corner of the rectangle. < / summary>
			float Y;
			/// <summary>	The x-coordinate of the lower-right corner of the rectangle. < / summary>
			float Width;
			/// <summary>	The y-coordinate of the lower-right corner of the rectangle. < / summary>
			float Height;
		};

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
		/// <summary>	Converts WOtech::DXWrapper::RECT into D2D1_RECT_F. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="rect">	Represents a rectangle defined by the coordinates of the upper-left corner (left, top) and the coordinates of the lower-right corner (right, bottom). </param>
		///
		/// <returns>	D2D1_RECT_F, Represents a rectangle defined by the coordinates of the upper-left corner (left, top) and the coordinates of the lower-right corner (right, bottom). </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline D2D1_RECT_F wrapRect(_In_ WOtech::DXWrapper::RECT rect)
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
			case WOtech::DXWrapper::FIGURE_BEGIN::FIGURE_BEGIN_FILLED:
				return D2D1_FIGURE_BEGIN::D2D1_FIGURE_BEGIN_FILLED;
				break;
			case WOtech::DXWrapper::FIGURE_BEGIN::FIGURE_BEGIN_HALLOW:
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
			case WOtech::DXWrapper::FIGURE_END::FIGURE_END_OPEN:
				return D2D1_FIGURE_END::D2D1_FIGURE_END_OPEN;
				break;
			case WOtech::DXWrapper::FIGURE_END::FIGURE_END_CLOSED:
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
			case WOtech::DXWrapper::SWEEP_DIRECTION::D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE:
				return D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE;
				break;
			case WOtech::DXWrapper::SWEEP_DIRECTION::D2D1_SWEEP_DIRECTION_CLOCKWISE:
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
			case WOtech::DXWrapper::ARC_SIZE::D2D1_ARC_SIZE_SMALL:
				return D2D1_ARC_SIZE_SMALL;
				break;
			case WOtech::DXWrapper::ARC_SIZE::D2D1_ARC_SIZE_LARGE:
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
		/// <summary>	Resource data formats, including fully-typed and typeless formats. A list of modifiers at the bottom of the page more fully describes each format type.  </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		public enum class FORMAT_DXGI {
			FORMAT_UNKNOWN,
			FORMAT_R32G32B32A32_TYPELESS,
			FORMAT_R32G32B32A32_FLOAT,
			FORMAT_R32G32B32A32_UINT,
			FORMAT_R32G32B32A32_SINT,
			FORMAT_R32G32B32_TYPELESS,
			FORMAT_R32G32B32_FLOAT,
			FORMAT_R32G32B32_UINT,
			FORMAT_R32G32B32_SINT,
			FORMAT_R16G16B16A16_TYPELESS,
			FORMAT_R16G16B16A16_FLOAT,
			FORMAT_R16G16B16A16_UNORM,
			FORMAT_R16G16B16A16_UINT,
			FORMAT_R16G16B16A16_SNORM,
			FORMAT_R16G16B16A16_SINT,
			FORMAT_R32G32_TYPELESS,
			FORMAT_R32G32_FLOAT,
			FORMAT_R32G32_UINT,
			FORMAT_R32G32_SINT,
			FORMAT_R32G8X24_TYPELESS,
			FORMAT_D32_FLOAT_S8X24_UINT,
			FORMAT_R32_FLOAT_X8X24_TYPELESS,
			FORMAT_X32_TYPELESS_G8X24_UINT,
			FORMAT_R10G10B10A2_TYPELESS,
			FORMAT_R10G10B10A2_UNORM,
			FORMAT_R10G10B10A2_UINT,
			FORMAT_R11G11B10_FLOAT,
			FORMAT_R8G8B8A8_TYPELESS,
			FORMAT_R8G8B8A8_UNORM,
			FORMAT_R8G8B8A8_UNORM_SRGB,
			FORMAT_R8G8B8A8_UINT,
			FORMAT_R8G8B8A8_SNORM,
			FORMAT_R8G8B8A8_SINT,
			FORMAT_R16G16_TYPELESS,
			FORMAT_R16G16_FLOAT,
			FORMAT_R16G16_UNORM,
			FORMAT_R16G16_UINT,
			FORMAT_R16G16_SNORM,
			FORMAT_R16G16_SINT,
			FORMAT_R32_TYPELESS,
			FORMAT_D32_FLOAT,
			FORMAT_R32_FLOAT,
			FORMAT_R32_UINT,
			FORMAT_R32_SINT,
			FORMAT_R24G8_TYPELESS,
			FORMAT_D24_UNORM_S8_UINT,
			FORMAT_R24_UNORM_X8_TYPELESS,
			FORMAT_X24_TYPELESS_G8_UINT,
			FORMAT_R8G8_TYPELESS,
			FORMAT_R8G8_UNORM,
			FORMAT_R8G8_UINT,
			FORMAT_R8G8_SNORM,
			FORMAT_R8G8_SINT,
			FORMAT_R16_TYPELESS,
			FORMAT_R16_FLOAT,
			FORMAT_D16_UNORM,
			FORMAT_R16_UNORM,
			FORMAT_R16_UINT,
			FORMAT_R16_SNORM,
			FORMAT_R16_SINT,
			FORMAT_R8_TYPELESS,
			FORMAT_R8_UNORM,
			FORMAT_R8_UINT,
			FORMAT_R8_SNORM,
			FORMAT_R8_SINT,
			FORMAT_A8_UNORM,
			FORMAT_R1_UNORM,
			FORMAT_R9G9B9E5_SHAREDEXP,
			FORMAT_R8G8_B8G8_UNORM,
			FORMAT_G8R8_G8B8_UNORM,
			FORMAT_BC1_TYPELESS,
			FORMAT_BC1_UNORM,
			FORMAT_BC1_UNORM_SRGB,
			FORMAT_BC2_TYPELESS,
			FORMAT_BC2_UNORM,
			FORMAT_BC2_UNORM_SRGB,
			FORMAT_BC3_TYPELESS,
			FORMAT_BC3_UNORM,
			FORMAT_BC3_UNORM_SRGB,
			FORMAT_BC4_TYPELESS,
			FORMAT_BC4_UNORM,
			FORMAT_BC4_SNORM,
			FORMAT_BC5_TYPELESS,
			FORMAT_BC5_UNORM,
			FORMAT_BC5_SNORM,
			FORMAT_B5G6R5_UNORM,
			FORMAT_B5G5R5A1_UNORM,
			FORMAT_B8G8R8A8_UNORM,
			FORMAT_B8G8R8X8_UNORM,
			FORMAT_R10G10B10_XR_BIAS_A2_UNORM,
			FORMAT_B8G8R8A8_TYPELESS,
			FORMAT_B8G8R8A8_UNORM_SRGB,
			FORMAT_B8G8R8X8_TYPELESS,
			FORMAT_B8G8R8X8_UNORM_SRGB,
			FORMAT_BC6H_TYPELESS,
			FORMAT_BC6H_UF16,
			FORMAT_BC6H_SF16,
			FORMAT_BC7_TYPELESS,
			FORMAT_BC7_UNORM,
			FORMAT_BC7_UNORM_SRGB,
			FORMAT_AYUV,
			FORMAT_Y410,
			FORMAT_Y416,
			FORMAT_NV12,
			FORMAT_P010,
			FORMAT_P016,
			FORMAT_420_OPAQUE,
			FORMAT_YUY2,
			FORMAT_Y210,
			FORMAT_Y216,
			FORMAT_NV11,
			FORMAT_AI44,
			FORMAT_IA44,
			FORMAT_P8,
			FORMAT_A8P8,
			FORMAT_B4G4R4A4_UNORM,
			FORMAT_P208,
			FORMAT_V208,
			FORMAT_V408,
			FORMAT_FORCE_UINT
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Describes a local identifier for an adapter. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		public value struct LUID_DXGI
		{
			/// <summary>	Specifies a DWORD that contains the unsigned lower numbers of the id.< / summary>
			UINT64	LowPart;
			/// <summary>	Specifies a LONG that contains the signed high numbers of the id.< / summary>
			INT64	HighPart;
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Describes an adapter (or video card) by using DXGI. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		public value struct ADAPTER_DXGI
		{
			/// <summary>	A string that contains the adapter description. On feature level 9 graphics hardware, GetDesc returns “Software Adapter” for the description string.< / summary>
			Platform::String^	Description;
			/// <summary>	The PCI ID of the hardware vendor. On feature level 9 graphics hardware, GetDesc returns zeros for the PCI ID of the hardware vendor.< / summary>
			UINT				VendorId;
			/// <summary>	The PCI ID of the hardware device. On feature level 9 graphics hardware, GetDesc returns zeros for the PCI ID of the hardware device.< / summary>
			UINT				DeviceId;
			/// <summary>	The PCI ID of the sub system. On feature level 9 graphics hardware, GetDesc returns zeros for the PCI ID of the sub system.< / summary>
			UINT				SubSysId;
			/// <summary>	The PCI ID of the revision number of the adapter. On feature level 9 graphics hardware, GetDesc returns zeros for the PCI ID of the revision number of the adapter.< / summary>
			UINT				Revision;
			/// <summary>	The number of bytes of dedicated video memory that are not shared with the CPU.< / summary>
			Platform::SizeT		DedicatedVideoMemory;
			/// <summary>	The number of bytes of dedicated system memory that are not shared with the CPU. This memory is allocated from available system memory at boot time.< / summary>
			Platform::SizeT		DedicatedSystemMemory;
			/// <summary>	The number of bytes of shared system memory. This is the maximum value of system memory that may be consumed by the adapter during operation. Any incidental memory consumed by the driver as it manages and uses video memory is additional.< / summary>
			Platform::SizeT		SharedSystemMemory;
			/// <summary>	A unique value that identifies the adapter. See LUID for a definition of the structure.< / summary>
			LUID_DXGI			AdapterLUID;
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Flags that indicate how the back buffers should be rotated to fit the physical rotation of a monitor. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		public enum class MODE_ROTATION_DXGI
		{
			/// <summary>	Unspecified rotation.< / summary>
			DXGI_MODE_ROTATION_UNSPECIFIED = 0,
			/// <summary>	Specifies no rotation.< / summary>
			DXGI_MODE_ROTATION_IDENTITY = 1,
			/// <summary>	Specifies 90 degrees of rotation.< / summary>
			DXGI_MODE_ROTATION_ROTATE90 = 2,
			/// <summary>	Specifies 180 degrees of rotation.< / summary>
			DXGI_MODE_ROTATION_ROTATE180 = 3,
			/// <summary>	Specifies 270 degrees of rotation.< / summary>
			DXGI_MODE_ROTATION_ROTATE270 = 4
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Describes an output or physical connection between the adapter (video card) and a device. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		public value struct DXGI_OUTPUT_DESC
		{
			/// <summary>	A string that contains the name of the output device.< / summary>
			Platform::String^       DeviceName;
			/// <summary>	A RECT structure containing the bounds of the output in desktop coordinates. Desktop coordinates depend on the dots per inch (DPI) of the desktop. For info about writing DPI-aware Win32 apps, see High DPI.< / summary>
			WOtech::DXWrapper::RECT	DesktopCoordinates;
			/// <summary>	True if the output is attached to the desktop; otherwise, false.< / summary>
			Platform::Boolean		AttachedToDesktop;
			/// <summary>	A member of the DXGI_MODE_ROTATION enumerated type describing on how an image is rotated by the output.< / summary>
			MODE_ROTATION_DXGI		Rotation;
			// TODO: HMONITOR           Monitor;
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Represents a rational number. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		public value struct RATIONAL_DXGI
		{
			/// <summary>	An unsigned integer value representing the top of the rational number.< / summary>
			UINT Numerator;
			/// <summary>	An unsigned integer value representing the bottom of the rational number.< / summary>
			UINT Denominator;
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Flags indicating the method the raster uses to create an image on a surface. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		public enum class MODE_SCANLINE_ORDER_DXGI
		{
			/// <summary>	Scanline order is unspecified.< / summary>
			DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED = 0,
			/// <summary>	The image is created from the first scanline to the last without skipping any.< / summary>
			DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE = 1,
			/// <summary>	The image is created beginning with the upper field.< / summary>
			DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST = 2,
			/// <summary>	The image is created beginning with the lower field.< / summary>
			DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST = 3
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Flags indicating how an image is stretched to fit a given monitor's resolution. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		public enum class MODE_SCALING_DXGI
		{
			/// <summary>	Unspecified scaling.< / summary>
			DXGI_MODE_SCALING_UNSPECIFIED = 0,
			/// <summary>	Specifies no scaling. The image is centered on the display. This flag is typically used for a fixed-dot-pitch display (such as an LED display).< / summary>
			DXGI_MODE_SCALING_CENTERED = 1,
			/// <summary>	Specifies stretched scaling.< / summary>
			DXGI_MODE_SCALING_STRETCHED = 2
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Describes a display mode. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		public value struct MODE_DESC_DXGI
		{
			/// <summary>	A value that describes the resolution width. If you specify the width as zero when you call the IDXGIFactory::CreateSwapChain method to create a swap chain, the runtime obtains the width from the output window and assigns this width value to the swap-chain description. You can subsequently call the IDXGISwapChain::GetDesc method to retrieve the assigned width value.< / summary>
			UINT                     Width;
			/// <summary>	A value describing the resolution height. If you specify the height as zero when you call the IDXGIFactory::CreateSwapChain method to create a swap chain, the runtime obtains the height from the output window and assigns this height value to the swap-chain description. You can subsequently call the IDXGISwapChain::GetDesc method to retrieve the assigned height value.< / summary>
			UINT                     Height;
			/// <summary>	A DXGI_RATIONAL structure describing the refresh rate in hertz< / summary>
			RATIONAL_DXGI            RefreshRate;
			/// <summary>	A DXGI_FORMAT structure describing the display format.< / summary>
			FORMAT_DXGI              Format;
			/// <summary>	A member of the DXGI_MODE_SCANLINE_ORDER enumerated type describing the scanline drawing mode.< / summary>
			MODE_SCANLINE_ORDER_DXGI ScanlineOrdering;
			/// <summary>	A member of the DXGI_MODE_SCALING enumerated type describing the scaling mode.< / summary>
			MODE_SCALING_DXGI        Scaling;
		};

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
			case WOtech::DXWrapper::MODE_ROTATION_DXGI::DXGI_MODE_ROTATION_UNSPECIFIED:
				return DXGI_MODE_ROTATION::DXGI_MODE_ROTATION_UNSPECIFIED;
				break;
			case WOtech::DXWrapper::MODE_ROTATION_DXGI::DXGI_MODE_ROTATION_IDENTITY:
				return DXGI_MODE_ROTATION::DXGI_MODE_ROTATION_IDENTITY;
				break;
			case WOtech::DXWrapper::MODE_ROTATION_DXGI::DXGI_MODE_ROTATION_ROTATE90:
				return DXGI_MODE_ROTATION::DXGI_MODE_ROTATION_ROTATE90;
				break;
			case WOtech::DXWrapper::MODE_ROTATION_DXGI::DXGI_MODE_ROTATION_ROTATE180:
				return DXGI_MODE_ROTATION::DXGI_MODE_ROTATION_ROTATE180;
				break;
			case WOtech::DXWrapper::MODE_ROTATION_DXGI::DXGI_MODE_ROTATION_ROTATE270:
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
			case WOtech::DXWrapper::MODE_SCANLINE_ORDER_DXGI::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED:
				return DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
				break;
			case WOtech::DXWrapper::MODE_SCANLINE_ORDER_DXGI::DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE:
				return DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
				break;
			case WOtech::DXWrapper::MODE_SCANLINE_ORDER_DXGI::DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST:
				return DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST;
				break;
			case WOtech::DXWrapper::MODE_SCANLINE_ORDER_DXGI::DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST:
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
			case WOtech::DXWrapper::MODE_SCALING_DXGI::DXGI_MODE_SCALING_UNSPECIFIED:
				return DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;
				break;
			case WOtech::DXWrapper::MODE_SCALING_DXGI::DXGI_MODE_SCALING_CENTERED:
				return DXGI_MODE_SCALING::DXGI_MODE_SCALING_CENTERED;
				break;
			case WOtech::DXWrapper::MODE_SCALING_DXGI::DXGI_MODE_SCALING_STRETCHED:
				return DXGI_MODE_SCALING::DXGI_MODE_SCALING_STRETCHED;
				break;
			default:
				return DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;
				break;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Specifies the parts of the depth stencil to clear.  </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		public enum class CLEAR_FLAG
		{
			/// <summary>	Clear the depth buffer, using fast clear if possible, then place the resource in a compressed state.< / summary>
			CLEAR_DEPTH = 0x1L,
			/// <summary>	Clear the stencil buffer, using fast clear if possible, then place the resource in a compressed state.< / summary>
			CLEAR_STENCIL = 0x2L
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Type of data contained in an input slot. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		public enum class INPUT_CLASSIFICATION
		{
			/// <summary>	Input data is per-vertex data.< / summary>
			D3D11_INPUT_PER_VERTEX_DATA = 0,
			/// <summary>	Input data is per-instance data.< / summary>
			D3D11_INPUT_PER_INSTANCE_DATA = 1
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	A description of a single element for the input-assembler stage. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		public value struct INPUT_ELEMENT_DESC
		{
			/// <summary>	The HLSL semantic associated with this element in a shader input-signature.< / summary>
			Platform::String^				SemanticName;
			/// <summary>	The semantic index for the element. A semantic index modifies a semantic, with an integer index number. A semantic index is only needed in a case where there is more than one element with the same semantic. For example, a 4x4 matrix would have four components each with the semantic name < / summary>
			UINT							SemanticIndex;
			/// <summary>	The data type of the element data. See FORMAT_DXGI.< / summary>
			FORMAT_DXGI						Format;
			/// <summary>	An integer value that identifies the input-assembler (see input slot). Valid values are between 0 and 15.< / summary>
			UINT							InputSlot;
			/// <summary>	Optional. Offset (in bytes) between each element. Use D3D11_APPEND_ALIGNED_ELEMENT for convenience to define the current element directly after the previous one, including any packing if necessary.< / summary>
			unsigned int					AlignedByteOffset;
			/// <summary>	Identifies the input data class for a single input slot.< / summary>
			INPUT_CLASSIFICATION			InputSlotClass;
			/// <summary>	The number of instances to draw using the same per-instance data before advancing in the buffer by one element. This value must be 0 for an element that contains per-vertex data (the slot class is set to D3D11_INPUT_PER_VERTEX_DATA).< / summary>
			UINT							InstanceDataStepRate;
		};

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

			D3D11_INPUT_ELEMENT_DESC* InputElementDESC = new D3D11_INPUT_ELEMENT_DESC;

			for (unsigned int i = 0; i <= size; i++)
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
		/// <summary>	Converts Windows::Foundation::Numerics::float4x4. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="matrix">	A 4x4 matrix, used for 3D transforms. </param>
		///
		/// <returns>	A DirectX::XMFLOAT4X4. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DirectX::XMFLOAT4X4 XM_CALLCONV wrapFloat4x4(_In_ Windows::Foundation::Numerics::float4x4 matrix)
		{
			return DirectX::XMFLOAT4X4(matrix.m11, matrix.m12, matrix.m13, matrix.m14,
				matrix.m21, matrix.m22, matrix.m23, matrix.m24,
				matrix.m31, matrix.m32, matrix.m33, matrix.m34,
				matrix.m41, matrix.m42, matrix.m43, matrix.m44);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts Windows::Foundation::Numerics::float4x4. </summary>
		///
		/// <remarks>	WraithOne, 20.08.2017. </remarks>
		///
		/// <param name="matrix">	A 4x4 matrix, used for 3D transforms. </param>
		///
		/// <returns>	A DirectX::XMMATRIX </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DirectX::XMMATRIX XM_CALLCONV wrapXMMATRIX(_In_ Windows::Foundation::Numerics::float4x4 matrix)
		{
			return DirectX::XMMATRIX(matrix.m11, matrix.m12, matrix.m13, matrix.m14,
				matrix.m21, matrix.m22, matrix.m23, matrix.m24,
				matrix.m31, matrix.m32, matrix.m33, matrix.m34,
				matrix.m41, matrix.m42, matrix.m43, matrix.m44);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	DirectX::XMFLOAT4X4 </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="matrix">	A 4*4 floating point matrix. </param>
		///
		/// <returns>	A 4x4 matrix, used for 3D transforms. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline WOtech::FLOAT4x4 XM_CALLCONV wrapXMFloat4x4(_In_ DirectX::XMFLOAT4X4 matrix)
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
		/// <summary>	DirectX::XMFLOAT4X4 </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="matrix">	A 4*4 floating point matrix. </param>
		///
		/// <returns>	A 4x4 matrix, used for 3D transforms. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DirectX::XMFLOAT4X4 XM_CALLCONV wrapWOFloat4x4(_In_ WOtech::FLOAT4x4 matrix)
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
		/// <summary>	DirectX::XMFLOAT4X4 </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="matrix">	A 4*4 floating point matrix. </param>
		///
		/// <returns>	A 4x4 matrix, used for 3D transforms. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DirectX::XMVECTOR XM_CALLCONV XMLoadFloat2(_In_ WOtech::FLOAT2 vector)
		{
			DirectX::XMFLOAT2 output = { vector.X, vector.Y };

			return DirectX::XMLoadFloat2(&output);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	DirectX::XMFLOAT4X4 </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="matrix">	A 4*4 floating point matrix. </param>
		///
		/// <returns>	A 4x4 matrix, used for 3D transforms. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DirectX::XMVECTOR XM_CALLCONV XMLoadFloat3(_In_ WOtech::FLOAT3 vector)
		{
			DirectX::XMFLOAT3 output = { vector.X, vector.Y , vector.Z};

			return DirectX::XMLoadFloat3(&output);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	DirectX::XMFLOAT4X4 </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="matrix">	A 4*4 floating point matrix. </param>
		///
		/// <returns>	A 4x4 matrix, used for 3D transforms. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DirectX::XMVECTOR XM_CALLCONV XMLoadFloat4(_In_ WOtech::FLOAT4 vector)
		{
			DirectX::XMFLOAT4 output = { vector.X, vector.Y , vector.Z , vector.W};

			return DirectX::XMLoadFloat4(&output);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	DirectX::XMFLOAT4X4 </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="matrix">	A 4*4 floating point matrix. </param>
		///
		/// <returns>	A 4x4 matrix, used for 3D transforms. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		inline DirectX::XMMATRIX XM_CALLCONV XMLoadFloat4x4(_In_ WOtech::FLOAT4x4 matrix)
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
	}
}
#endif