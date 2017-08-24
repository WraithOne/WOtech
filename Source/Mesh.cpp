////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Mesh.cpp
///
///			Description:
///
///			Created:	23.02.2016
///			Edited:		21.08.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "3DComponents.h"
#include "DeviceDX11.h"

namespace WOtech
{
	Mesh::Mesh(_In_ VertexBuffer^ vertexBuffer, _In_ IndexBuffer^ indexBuffer, _In_ IMaterial^ material)
	{
		m_vertexBuffer = vertexBuffer;
		m_indexBuffer = indexBuffer;
		m_material = material;

		m_position = { 0 };
		m_scaling = { 0 };
		m_rotation = { 0 };
	}

	void WOtech::Mesh::bindMaterial(_In_ DeviceDX11 ^ device)
	{
		m_material->bindMaterial(device);
	}

	void Mesh::Render(_In_ DeviceDX11^ device)
	{
		m_material->bindMaterial(device);

		m_vertexBuffer->SubmitBuffer(device);
		m_indexBuffer->SubmitBuffer(device);

		auto context = device->getContext();

		context->DrawIndexed(m_indexBuffer->getCount(), 0, 0);
	}
}// namespace WOtech