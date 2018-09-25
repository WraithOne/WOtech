////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Texture.cpp
///
///			Description:
///
///			Created:	30.08.2014
///			Edited:		25.09.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "DeviceDX11.h"
#include "3DComponents.h"
#include "Utilities.h"
#include "WICTextureLoader.h"

namespace WOtech
{
	Texture::Texture(_In_ Platform::String^ filename)
	{
		m_filenName = filename;
	}

	Platform::Boolean Texture::Load(_In_ DeviceDX11^ device)
	{
		HRESULT hr;

		hr = DirectX::CreateWICTextureFromFile(device->getDevice(), device->getContext(), m_filenName->Data(), nullptr, m_texture.ReleaseAndGetAddressOf(), 2048);

		ThrowIfFailed(hr);
		m_texture->GetDesc(&m_texDESC);

		return true;
	}

	void Texture::SubmitTexture(_In_ DeviceDX11^ device, _In_ uint32 slot)
	{
		auto context = device->getContext();

		context->PSSetShaderResources(slot, 1, m_texture.GetAddressOf());
	}

	ID3D11ShaderResourceView* Texture::getTexture()
	{
		return m_texture.Get();
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC Texture::getDescription()
	{
		return m_texDESC;
	}

	Platform::String ^ Texture::getFilename()
	{
		return m_filenName;
	}
}//namespace WOtech