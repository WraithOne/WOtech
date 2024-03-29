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
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <DeferredRenderer.h>
#include <Utilities.h>

namespace WOtech
{
	DeferredRenderer::DeferredRenderer(_In_ DeviceDX11^ device)
	{
		m_device = device;
		m_beginRender = false;
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
		if (m_beginRender)
		{
			throw Platform::Exception::CreateException(E_FAIL, "Begin was called before End");
		}

		m_CommandQueue.clear();
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