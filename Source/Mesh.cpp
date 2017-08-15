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
///			Edited:		15.08.2017
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
	Mesh::Mesh(VertexBuffer^ vertexBuffer, IndexBuffer^ indexBuffer, MaterialInstance^ materialInstance)
	{
		m_vertexBuffer = vertexBuffer;
		m_IndexBuffer = indexBuffer;
		m_MaterialInstance = materialInstance;
	}

	void Mesh::Render(DeviceDX11^ device)
	{
		m_MaterialInstance->bindMaterialInstance(device);

		m_vertexBuffer->SubmitBuffer(device);
		m_IndexBuffer->SubmitBuffer(device);

		auto context = device->getContext();

		context->DrawIndexed(m_IndexBuffer->getCount(), 0, 0);
	}
}// namespace WOtech