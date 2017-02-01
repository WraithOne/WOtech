////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: ForwardRenderer.cpp
///
///			Created:	21.02.2016
///			Edited:		27.11.2016
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "ForwardRenderer.h"
#include "DeviceDX11.h"
#include "Utilities.h"

using namespace WOtech::DXWrapper;
using namespace Windows::Foundation::Numerics;
using namespace Windows::UI;

namespace WOtech
{
	ForwardRenderer::ForwardRenderer(DeviceDX11^ device)
	{
		m_device = device;
		Init();
	}
	void ForwardRenderer::Begin()
	{
		m_CommandQueue.clear();

		Color clearColor = Colors::Gray;
		m_device->Clear(clearColor);
	}
	void ForwardRenderer::Submit(Mesh^ mesh, Camera^ camera, float4x4 transform)
	{
		RenderCommand command;
		command.mesh = mesh;
		command.uniforms.ModelMatrix = transform;
		command.uniforms.ProjectionMatrix = camera->Projection();
		command.uniforms.ViewMatrix = camera->View();
		command.uniforms.WorldMatrix = camera->World();

		m_CommandQueue.push_back(command);
	}
	void ForwardRenderer::Submit()
	{
		// for lights
	}
	void ForwardRenderer::End()
	{
		// do sorting here
	}
	void ForwardRenderer::Present()
	{
		for (uint32 i = 0; i < m_CommandQueue.size(); i++)
		{
			// Submit Shaders, Textures
			const RenderCommand& command = m_CommandQueue[i];
			command.mesh->GetMaterialInstance()->bindMaterialInstance(m_device);

			// Submit Uniforms
			m_device->GetContext()->UpdateSubresource(m_worldCB.Get(), 0, 0, &command.uniforms.WorldMatrix, 0, 0);
			m_device->GetContext()->UpdateSubresource(m_viewCB.Get(), 0, 0, &command.uniforms.ViewMatrix, 0, 0);
			m_device->GetContext()->UpdateSubresource(m_pojectionCB.Get(), 0, 0, &command.uniforms.ProjectionMatrix, 0, 0);
			m_device->GetContext()->UpdateSubresource(m_modelCB.Get(), 0, 0, &command.uniforms.ModelMatrix, 0, 0);
			m_device->GetContext()->VSSetConstantBuffers(0, 1, m_worldCB.GetAddressOf());
			m_device->GetContext()->VSSetConstantBuffers(1, 1, m_viewCB.GetAddressOf());
			m_device->GetContext()->VSSetConstantBuffers(2, 1, m_pojectionCB.GetAddressOf());
			m_device->GetContext()->VSSetConstantBuffers(3, 1, m_modelCB.GetAddressOf());

			// Submit Vertex and Index data and render the final mesh
			command.mesh->Render(m_device);
		}
			
		m_device->Present();
	}

	void ForwardRenderer::Init()
	{
		HRESULT hr;
		D3D11_BUFFER_DESC constDesc;
		ZeroMemory(&constDesc, sizeof(constDesc));
		constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constDesc.ByteWidth = sizeof(DirectX::XMMATRIX);
		constDesc.Usage = D3D11_USAGE_DEFAULT;
		constDesc.CPUAccessFlags = 0;
		constDesc.StructureByteStride = 0;
		constDesc.MiscFlags = 0;

		hr = m_device->getDevice()->CreateBuffer(&constDesc, 0, m_worldCB.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);

		hr = m_device->getDevice()->CreateBuffer(&constDesc, 0, m_viewCB.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);

		hr = m_device->getDevice()->CreateBuffer(&constDesc, 0, m_pojectionCB.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);

		hr = m_device->getDevice()->CreateBuffer(&constDesc, 0, m_modelCB.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);
	}

	DeviceDX11 ^ ForwardRenderer::getDeviceDX11()
	{
		return m_device;
	}
}