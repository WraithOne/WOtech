////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Buffer.cpp
///
///			Description:
///
///			Created:	23.02.2016
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <3DComponents.h>
#include <DeviceDX11.h>
#include <Utilities.h>

namespace WOtech
{
	///////////////////////////////////////////////////////////////////
	/// Vertex Buffer
	///////////////////////////////////////////////////////////////////
	VertexBuffer::VertexBuffer(_In_ Platform::IntPtr data, _In_ UINT size, _In_  UINT stride, _In_ UINT offset, _In_ DeviceDX11^ device)
	{
		CreateBuffer(data, size, device);
		m_stride = stride;
		m_offset = offset;
	}

	void VertexBuffer::SubmitBuffer(_In_ DeviceDX11^ device)
	{
		auto context = device->getContext();

		context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &m_stride, &m_offset);
	}

	void VertexBuffer::setOffset(_In_ UINT offset)
	{
		m_offset = offset;
	}

	void VertexBuffer::setStride(_In_ UINT stride)
	{
		m_stride = stride;
	}

	UINT32 VertexBuffer::getStride()
	{
		return m_stride;
	}

	UINT32 VertexBuffer::getOffset()
	{
		return m_offset;
	}

	void VertexBuffer::CreateBuffer(_In_ Platform::IntPtr data, _In_  UINT size, _In_  DeviceDX11^ device)
	{
		HRESULT hr;

		D3D11_BUFFER_DESC vertexDesc;
		ZeroMemory(&vertexDesc, sizeof(vertexDesc));
		vertexDesc.Usage = D3D11_USAGE_DYNAMIC;
		vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexDesc.ByteWidth = size;
		vertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vertexDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA resourceData;
		ZeroMemory(&resourceData, sizeof(resourceData));
		resourceData.pSysMem = (void*)data; // todo: safecheck void* to Intptr to void*
		resourceData.SysMemPitch = 0;
		resourceData.SysMemSlicePitch = 0;

		hr = device->getDevice()->CreateBuffer(&vertexDesc, &resourceData, m_vertexBuffer.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);
	}

	///////////////////////////////////////////////////////////////////
	/// Index Buffer
	///////////////////////////////////////////////////////////////////
	IndexBuffer::IndexBuffer(_In_ Platform::IntPtr data, _In_  UINT count, _In_  DeviceDX11^ device)
	{
		m_count = count;

		CreateBuffer(data, count, device);
	}
	void IndexBuffer::SubmitBuffer(_In_ DeviceDX11^ device)
	{
		auto context = device->getContext();

		context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
	void IndexBuffer::CreateBuffer(_In_ Platform::IntPtr data, _In_  UINT count, _In_  DeviceDX11^ device)
	{
		HRESULT hr;

		D3D11_BUFFER_DESC indexDesc;
		ZeroMemory(&indexDesc, sizeof(indexDesc));
		indexDesc.Usage = D3D11_USAGE_DEFAULT;
		indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexDesc.ByteWidth = count;
		indexDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA resourceData;
		ZeroMemory(&resourceData, sizeof(resourceData));
		resourceData.pSysMem = (void*)data; // todo: safecheck void* to Intptr to void*
		resourceData.SysMemPitch = 0;
		resourceData.SysMemSlicePitch = 0;

		hr = device->getDevice()->CreateBuffer(&indexDesc, &resourceData, m_indexBuffer.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);
	}

	///////////////////////////////////////////////////////////////////
	/// Constant Buffer
	///////////////////////////////////////////////////////////////////

	WOtech::ConstantBuffer::ConstantBuffer()
	{
		throw ref new Platform::NotImplementedException();
	}
	ConstantBuffer::~ConstantBuffer()
	{
		throw ref new Platform::NotImplementedException();
	}
}// namespace WOtech