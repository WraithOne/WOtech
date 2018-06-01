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
///			Edited:		01.05.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "materials.h"
#include "ForwardRenderer.h"
#include "DeviceDX11.h"
#include "Utilities.h"

namespace WOtech
{
	ForwardRenderer::ForwardRenderer(_In_ DeviceDX11^ device)
	{
		m_device = device;
		m_beginRender = false;
	}
	void ForwardRenderer::Begin()
	{
		if (m_beginRender)
		{
			throw Platform::Exception::CreateException(E_FAIL, "Begin was called before EndD");
		}

		m_CommandQueue.clear();

		m_device->Clear(m_clearColor);
	}
	void ForwardRenderer::Submit(_In_ Mesh^ mesh, _In_ Camera^ camera)
	{
		RenderCommand command;
		command.mesh = mesh;
		command.uniforms.WorldMatrix = WOtech::DXWrapper::wrapXMMATRIX(DirectX::XMMatrixTransformation(DirectX::g_XMZero,
			DirectX::XMQuaternionIdentity(),
			WOtech::DXWrapper::XMLoadFloat3(mesh->getScaling()),
			DirectX::g_XMZero,
			WOtech::DXWrapper::XMLoadFloat3(mesh->getRotation()),
			WOtech::DXWrapper::XMLoadFloat3(mesh->getPosition())));

		command.uniforms.WorldInverseMatrix = WOtech::DXWrapper::wrapXMFloat4x4(camera->InverseMatrix());
		command.uniforms.ProjectionMatrix = WOtech::DXWrapper::wrapXMFloat4x4(camera->ProjectionMatrix());
		command.uniforms.ViewMatrix = WOtech::DXWrapper::wrapXMFloat4x4(camera->ViewMatrix());

		m_CommandQueue.push_back(command);
	}
	void ForwardRenderer::Submit()
	{
		// for lights
	}
	void ForwardRenderer::End()
	{
		if (!m_beginRender)
		{
			throw Platform::Exception::CreateException(E_FAIL, "End was called before Begin");
		}

		// do sorting here

		for (uint32 i = 0; i < m_CommandQueue.size(); i++)
		{
			// Submit Shaders, Textures
			const RenderCommand& command = m_CommandQueue[i];

			auto materialMatrices = dynamic_cast<WOtech::IMaterialMatrices^>(command.mesh->GetMaterial());
			if (materialMatrices)
				materialMatrices->setMatrices(command.uniforms.WorldMatrix, command.uniforms.WorldInverseMatrix, command.uniforms.ViewMatrix, command.uniforms.ProjectionMatrix);

			command.mesh->bindMaterial(m_device);

			// Submit Vertex and Index data and render the final mesh
			command.mesh->Render(m_device);
		}
	}
	void ForwardRenderer::Present()
	{
		m_device->Present();
	}

	void ForwardRenderer::Init(_In_ Windows::UI::Color clearColor)
	{
		m_clearColor = clearColor;
	}

	DeviceDX11 ^ ForwardRenderer::getDeviceDX11()
	{
		return m_device;
	}
}