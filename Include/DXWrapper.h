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
///			Edited:		10.05.2017
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_DXWRAPPER_H
#define WO_DXWRAPPER_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Utilities.h"

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
		D2D1_COLOR_F wrapColor(_In_ Windows::UI::Color color);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts WOtech::DXWrapper::RECT into D2D1_RECT_F. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="rect">	Represents a rectangle defined by the coordinates of the upper-left corner (left, top) and the coordinates of the lower-right corner (right, bottom). </param>
		///
		/// <returns>	D2D1_RECT_F, Represents a rectangle defined by the coordinates of the upper-left corner (left, top) and the coordinates of the lower-right corner (right, bottom). </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		D2D1_RECT_F wrapRect(_In_ WOtech::DXWrapper::RECT rect);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts Windows::Foundation::Size. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="size">	Represents number values that specify a height and width. </param>
		///
		/// <returns>	D2D1_SIZE_F, Stores an ordered pair of floats, typically the width and height of a rectangle. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		D2D1_SIZE_F wrapSize(_In_ Windows::Foundation::Size size);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts Windows::Foundation::Point. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="point"> Represents x - and y - coordinate values that define a point in a two - dimensional plane.. </param>
		///
		/// <returns>	D2D1_POINT_2F, Represents an x-coordinate and y-coordinate pair in two-dimensional space. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		D2D1_POINT_2F wrapPoint(_In_ Windows::Foundation::Point point);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts FONT_STYLE. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="fontstyle"> Represents the style of a font face as normal, italic, or oblique. </param>
		///
		/// <returns>	A DWRITE_FONT_STYLE. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		DWRITE_FONT_STYLE wraptFontStyle(_In_ FONT_STYLE fontstyle);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts BITMAP_INTERPOLATION_MODE. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="bitmapinterpolationmode"> Specifies the algorithm that is used when images are scaled or rotated. </param>
		///
		/// <returns>	A D2D1_BITMAP_INTERPOLATION_MODE. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		D2D1_BITMAP_INTERPOLATION_MODE wrapBitmapInterpolationMode(_In_ const BITMAP_INTERPOLATION_MODE bitmapinterpolationmode);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts FIGURE_BEGIN. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="figurebegin">	Indicates whether a specific figure is filled or hollow.  </param>
		///
		/// <returns>	A D2D1_FIGURE_BEGIN. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		D2D1_FIGURE_BEGIN wrapFigureBegin(_In_ FIGURE_BEGIN figurebegin);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts FIGURE_END. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="figureend">	Indicates whether a specific figure is open or closed.  </param>
		///
		/// <returns>	A D2D1_FIGURE_END. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		D2D1_FIGURE_END wrapFigureEnd(_In_ FIGURE_END figureend);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts BEZIER_SEGMENT. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="beziersegment">	Represents a cubic bezier segment drawn between two points. </param>
		///
		/// <returns>	A D2D1_BEZIER_SEGMENT. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		D2D1_BEZIER_SEGMENT wrapBezierSegment(_In_ BEZIER_SEGMENT beziersegment);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts SWEEP_DIRECTION. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="sweepdirection">	Defines the direction that an elliptical arc is drawn.  </param>
		///
		/// <returns>	A D2D1_SWEEP_DIRECTION. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		D2D1_SWEEP_DIRECTION wrapSweepDirection(_In_ SWEEP_DIRECTION sweepdirection);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts ARC_SIZE. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="arcsize">	Specifies whether an arc should be greater than 180 degrees. </param>
		///
		/// <returns>	A D2D1_ARC_SIZE. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		D2D1_ARC_SIZE wrapArcSize(_In_ ARC_SIZE arcsize);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts ARC_SEGMENT. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="arcsegment">	Describes an elliptical arc between two points. </param>
		///
		/// <returns>	A D2D1_ARC_SEGMENT. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		D2D1_ARC_SEGMENT wrapArcSegment(_In_ ARC_SEGMENT arcsegment);

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
		DXGI_FORMAT wrapDXGIFormat(_In_ FORMAT_DXGI formatDXGI);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts MODE_ROTATION_DXGI. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="moderotationDXGI">	Flags that indicate how the back buffers should be rotated to fit the physical rotation of a monitor. </param>
		///
		/// <returns>	A DXGI_MODE_ROTATION. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		DXGI_MODE_ROTATION wrapDXGIModeRotation(_In_ MODE_ROTATION_DXGI moderotationDXGI);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts MODE_SCANLINE_ORDER_DXGI. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="modescanlineorderDXGI">	Flags indicating the method the raster uses to create an image on a surface.. </param>
		///
		/// <returns>	A DXGI_MODE_SCANLINE_ORDER. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		DXGI_MODE_SCANLINE_ORDER warpDXGIModeScanlineOrder(_In_ MODE_SCANLINE_ORDER_DXGI modescanlineorderDXGI);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts MODE_SCALING_DXGI. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="modescalingmodeDXGI">	The modescalingmode dxgi. </param>
		///
		/// <returns>	A DXGI_MODE_SCALING. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		DXGI_MODE_SCALING warpDXGIModeScaling(_In_ MODE_SCALING_DXGI modescalingmodeDXGI);

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
		D3D11_CLEAR_FLAG wrapClearFlag(_In_ CLEAR_FLAG clearflag);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts INPUT_CLASSIFICATION. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="inputclassification">	The inputclassification. </param>
		///
		/// <returns>	A D3D11_INPUT_CLASSIFICATION. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		D3D11_INPUT_CLASSIFICATION wrapInputClassification(_In_ INPUT_CLASSIFICATION inputclassification);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts Platform::Array<INPUT_ELEMENT_DESC>^ . </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="inputelementdesc">	The inputelementdesc. </param>
		///
		/// <returns>	Null if it fails, else a pointer to a D3D11_INPUT_ELEMENT_DESC. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		D3D11_INPUT_ELEMENT_DESC* wrapInputElementDesc(_In_ const Platform::Array<INPUT_ELEMENT_DESC>^ inputelementdesc);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Converts Windows::Foundation::Numerics::float4x4. </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="matrix">	A 4x4 matrix, used for 3D transforms.. </param>
		///
		/// <returns>	A DirectX::XMFLOAT4X4. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		DirectX::XMFLOAT4X4 wrapFloat4x4(_In_ Windows::Foundation::Numerics::float4x4 matrix);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	DirectX::XMFLOAT4X4 </summary>
		///
		/// <remarks>	WraithOne, 17.04.2017. </remarks>
		///
		/// <param name="matrix">	A 4*4 floating point matrix. </param>
		///
		/// <returns>	A 4x4 matrix, used for 3D transforms. </returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Windows::Foundation::Numerics::float4x4 wrapXMFloat4x4(_In_ DirectX::XMFLOAT4X4 matrix);
	}
}
#endif