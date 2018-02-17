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
///			Edited:		18.02.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "DeferredRenderer.h"
#include "Utilities.h"

using namespace Windows::Foundation::Numerics;
using namespace Windows::UI;

namespace WOtech
{
	DeferredRenderer::DeferredRenderer(_In_ DeviceDX11^ device)
	{
		m_device = device;
		m_beginRender = false;
	}
	void DeferredRenderer::Init(_In_ Color clearColor)
	{
		m_clearColor = clearColor;
	}
	DeviceDX11^ DeferredRenderer::getDeviceDX11()
	{
		return m_device;
	}
	void DeferredRenderer::Begin()
	{
		if (m_beginRender)
		{
			throw Platform::Exception::CreateException(E_FAIL, "Begin was called before EndD");
		}

		m_CommandQueue.clear();

		m_device->Clear(m_clearColor);
	}
	void DeferredRenderer::Submit(_In_ Mesh^ mesh, _In_ Camera^ camera)
	{
	}
	void DeferredRenderer::Submit()
	{
	}
	void DeferredRenderer::End()
	{
		if (!m_beginRender)
		{
			throw Platform::Exception::CreateException(E_FAIL, "End was called before Begin");
		}
	}
	void DeferredRenderer::Present()
	{
		m_device->Present();
	}
}