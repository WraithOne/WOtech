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
///			Edited:		01.05.2018
///
////////////////////////////////////////////////////////////////////////////

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <Materials.h>
#include <DeviceDX11.h>
#include <Utilities.h>
#include <DXWrapper.h>

namespace WOtech
{
	///////////////////////
	// Struct DirectionalLight
	///////////////////////
	WOtech::DirectionalLight::DirectionalLight()
	{
		Direction = DirectX::g_XMOne;
		DiffuseColor = DirectX::g_XMOne;
		SpecularColor = DirectX::g_XMOne;
	}

	///////////////////////
	// Struct MaterialMatrices
	///////////////////////
	MaterialMatrices::MaterialMatrices()
	{
		World = DirectX::XMMatrixIdentity();
		View = DirectX::XMMatrixIdentity();
		Projection = DirectX::XMMatrixIdentity();
		worldView = DirectX::XMMatrixIdentity();
	}

	void MaterialMatrices::setConstants(_In_ DirectX::XMMATRIX& worldViewProjectionConstant, _In_ DirectX::XMMATRIX& worldConstant, _In_ DirectX::XMMATRIX& worldInverseConstant)
	{
		worldView = XMMatrixMultiply(World, View);
		worldConstant = World;
		worldInverseConstant = WorldInverse;
		worldViewProjectionConstant = XMMatrixTranspose(XMMatrixMultiply(worldView, Projection));
	}

	///////////////////////
	// Struct MaterialColor
	///////////////////////
	MaterialColor::MaterialColor()
	{
		Alpha = 1.0f;
		DiffuseColor = DirectX::g_XMOne;
	}

	void MaterialColor::setConstants(_In_ DirectX::XMVECTOR& diffuseColorConstant)
	{
	}

	///////////////////////
	// Struct MaterialLights
	///////////////////////
	MaterialLights::MaterialLights()
	{
		EmissiveColor = DirectX::g_XMZero;
		AmbientLightColor = DirectX::g_XMZero;

		for (int i = 0; i < MaxDirectionalLights; i++)
		{
			LightEnabled[i] = 0;
		}
	}

	void MaterialLights::setConstants(_In_ MaterialMatrices const & matrices, _In_ DirectX::XMVECTOR & emissiveColor, _In_ DirectX::XMMATRIX & worldConstant, _In_ DirectX::XMVECTOR worldInverseTransposeConstant[3], _In_ DirectX::XMVECTOR & eyePositionConstant, _In_ DirectX::XMVECTOR & diffuseColorConstant, _In_ DirectX::XMVECTOR & emissiveColorConstant, _In_ bool lightingEnabled)
	{
	}

	///////////////////////
	// BasicMaterial
	///////////////////////
	BasicMaterial::BasicMaterial(_In_ VertexShader^ Vshader, _In_ PixelShader^ Pshader, _In_ DeviceDX11^ device)
	{
		m_constants = { 0 };
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

	void BasicMaterial::setWorld(_In_ Windows::Foundation::Numerics::float4x4 world)
	{
		m_matrices.World = WOtech::DXWrapper::XMLoadFloat4x4(world);
	}
	void BasicMaterial::setWorldInverse(_In_ Windows::Foundation::Numerics::float4x4 worldInverse)
	{
		m_matrices.WorldInverse = WOtech::DXWrapper::XMLoadFloat4x4(worldInverse);
	}
	void BasicMaterial::setView(_In_ Windows::Foundation::Numerics::float4x4 view)
	{
		m_matrices.View = WOtech::DXWrapper::XMLoadFloat4x4(view);
	}
	void BasicMaterial::setProjection(_In_ Windows::Foundation::Numerics::float4x4 projection)
	{
		m_matrices.Projection = WOtech::DXWrapper::XMLoadFloat4x4(projection);
	}

	void BasicMaterial::setMatrices(_In_ Windows::Foundation::Numerics::float4x4 world, _In_ Windows::Foundation::Numerics::float4x4 worldInverse, _In_ Windows::Foundation::Numerics::float4x4 view, _In_ Windows::Foundation::Numerics::float4x4 projection)
	{
		m_matrices.World = WOtech::DXWrapper::XMLoadFloat4x4(world);
		m_matrices.WorldInverse = WOtech::DXWrapper::XMLoadFloat4x4(worldInverse);
		m_matrices.View = WOtech::DXWrapper::XMLoadFloat4x4(view);
		m_matrices.Projection = WOtech::DXWrapper::XMLoadFloat4x4(projection);
	}

	void WOtech::BasicMaterial::setConstants(_In_ DeviceDX11^ device)
	{
		m_matrices.setConstants(m_constants.worldViewProj, m_constants.world, m_constants.worldInverse);
		auto context = device->getContext();

		// Update Constantbuffer
		context->UpdateSubresource1(m_constantBuffer.Get(), 0, NULL, &m_constants, 0, 0, 0);

		// set Constantbuffer
		context->CSSetConstantBuffers1(0, 1, m_constantBuffer.GetAddressOf(), nullptr, nullptr);
	}
}