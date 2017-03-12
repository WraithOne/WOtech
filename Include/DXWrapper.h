////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: DXWrapper.h
///
///			Description:
///
///			Created:	06.11.2016
///			Edited:		26.12.2016
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
		///////////////////////////////////////////////////////////////
		// D2D1 Wrapper 
		///////////////////////////////////////////////////////////////
		public enum class FONT_STYLE
		{
			/// <summary>
			/// Font slope style : Normal.
			/// </summary>
			FONT_STYLE_NORMAL,

			/// <summary>
			/// Font slope style : Oblique.
			/// </summary>
			FONT_STYLE_OBLIQUE,

			/// <summary>
			/// Font slope style : Italic.
			/// </summary>
			FONT_STYLE_ITALIC

		};

		public enum class BITMAP_INTERPOLATION_MODE
		{

			/// <summary>
			/// Nearest Neighbor filtering. Also known as nearest pixel or nearest point
			/// sampling.
			/// </summary>
			BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,

			/// <summary>
			/// Linear filtering.
			/// </summary>
			BITMAP_INTERPOLATION_MODE_LINEAR,
			BITMAP_INTERPOLATION_MODE_FORCE_DWORD
		};

		public enum class FIGURE_BEGIN
		{
			FIGURE_BEGIN_FILLED, // Indicates the figure will be filled by the FillGeometry (ID2D1CommandSink::FillGeometry or ID2D1RenderTarget::FillGeometry) method.
			FIGURE_BEGIN_HALLOW // Indicates the figure will not be filled by the FillGeometry (ID2D1CommandSink::FillGeometry or ID2D1RenderTarget::FillGeometry) method and will only consist of an outline. Moreover, the bounds of a hollow figure are zero. D2D1_FIGURE_BEGIN_HOLLOW should be used for stroking, or for other geometry operations.
		};

		public enum class FIGURE_END
		{
			FIGURE_END_OPEN, // The figure is open.
			FIGURE_END_CLOSED // The figure is closed.
		};

		public value struct BEZIER_SEGMENT
		{
			Windows::Foundation::Point point1; // The first control point for the Bezier segment.
			Windows::Foundation::Point point2; // The second control point for the Bezier segment.
			Windows::Foundation::Point point3; // The end point for the Bezier segment.
		};

		public enum class SWEEP_DIRECTION
		{
			D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE, // Arcs are drawn in a counterclockwise(negative - angle) direction.
			D2D1_SWEEP_DIRECTION_CLOCKWISE // Arcs are drawn in a clockwise (positive-angle) direction. 
		};

		public enum class ARC_SIZE
		{
			D2D1_ARC_SIZE_SMALL, // An arc's sweep should be 180 degrees or less.
			D2D1_ARC_SIZE_LARGE // An arc's sweep should be 180 degrees or greater.
		};

		public value struct ARC_SEGMENT
		{
			Windows::Foundation::Point point; // The end point of the arc.
			Windows::Foundation::Size size; // The x-radius and y-radius of the arc.
			FLOAT rotationAngle; // A value that specifies how many degrees in the clockwise direction the ellipse is rotated relative to the current coordinate system.
			SWEEP_DIRECTION sweepDirection; // A value that specifies whether the arc sweep is clockwise or counterclockwise.
			ARC_SIZE arcSize; // A value that specifies whether the given arc is larger than 180 degrees.
		};

		public value class RECT
		{
		public:
			float X;
			float Y;
			float Width;
			float Height;
		};
		
		///////////////////////////////////////////////////////////////
		// D2D1 Wrapper Functions
		///////////////////////////////////////////////////////////////
		D2D1_COLOR_F wrapColor(_In_ Windows::UI::Color& color);

		D2D1_RECT_F wrapRect(_In_ WOtech::DXWrapper::RECT& rect);

		D2D1_SIZE_F wrapSize(_In_ Windows::Foundation::Size& size);

		D2D1_POINT_2F wrapPoint(_In_ Windows::Foundation::Point& point);

		DWRITE_FONT_STYLE wraptFontStyle(_In_ FONT_STYLE& fontstyle);

		D2D1_BITMAP_INTERPOLATION_MODE wrapBitmapInterpolationMode(_In_ const BITMAP_INTERPOLATION_MODE& bitmapinterpolationmode);

		D2D1_FIGURE_BEGIN wrapFigureBegin(_In_ FIGURE_BEGIN& figurebegin);

		D2D1_FIGURE_END wrapFigureEnd(_In_ FIGURE_END& figureend);

		D2D1_BEZIER_SEGMENT wrapBezierSegment(_In_ BEZIER_SEGMENT& beziersegment);

		D2D1_SWEEP_DIRECTION wrapSweepDirection(_In_ SWEEP_DIRECTION& sweepdirection);

		D2D1_ARC_SIZE wrapArcSize(_In_ ARC_SIZE& arcsize);

		D2D1_ARC_SEGMENT wrapArcSegment(_In_ ARC_SEGMENT& arcsegment);

		///////////////////////////////////////////////////////////////
		// D3D11 Wrapper 
		///////////////////////////////////////////////////////////////
		public value struct VertexPosition
		{
			Windows::Foundation::Numerics::float3 Position;
		};

		public value struct VertexPositionColor 
		{
			Windows::Foundation::Numerics::float3 Position;
			Windows::Foundation::Numerics::float4 Color;
		};

		public value struct VertexPositionTexture
		{
			Windows::Foundation::Numerics::float3 Position;
			Windows::Foundation::Numerics::float2 TextureCoordinate;
		};

		public value struct VertexPositionNormal
		{
			Windows::Foundation::Numerics::float3 Position;
			Windows::Foundation::Numerics::float2 Normal;
		};

		public value struct VertexPositionNormalColor
		{
			Windows::Foundation::Numerics::float3 Position;
			Windows::Foundation::Numerics::float2 Normal;
			Windows::Foundation::Numerics::float4 Color;
		};

		public value struct VertexPositionColorTexture
		{
			Windows::Foundation::Numerics::float3 Position;
			Windows::Foundation::Numerics::float4 Color;
			Windows::Foundation::Numerics::float2 TextureCoordinate;
		};

		public value struct VertexPositionNormalTexture
		{
			Windows::Foundation::Numerics::float3 Position;
			Windows::Foundation::Numerics::float3 Normal;
			Windows::Foundation::Numerics::float2 TextureCoordinate;
		};

		public value struct VertexPositionNormalColorTexture
		{
			Windows::Foundation::Numerics::float3 Position;
			Windows::Foundation::Numerics::float3 Normal;
			Windows::Foundation::Numerics::float4 Color;
			Windows::Foundation::Numerics::float2 TextureCoordinate;
		};


		public enum class CLEAR_FLAG
		{
			CLEAR_DEPTH = 0x1L,
			CLEAR_STENCIL = 0x2L
		};

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

		public enum class INPUT_CLASSIFICATION
		{
			D3D11_INPUT_PER_VERTEX_DATA = 0,
			D3D11_INPUT_PER_INSTANCE_DATA = 1
		};

		public value struct INPUT_ELEMENT_DESC
		{
			Platform::String^				SemanticName;
			UINT							SemanticIndex;
			FORMAT_DXGI						Format;
			UINT							InputSlot;
			UINT							AlignedByteOffset;
			INPUT_CLASSIFICATION			InputSlotClass;
			UINT							InstanceDataStepRate;
		};

		///////////////////////////////////////////////////////////////
		// D3D11 Wrapper Functions
		///////////////////////////////////////////////////////////////
		D3D11_CLEAR_FLAG wrapClearFlag(_In_ CLEAR_FLAG& clearflag);

		DXGI_FORMAT wrapDXGIFormat(_In_ FORMAT_DXGI& formatDXGI);

		D3D11_INPUT_CLASSIFICATION wrapInputClassification(_In_ INPUT_CLASSIFICATION& inputclassification);

		D3D11_INPUT_ELEMENT_DESC* wrapInputElementDesc(_In_ const Platform::Array<INPUT_ELEMENT_DESC>^ inputelementdesc);

		DirectX::XMFLOAT4X4 wrapFloat4x4(_In_ Windows::Foundation::Numerics::float4x4& matrix);

		Windows::Foundation::Numerics::float4x4 wrapXMFloat4x4(_In_ DirectX::XMFLOAT4X4& matrix);
	}
}
#endif