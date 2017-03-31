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
///			Edited:		31.03.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "DXWrapper.h"

using namespace Windows::UI;
using namespace Windows::Foundation;
using namespace WOtech::DXWrapper;
namespace WOtech
{
	namespace DXWrapper
	{
		D2D1_COLOR_F wrapColor(_In_ Color color)
		{
			return D2D1::ColorF(static_cast<float>(color.R), static_cast<float>(color.G), static_cast<float>(color.B), static_cast<float>(color.A));
		}

		D2D1_RECT_F wrapRect(_In_ RECT& rect)
		{
			return D2D1::RectF(rect.X, rect.Y, rect.Width, rect.Height);
		}

		D2D1_SIZE_F wrapSize(_In_ Size size)
		{
			return D2D1::SizeF(size.Width, size.Height);
		}

		D2D1_POINT_2F wrapPoint(_In_ Point point)
		{
			return D2D1::Point2F(point.X, point.Y);
		}

		DWRITE_FONT_STYLE wraptFontStyle(_In_ FONT_STYLE fontstyle)
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

		D2D1_BITMAP_INTERPOLATION_MODE wrapBitmapInterpolationMode(_In_ const BITMAP_INTERPOLATION_MODE& bitmapinterpolationmode)
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

		D2D1_FIGURE_BEGIN wrapFigureBegin(_In_ FIGURE_BEGIN figurebegin)
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

		D2D1_FIGURE_END wrapFigureEnd(_In_ FIGURE_END figureend)
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

		D2D1_BEZIER_SEGMENT wrapBezierSegment(_In_ BEZIER_SEGMENT& beziersegment)
		{
			return D2D1::BezierSegment(wrapPoint(beziersegment.point1), wrapPoint(beziersegment.point2), wrapPoint(beziersegment.point3));
		}

		D2D1_SWEEP_DIRECTION wrapSweepDirection(_In_ SWEEP_DIRECTION sweepdirection)
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

		D2D1_ARC_SIZE wrapArcSize(_In_ ARC_SIZE arcsize)
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

		D2D1_ARC_SEGMENT wrapArcSegment(_In_ ARC_SEGMENT& arcsegment)
		{
			return D2D1::ArcSegment(wrapPoint(arcsegment.point), wrapSize(arcsegment.size), arcsegment.rotationAngle, wrapSweepDirection(arcsegment.sweepDirection), wrapArcSize(arcsegment.arcSize));
		}

		D3D11_CLEAR_FLAG wrapClearFlag(_In_ CLEAR_FLAG clearflag)
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

		D3D11_INPUT_CLASSIFICATION wrapInputClassification(_In_ INPUT_CLASSIFICATION inputclassification)
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

		D3D11_INPUT_ELEMENT_DESC* wrapInputElementDesc(_In_ const Platform::Array<INPUT_ELEMENT_DESC>^ inputelementdesc)
		{
			const UINT size = inputelementdesc->Length;

			D3D11_INPUT_ELEMENT_DESC* InputElementDESC = new D3D11_INPUT_ELEMENT_DESC;

			for (unsigned int i = 0; i <= size; i++)
			{
				InputElementDESC[i].AlignedByteOffset = inputelementdesc[i].AlignedByteOffset;// DATA type!!!! buffer OVERFLOW
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

		DirectX::XMFLOAT4X4 wrapFloat4x4(_In_ Windows::Foundation::Numerics::float4x4 matrix)
		{
			return DirectX::XMFLOAT4X4(matrix.m11, matrix.m12, matrix.m13, matrix.m14,
				matrix.m21, matrix.m22, matrix.m23, matrix.m24,
				matrix.m31, matrix.m32, matrix.m33, matrix.m34,
				matrix.m41, matrix.m42, matrix.m43, matrix.m44);
		}

		Windows::Foundation::Numerics::float4x4 wrapXMFloat4x4(_In_ DirectX::XMFLOAT4X4& matrix)
		{
			Windows::Foundation::Numerics::float4x4 temp;
			temp.m11 = matrix._11;
			temp.m12 = matrix._12;
			temp.m13 = matrix._13;
			temp.m14 = matrix._14;
			temp.m21 = matrix._21;
			temp.m22 = matrix._22;
			temp.m23 = matrix._23;
			temp.m24 = matrix._24;
			temp.m31 = matrix._31;
			temp.m32 = matrix._32;
			temp.m33 = matrix._33;
			temp.m34 = matrix._34;
			temp.m41 = matrix._41;
			temp.m42 = matrix._42;
			temp.m43 = matrix._43;
			temp.m44 = matrix._44;
			return temp;
		}

		DXGI_FORMAT wrapDXGIFormat(_In_ FORMAT_DXGI formatDXGI)
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

		DXGI_MODE_ROTATION wrapDXGIModeRotation(_In_ MODE_ROTATION_DXGI moderotationDXGI)
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

		DXGI_MODE_SCANLINE_ORDER warpDXGIModeScanlineOrder(_In_ MODE_SCANLINE_ORDER_DXGI modescanlineorderDXGI)
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

		DXGI_MODE_SCALING warpDXGIModeScaling(_In_ MODE_SCALING_DXGI modescalingmodeDXGI)
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
	}
}