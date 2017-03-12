////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: DeferredRenderer.cpp
///
///			Description:
///
///			Created:	21.02.2016
///			Edited:		13.11.2016
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include"DeferredRenderer.h"
#include "Utilities.h"

using namespace Windows::Foundation::Numerics;

namespace WOtech
{
	DeferredRenderer::DeferredRenderer(DeviceDX11^ device)
	{
		m_device = device;
	}
	void DeferredRenderer::Init()
	{
	}
	DeviceDX11^ DeferredRenderer::getDeviceDX11()
	{
		return m_device;
	}
	void DeferredRenderer::Begin()
	{
	}
	void DeferredRenderer::Submit(Mesh^ mesh, Camera^ camera, float4x4 transform)
	{
	}
	void DeferredRenderer::Submit()
	{
	}
	void DeferredRenderer::End()
	{
	}
	void DeferredRenderer::Present()
	{
		HRESULT hr = S_OK;

		ThrowIfFailed(hr);
	}
}