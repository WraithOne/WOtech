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
///			Edited:		15.08.2017
///
////////////////////////////////////////////////////////////////////////////

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "3DComponents.h"
#include "DeviceDX11.h"
#include "Utilities.h"

namespace WOtech
{
	///////////////////////
	// Material
	///////////////////////
	Material::Material(VertexShader^ Vshader, PixelShader^ Pshader, DeviceDX11^ device) : m_numMatrials(0U)
	{
		m_vertexShader = Vshader;
		m_pixelShader = Pshader;
		
		size_t maxSize = 16;
		m_textures.reserve(maxSize);// todo: reserve to MAX_HW_TEXTURES_SUPPORTET
		m_textures.resize(maxSize);

		D3D11_SAMPLER_DESC samplerDesc;
		ZeroMemory(&samplerDesc, sizeof(samplerDesc));
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		device->getDevice()->CreateSamplerState(&samplerDesc, m_samplerState.ReleaseAndGetAddressOf());
	}

	void Material::bindMaterial(DeviceDX11^ device)
	{
		auto context = device->getContext();

		context->IASetInputLayout(m_vertexShader->getInputLayout());
		context->VSSetShader(m_vertexShader->getShader(), nullptr, 0);

		context->PSSetShader(m_pixelShader->getShader(), nullptr, 0);
		for (uint32 i = 0; i < m_textures.size(); i++)
		{
			if (m_textures.at(i) != nullptr)
				m_textures.at(i)->SubmitTexture(device, i);
		}
		if(m_textures.size() > 0)
			context->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
	}
	void Material::unbindMaterial(DeviceDX11^ device)
	{
		auto context = device->getContext();

		context->IASetInputLayout(nullptr);
		context->VSSetShader(nullptr, 0, 0);

		context->PSSetShader(nullptr, 0, 0);
		context->PSSetShaderResources(0, safe_cast<UINT>(m_textures.size()), nullptr);
		context->PSSetSamplers(0, 1, nullptr);
	}
	void Material::addTexture(Texture^ texture, uint32 slot)
	{
		m_textures.at(slot) = texture;
	}
	///////////////////////
	// MaterialInstance
	///////////////////////
	MaterialInstance::MaterialInstance(Material^ material)
	{
		m_material = nullptr;
		m_material = material;
	}
	void MaterialInstance::bindMaterialInstance(DeviceDX11^ device)
	{
		m_material->bindMaterial(device);
	}
	void MaterialInstance::UnbindMaterialInstance(DeviceDX11^ device)
	{
		m_material->unbindMaterial(device);
	}
}