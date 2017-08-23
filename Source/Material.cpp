////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Material.cpp
///
///			Description:
///
///			Created:	25.02.2016
///			Edited:		22.08.2017
///
////////////////////////////////////////////////////////////////////////////

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Materials.h"
#include "DeviceDX11.h"
#include "Utilities.h"
#include "DXWrapper.h"

using namespace Windows::Foundation::Numerics;
using namespace DirectX;

namespace WOtech
{
	///////////////////////
	// Struct DirectionalLight
	///////////////////////
	WOtech::DirectionalLight::DirectionalLight()
	{
		Direction =		g_XMOne;
		DiffuseColor =	g_XMOne;
		SpecularColor =	g_XMOne;
	}

	///////////////////////
	// Struct MaterialMatrices
	///////////////////////
	MaterialMatrices::MaterialMatrices()
	{
		World =			XMMatrixIdentity();
		View =			XMMatrixIdentity();
		Projection =	XMMatrixIdentity();
		worldView =		XMMatrixIdentity();
	}

	void MaterialMatrices::setConstants(_In_ XMMATRIX& worldViewProjectionConstant)
	{
		worldView = XMMatrixMultiply(World, View);

		worldViewProjectionConstant = XMMatrixTranspose(XMMatrixMultiply(worldView, Projection));
	}

	///////////////////////
	// Struct MaterialColor
	///////////////////////
	MaterialColor::MaterialColor()
	{
		Alpha =			1.0f;
		DiffuseColor =	DirectX::g_XMOne;
	}

	void MaterialColor::setConstants(_In_ XMVECTOR& diffuseColorConstant)
	{
	}

	///////////////////////
	// Struct MaterialLights
	///////////////////////
	MaterialLights::MaterialLights()
	{
		EmissiveColor =		g_XMZero;
		AmbientLightColor =	g_XMZero;

		for (int i = 0; i < MaxDirectionalLights; i++)
		{
			LightEnabled[i] = 0;
		}
	}

	void MaterialLights::setConstants(_In_ MaterialMatrices const & matrices, _In_ XMVECTOR & emissiveColor, _In_ XMMATRIX & worldConstant, _In_ XMVECTOR worldInverseTransposeConstant[3], _In_ XMVECTOR & eyePositionConstant, _In_ XMVECTOR & diffuseColorConstant, _In_ XMVECTOR & emissiveColorConstant, _In_ bool lightingEnabled)
	{
	}

	///////////////////////
	// BasicMaterial
	///////////////////////
	BasicMaterial::BasicMaterial(_In_ VertexShader^ Vshader, _In_ PixelShader^ Pshader, _In_ DeviceDX11^ device)
	{
		m_vertexShader = Vshader;
		m_pixelShader = Pshader;

		HRESULT hr;
		D3D11_BUFFER_DESC constDesc;
		ZeroMemory(&constDesc, sizeof(constDesc));
		constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constDesc.ByteWidth = sizeof(MaterialConstants);
		constDesc.Usage = D3D11_USAGE_DEFAULT;
		constDesc.CPUAccessFlags = 0;
		constDesc.StructureByteStride = 0;
		constDesc.MiscFlags = 0;

		auto DXdevice = device->getDevice();
		hr = DXdevice->CreateBuffer(&constDesc, nullptr, &m_constantBuffer);
		ThrowIfFailed(hr);
	}

	void BasicMaterial::bindMaterial(_In_ DeviceDX11^ device)
	{
		auto context = device->getContext();

		// Submit Uniforms
		setConstants(device);

		// Set VertexShader
		context->IASetInputLayout(m_vertexShader->getInputLayout());
		context->VSSetShader(m_vertexShader->getShader(), nullptr, 0);

		// Set PixelShader
		context->PSSetShader(m_pixelShader->getShader(), nullptr, 0);
	}
	void BasicMaterial::unbindMaterial(_In_ DeviceDX11^ device)
	{
		auto context = device->getContext();

		context->IASetInputLayout(nullptr);
		context->VSSetShader(nullptr, 0, 0);

		context->PSSetShader(nullptr, 0, 0);
	}

	void BasicMaterial::setWorld(_In_ float4x4 world)
	{
		m_matrices.World = DXWrapper::wrapXMMATRIX(world);
	}
	void BasicMaterial::setView(_In_ float4x4 view)
	{
		m_matrices.View = DXWrapper::wrapXMMATRIX(view);
	}
	void BasicMaterial::setProjection(_In_ float4x4 projection)
	{
		m_matrices.Projection = DXWrapper::wrapXMMATRIX(projection);
	}
	void BasicMaterial::setMatrices(_In_ float4x4 world, _In_ float4x4 view, _In_ float4x4 projection)
	{
		m_matrices.World = DXWrapper::wrapXMMATRIX(world);
		m_matrices.View = DXWrapper::wrapXMMATRIX(view);
		m_matrices.Projection = DXWrapper::wrapXMMATRIX(projection);
	}

	void WOtech::BasicMaterial::setConstants(_In_ DeviceDX11^ device)
	{
		m_matrices.setConstants(m_constants.worldViewProj);
		auto context = device->getContext();

		context->UpdateSubresource1(m_constantBuffer.Get(), 0, NULL, &m_constants, 0, 0, 0);
	}
}
