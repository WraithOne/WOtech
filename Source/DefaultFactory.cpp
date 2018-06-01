////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: DefaultFactory.cpp
///
///			Description:
///
///			Created:	27.02.2016
///			Edited:		01.05.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include <WindowsNumerics.h>

#include "DefaultFactory.h"
#include "VertexTypes.h"
#include "DeviceDX11.h"
#include "3DComponents.h"
#include "Materials.h"

#include "Source\Shader\Compiled\VS_Basic.inc"
#include "Source\Shader\Compiled\PS_Basic.inc"

namespace WOtech
{
	BasicMaterial ^ DefaultFactory::CreateBasicMaterial(_In_ WOtech::DeviceDX11 ^ device)
	{
		WOtech::VertexShader^ vertexshader = ref new VertexShader((void*)VS_Basic, sizeof(VS_Basic), nullptr, 0, 0, device);//todo: safecheck
		WOtech::PixelShader^ pixelshader = ref new PixelShader((void*)PS_Basic, sizeof(PS_Basic), device);//todo: safecheck

		return ref new BasicMaterial(vertexshader, pixelshader, device);
	}

	Mesh^ DefaultFactory::CreateCube(_In_ float size, _In_ IMaterial^ material, _In_ DeviceDX11^ device)
	{
		auto data = ref new Platform::Array<VertexPositionColor^>(8);

		for (unsigned int i = 0; i < data->Length; i++)
		{
			data[i] = ref new VertexPositionColor;
		}

		data[0]->Position = Windows::Foundation::Numerics::float3{ -size / 2.0f, -size / 2.0f, -size / 2.0f };
		data[0]->Color = Windows::Foundation::Numerics::float4{ 1.0f, 0.0f, 0.0f, 1.0f };

		data[1]->Position = Windows::Foundation::Numerics::float3{ -size / 2.0f, -size / 2.0f, size / 2.0f };
		data[1]->Color = Windows::Foundation::Numerics::float4{ 0.0f, 1.0f, 0.0f, 1.0f };

		data[2]->Position = Windows::Foundation::Numerics::float3{ -size / 2.0f, size / 2.0f, -size / 2.0f };
		data[2]->Color = Windows::Foundation::Numerics::float4{ 0.0f, 0.0f, 1.0f, 1.0f };

		data[3]->Position = Windows::Foundation::Numerics::float3{ -size / 2.0f, size / 2.0f, size / 2.0f };
		data[3]->Color = Windows::Foundation::Numerics::float4{ 1.0f, 0.0f, 0.0f, 1.0f };

		data[4]->Position = Windows::Foundation::Numerics::float3{ size / 2.0f, -size / 2.0f, -size / 2.0f };
		data[4]->Color = Windows::Foundation::Numerics::float4{ 0.0f, 1.0f, 0.0f, 1.0f };

		data[5]->Position = Windows::Foundation::Numerics::float3{ size / 2.0f, -size / 2.0f, size / 2.0f };
		data[5]->Color = Windows::Foundation::Numerics::float4{ 0.0f, 0.0f, 1.0f, 1.0f };

		data[6]->Position = Windows::Foundation::Numerics::float3{ size / 2.0f, size / 2.0f, -size / 2.0f };
		data[6]->Color = Windows::Foundation::Numerics::float4{ 1.0f, 0.0f, 0.0f, 1.0f };

		data[7]->Position = Windows::Foundation::Numerics::float3{ size / 2.0f, size / 2.0f, size / 2.0f };
		data[7]->Color = Windows::Foundation::Numerics::float4{ 0.0f, 1.0f, 0.0f, 1.0f };

		WORD indices[] =
		{
			0,2,1, // -x
			1,2,3,

			4,5,6, // +x
			5,7,6,

			0,1,5, // -y
			0,5,4,

			2,6,7, // +y
			2,7,3,

			0,4,6, // -z
			0,6,2,

			1,3,7, // +z
			1,7,5,
		};

		IndexBuffer^ iB = ref new IndexBuffer(indices, 36, device);

		UINT32 stride = sizeof(VertexPositionColor);
		VertexBuffer^ vB = ref new VertexBuffer(data->Data, sizeof(VertexPositionColor), stride, 0U, device);

		return ref new Mesh(vB, iB, material);
	}
	Mesh^ DefaultFactory::CreateTriangle(_In_ float size, _In_ IMaterial^ material, _In_ DeviceDX11^ device)
	{
		auto data = ref new Platform::Array<VertexPositionColor^>(3);

		for (unsigned int i = 0; i < data->Length; i++)
		{
			data[i] = ref new VertexPositionColor;
		}

		data[0]->Position = Windows::Foundation::Numerics::float3{ 0.5f, 0.5f, 0.5f };
		data[0]->Color = Windows::Foundation::Numerics::float4{ 1.0f, 0.0f, 0.0f, 1.0f };

		data[1]->Position = Windows::Foundation::Numerics::float3{ 0.5f, -0.5f, 0.5f };
		data[1]->Color = Windows::Foundation::Numerics::float4{ 1.0f, 0.0f, 0.0f, 1.0f };

		data[2]->Position = Windows::Foundation::Numerics::float3{ -0.5f, -0.5f, 0.5f };
		data[2]->Color = Windows::Foundation::Numerics::float4{ 1.0f, 0.0f, 0.0f, 1.0f };

		WORD indices[] =
		{
			0, 1, 2
		};

		IndexBuffer^ iB = ref new IndexBuffer(indices, 3, device);
		UINT32 stride = sizeof(VertexPositionColor);
		VertexBuffer^ vB = ref new VertexBuffer(data->Data, 3 * sizeof(VertexPositionColor), stride, 0U, device);

		return ref new Mesh(vB, iB, material);
	}
}