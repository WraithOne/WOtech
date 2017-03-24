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
///			Edited:		11.11.2016
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include <windows.foundation.numerics.h>
#include <WindowsNumerics.h>
#include "DefaultFactory.h"

using namespace DirectX;
using namespace WOtech::DXWrapper;
using namespace Windows::Foundation::Numerics;

namespace WOtech
{
	Mesh^ CreateCube(_In_ float32 size, _In_ MaterialInstance^ material, _In_ DeviceDX11^ device)
	{
		VertexPositionNormalTexture data[] =
		{
			{ float3(-size / 2.0f, -size / 2.0f, size / 2.0f) ,float3(0.0f, 0.0f, -1.0f), float2(0.0f, 0.0f) },
			{ float3(size / 2.0f, -size / 2.0f, size / 2.0f), float3(0.0f, 0.0f, 1.0f), float2(0.0f, 0.0f) },
			{ float3(size / 2.0f, size / 2.0f, size / 2.0f),float3(1.0f, 0.0f, -1.0f), float2(0.0f, 0.0f) },
			{ float3(-size / 2.0f, size / 2.0f, size / 2.0f), float3(-1.0f, 1.0f, 1.0f), float2(0.0f, 0.0f) },
			{ float3(-size / 2.0f, -size / 2.0f, -size / 2.0f), float3(-1.0f, -1.0f, -1.0f), float2(0.0f, 0.0f) },
			{ float3(size / 2.0f, -size / 2.0f, -size / 2.0f), float3(1.0f, -1.0f, -1.0f), float2(0.0f, 0.0f) },
			{ float3(size / 2.0f, size / 2.0f, -size / 2.0f), float3(1.0f, 1.0f, -1.0f), float2(0.0f, 0.0f) },
			{ float3(-size / 2.0f, size / 2.0f, -size / 2.0f), float3(-1.0f, 1.0f, -1.0f), float2(0.0f, 0.0f) }
		};

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
		VertexBuffer^ vB = ref new VertexBuffer(data, 8 * sizeof(VertexPositionNormalTexture), stride, 0U, device);

		return ref new Mesh(vB, iB, material);
	}
	Mesh^ CreateTriangle(_In_ float32 size, _In_ MaterialInstance^ material, _In_ DeviceDX11^ device)
	{
		VertexPositionNormalTexture data[] =
		{
			{ float3(0.5f, 0.5f, 0.5f), float3(0.0f, 0.0f, -1.0f), float2(0.0f, 0.0f) },
			{ float3(0.5f, -0.5f, 0.5f), float3(0.0f, 0.0f, -1.0f), float2(0.5f, 1.0f) },
			{ float3(-0.5f, -0.5f, 0.5f), float3(0.0f, 0.0f, -1.0f), float2(1.0f, 0.0f) }
		};

		WORD indices[] =
		{
			0, 1, 2
		};

		IndexBuffer^ iB = ref new IndexBuffer(indices, 3, device);
		UINT32 stride = sizeof(VertexPositionNormalTexture);
		VertexBuffer^ vB = ref new VertexBuffer(data, 3 * sizeof(VertexPositionNormalTexture), stride, 0U, device);

		return ref new Mesh(vB, iB, material);
	}
}