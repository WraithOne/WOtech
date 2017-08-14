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
///			Edited:		15.04.2017
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

#include "Source\Shader\Compiled\VS_Basic.inc"
#include "Source\Shader\Compiled\PS_Basic.inc"

namespace WOtech
{
	Material ^ DefaultFactory::CreateBasicMaterial(_In_ WOtech::DeviceDX11 ^ device)
	{
		WOtech::VertexShader^ vertexshader = ref new VertexShader(VS_Basic, sizeof(VS_Basic), nullptr, 0, 0,device);
		WOtech::PixelShader^ pixelshader = ref new PixelShader(PS_Basic, sizeof(PS_Basic), device);

		return ref new Material(vertexshader, pixelshader, device);
	}

	Mesh^ DefaultFactory::CreateCube(_In_ float size, _In_ MaterialInstance^ material, _In_ DeviceDX11^ device)
	{
		auto data = ref new Platform::Array<VertexPositionColor^>(6);

		for (unsigned int i = 0; i < data->Length; i++)
		{
			data[i] = ref new VertexPositionColor;
		}

		data[0]->Position = Windows::Foundation::Numerics::float3{ -size / 2.0f, -size / 2.0f, size / 2.0f };
		data[0]->Color = Windows::Foundation::Numerics::float4(1.0f, 0.0f, 0.0f, 1.0f);

		data[1]->Position = Windows::Foundation::Numerics::float3(0.0f, 0.0f, 1.0f);
		data[1]->Color = Windows::Foundation::Numerics::float4(1.0f, 0.0f, 0.0f, 1.0f);

		data[2]->Position = Windows::Foundation::Numerics::float3(size / 2.0f, size / 2.0f, size / 2.0f);
		data[2]->Color = Windows::Foundation::Numerics::float4(1.0f, 0.0f, 0.0f, 1.0f);

		data[3]->Position = Windows::Foundation::Numerics::float3(-size / 2.0f, size / 2.0f, size / 2.0f);
		data[3]->Color = Windows::Foundation::Numerics::float4(1.0f, 0.0f, 0.0f, 1.0f);

		data[4]->Position = Windows::Foundation::Numerics::float3(-size / 2.0f, -size / 2.0f, -size / 2.0f);
		data[4]->Color = Windows::Foundation::Numerics::float4(1.0f, 0.0f, 0.0f, 1.0f);

		data[5]->Position = Windows::Foundation::Numerics::float3(size / 2.0f, -size / 2.0f, -size / 2.0f);
		data[5]->Color = Windows::Foundation::Numerics::float4(1.0f, 0.0f, 0.0f, 1.0f);

		WORD indices[] =
		{
			0, 1, 2, 2, 3, 0,
			3, 2, 6, 6, 7, 3,
			7, 6, 5, 5, 4, 7,
			4, 0, 3, 3, 7, 4,
			0, 1, 5, 5, 4, 0,
			1, 5, 6, 6, 2, 1
		};

		IndexBuffer^ iB = ref new IndexBuffer(indices, 36, device);

		UINT32 stride = sizeof(VertexPositionColor);
		VertexBuffer^ vB = ref new VertexBuffer(data->Data, 8 * sizeof(VertexPositionColor), stride, 0U, device);

		return ref new Mesh(vB, iB, material);
	}
	Mesh^ DefaultFactory::CreateTriangle(_In_ float size, _In_ MaterialInstance^ material, _In_ DeviceDX11^ device)
	{
		auto data = ref new Platform::Array<VertexPositionColor^>(3);

		for (unsigned int i = 0; i < data->Length; i++)
		{
			data[i] = ref new VertexPositionColor;
		}

		data[0]->Position = Windows::Foundation::Numerics::float3(0.5f, 0.5f, 0.5f);
		data[0]->Color = Windows::Foundation::Numerics::float4(1.0f, 0.0f, 0.0f, 1.0f);
		

		data[1]->Position = Windows::Foundation::Numerics::float3(0.5f, -0.5f, 0.5f);
		data[1]->Color = Windows::Foundation::Numerics::float4(1.0f, 0.0f, 0.0f, 1.0f);
		

		data[2]->Position = Windows::Foundation::Numerics::float3(-0.5f, -0.5f, 0.5f);
		data[2]->Color = Windows::Foundation::Numerics::float4(1.0f, 0.0f, 0.0f, 1.0f);
		

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