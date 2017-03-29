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
///			Edited:		29.03.2017
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


namespace WOtech
{
	Mesh^ CreateCube(_In_ float size, _In_ MaterialInstance^ material, _In_ DeviceDX11^ device)
	{
		Platform::Array<VertexPositionNormalTexture^>^ data;
		data->get(0)->Position = Windows::Foundation::Numerics::float3{ -size / 2.0f, -size / 2.0f, size / 2.0f };
		data->get(0)->Normal = Windows::Foundation::Numerics::float3(0.0f, 0.0f, -1.0f);
		data->get(0)->TextureCoordinate = Windows::Foundation::Numerics::float2(0.0f, 0.0f);

		data->get(1)->Position = Windows::Foundation::Numerics::float3(0.0f, 0.0f, 1.0f);
		data->get(1)->Normal = Windows::Foundation::Numerics::float3(0.0f, 0.0f, 1.0f);
		data->get(1)->TextureCoordinate = Windows::Foundation::Numerics::float2(0.0f, 0.0f);

		data->get(2)->Position = Windows::Foundation::Numerics::float3(size / 2.0f, size / 2.0f, size / 2.0f);
		data->get(2)->Normal = Windows::Foundation::Numerics::float3(1.0f, 0.0f, -1.0f);
		data->get(2)->TextureCoordinate = Windows::Foundation::Numerics::float2(0.0f, 0.0f);

		data->get(3)->Position = Windows::Foundation::Numerics::float3(-size / 2.0f, size / 2.0f, size / 2.0f);
		data->get(3)->Normal = Windows::Foundation::Numerics::float3(-1.0f, 1.0f, 1.0f);
		data->get(3)->TextureCoordinate = Windows::Foundation::Numerics::float2(0.0f, 0.0f);

		data->get(4)->Position = Windows::Foundation::Numerics::float3(-size / 2.0f, -size / 2.0f, -size / 2.0f);
		data->get(4)->Normal = Windows::Foundation::Numerics::float3(-1.0f, -1.0f, -1.0f);
		data->get(4)->TextureCoordinate = Windows::Foundation::Numerics::float2(0.0f, 0.0f);

		data->get(5)->Position = Windows::Foundation::Numerics::float3(size / 2.0f, -size / 2.0f, -size / 2.0f);
		data->get(5)->Normal = Windows::Foundation::Numerics::float3(1.0f, -1.0f, -1.0f);
		data->get(5)->TextureCoordinate = Windows::Foundation::Numerics::float2(0.0f, 0.0f);

		data->get(6)->Position = Windows::Foundation::Numerics::float3(size / 2.0f, size / 2.0f, -size / 2.0f);
		data->get(6)->Normal = Windows::Foundation::Numerics::float3(1.0f, 1.0f, -1.0f);
		data->get(6)->TextureCoordinate = Windows::Foundation::Numerics::float2(0.0f, 0.0f);

		data->get(7)->Position = Windows::Foundation::Numerics::float3(-size / 2.0f, size / 2.0f, -size / 2.0f);
		data->get(7)->Normal = Windows::Foundation::Numerics::float3(-1.0f, 1.0f, -1.0f);
		data->get(7)->TextureCoordinate = Windows::Foundation::Numerics::float2(0.0f, 0.0f);

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

		UINT32 stride = sizeof(VertexPositionNormalTexture);
		VertexBuffer^ vB = ref new VertexBuffer(data->Data, 8 * sizeof(VertexPositionNormalTexture), stride, 0U, device);

		return ref new Mesh(vB, iB, material);
	}
	Mesh^ CreateTriangle(_In_ float size, _In_ MaterialInstance^ material, _In_ DeviceDX11^ device)
	{
		Platform::Array<VertexPositionNormalTexture^>^ data;

		data->get(0)->Position = Windows::Foundation::Numerics::float3(0.5f, 0.5f, 0.5f);
		data->get(0)->Normal = Windows::Foundation::Numerics::float3(0.0f, 0.0f, -1.0f);
		data->get(0)->TextureCoordinate = Windows::Foundation::Numerics::float2(0.0f, 0.0f);

		data->get(1)->Position = Windows::Foundation::Numerics::float3(0.5f, -0.5f, 0.5f);
		data->get(1)->Normal = Windows::Foundation::Numerics::float3(0.0f, 0.0f, -1.0f);
		data->get(1)->TextureCoordinate = Windows::Foundation::Numerics::float2(0.5f, 1.0f);

		data->get(1)->Position = Windows::Foundation::Numerics::float3(-0.5f, -0.5f, 0.5f);
		data->get(1)->Normal = Windows::Foundation::Numerics::float3(0.0f, 0.0f, -1.0f);
		data->get(1)->TextureCoordinate = Windows::Foundation::Numerics::float2(1.0f, 0.0f);

		WORD indices[] =
		{
			0, 1, 2
		};

		IndexBuffer^ iB = ref new IndexBuffer(indices, 3, device);
		UINT32 stride = sizeof(VertexPositionNormalTexture);
		VertexBuffer^ vB = ref new VertexBuffer(data->Data, 3 * sizeof(VertexPositionNormalTexture), stride, 0U, device);

		return ref new Mesh(vB, iB, material);
	}
}