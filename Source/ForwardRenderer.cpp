////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: ForwardRenderer.cpp
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
#include "ForwardRenderer.h"
#include "DeviceDX11.h"
#include "Utilities.h"

using namespace WOtech::DXWrapper;
using namespace Windows::Foundation::Numerics;
using namespace Windows::UI;

namespace WOtech
{
	ForwardRenderer::ForwardRenderer(_In_ DeviceDX11^ device)
	{
		m_device = device;
	}
	void ForwardRenderer::Begin()
	{
		m_CommandQueue.clear();

		m_device->Clear(m_clearColor);
	}
	void ForwardRenderer::Submit(_In_ Mesh^ mesh, _In_ Camera^ camera, _In_ float4x4 transform)
	{
		RenderCommand command;
		command.mesh = mesh;
		command.uniforms.ModelMatrix = wrapFloat4x4(transform);
		command.uniforms.ProjectionMatrix = camera->ProjectionMatrix();
		command.uniforms.ViewMatrix = camera->ViewMatrix();

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

			auto context = m_device->getContext();

			// Submit Uniforms
			context->UpdateSubresource1(m_constantBuffer.Get(), 0, NULL, &command.uniforms, 0, 0, 0);
			context->VSSetConstantBuffers1(0, 1, m_constantBuffer.GetAddressOf(), nullptr, nullptr);
			
			// Submit Vertex and Index data and render the final mesh
			command.mesh->Render(m_device);
		}

		m_device->Present();
	}

	void ForwardRenderer::Init(_In_ Color clearColor)
	{
		m_clearColor = clearColor;

		HRESULT hr;
		D3D11_BUFFER_DESC constDesc;
		ZeroMemory(&constDesc, sizeof(constDesc));
		constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constDesc.ByteWidth = sizeof(RendererUniforms); // todo: Shader specific Uniforms
		constDesc.Usage = D3D11_USAGE_DEFAULT;
		constDesc.CPUAccessFlags = 0;
		constDesc.StructureByteStride = 0;
		constDesc.MiscFlags = 0;

		auto device = m_device->getDevice();
		hr = device->CreateBuffer(&constDesc, nullptr, &m_constantBuffer);
		ThrowIfFailed(hr);
	}

	DeviceDX11 ^ ForwardRenderer::getDeviceDX11()
	{
		return m_device;
	}
}