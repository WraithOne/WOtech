////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: Buffer.cpp
///
///			Created:	23.02.2016
///			Edited:		11.11.2016
///
////////////////////////////////////////////////////////////////////////////

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "3DComponents.h"
#include "DeviceDX11.h"
#include "Utilities.h"

using namespace WOtech::DXWrapper;

namespace WOtech
{
	///////////////////////////////////////////////////////////////////
	/// Vertex Buffer
	///////////////////////////////////////////////////////////////////
	VertexBuffer::VertexBuffer(void* data, UINT32 size, _In_  UINT32 stride, DeviceDX11^ device)
	{
		CreateBuffer(data, size, device);
		m_stride = stride;
	}

	void VertexBuffer::SubmitBuffer(_In_ DeviceDX11^ device)
	{
		device->GetContext()->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &m_stride, &m_offset);
	}

	void VertexBuffer::setOffset(UINT32 offset)
	{
		m_offset = offset;
	}

	UINT32 VertexBuffer::getStride()
	{
		return m_stride;
	}

	UINT32 VertexBuffer::getOffset()
	{
		return m_offset;
	}

	void VertexBuffer::CreateBuffer(_In_ void* data, _In_  UINT32 size, _In_  DeviceDX11^ device)
	{
		HRESULT hr;

		D3D11_BUFFER_DESC vertexDesc;
		ZeroMemory(&vertexDesc, sizeof(vertexDesc));
		vertexDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexDesc.ByteWidth = size;
		vertexDesc.CPUAccessFlags = 0;
		vertexDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA resourceData;
		ZeroMemory(&resourceData, sizeof(resourceData));
		resourceData.pSysMem = data;
		resourceData.SysMemPitch = 0;
		resourceData.SysMemSlicePitch = 0;

		hr = device->getDevice()->CreateBuffer(&vertexDesc, &resourceData, m_vertexBuffer.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);
	}

	///////////////////////////////////////////////////////////////////
	/// Index Buffer
	///////////////////////////////////////////////////////////////////
	IndexBuffer::IndexBuffer(_In_ void* data, _In_  UINT32 count, _In_  DeviceDX11^ device)
	{
		m_count = count;
			
		CreateBuffer(data, count, device);
	}
	void IndexBuffer::SubmitBuffer(_In_ DeviceDX11^ device)
	{
		device->GetContext()->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
		device->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
	void IndexBuffer::CreateBuffer(_In_ void* data, _In_  UINT32 count, _In_  DeviceDX11^ device)
	{
		HRESULT hr;

		D3D11_BUFFER_DESC indexDesc;
		ZeroMemory(&indexDesc, sizeof(indexDesc));
		indexDesc.Usage = D3D11_USAGE_DEFAULT;
		indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexDesc.ByteWidth = sizeof(WORD)* count;
		indexDesc.CPUAccessFlags = 0;
			
		D3D11_SUBRESOURCE_DATA resourceData;
		ZeroMemory(&resourceData, sizeof(resourceData));
		resourceData.pSysMem = data;

		hr = device->getDevice()->CreateBuffer(&indexDesc, &resourceData, m_indexBuffer.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);
	}
}// namespace WOtech