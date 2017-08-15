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
///			Edited:		15.08.2017
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
		PIXBEGINEVENT(PIX_COLOR_DEFAULT, L"DeferredRenderer::Begin");
		m_CommandQueue.clear();

		m_device->Clear(m_clearColor);
		PIXENDEVENT();
	}
	void DeferredRenderer::Submit(_In_ Mesh^ mesh, _In_ Camera^ camera, _In_ float4x4 transform)
	{
		PIXBEGINEVENT(PIX_COLOR_DEFAULT, L"DeferredRenderer::Submit Mesh");
		PIXENDEVENT();
	}
	void DeferredRenderer::Submit()
	{
		PIXBEGINEVENT(PIX_COLOR_DEFAULT, L"DeferredRenderer::Submit Lights");
		PIXENDEVENT();
	}
	void DeferredRenderer::End()
	{
		PIXBEGINEVENT(PIX_COLOR_DEFAULT, L"DeferredRenderer::End");
		PIXENDEVENT();
	}
	void DeferredRenderer::Present()
	{
		PIXBEGINEVENT(PIX_COLOR_DEFAULT, L"DeferredRenderer::Present");
		PIXENDEVENT();
	}
}