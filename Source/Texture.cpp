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
///			Edited:		15.08.2017
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

using namespace Platform;
using namespace DirectX;

namespace WOtech
{
	Texture::Texture(_In_ String^ filename)
	{
		m_filenName = filename;
	}

	Platform::Boolean Texture::Load(_In_ DeviceDX11^ device)
	{
		CreateWICTextureFromFile(device->getDevice(), device->getContext(), m_filenName->Data(), nullptr, m_texture.ReleaseAndGetAddressOf(), 2048);
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

	Platform::String ^ Texture::getFilename()
	{
		return m_filenName;
	}
}//namespace WOtech