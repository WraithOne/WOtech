////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Shader.cpp
///
///			Description:
///
///			Created:	06.05.2014
///			Edited:		08.11.2016
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Graphic.h"
#include "Utilities.h"

#include <stdio.h>
#include <d3dcompiler.h>

using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::ApplicationModel;
using namespace Microsoft::WRL;
using namespace WOtech;
using namespace WOtech::DXWrapper;

namespace WOtech
{
	///////////////////////////////////////////////////////////////////
	/// Vertex Shader
	///////////////////////////////////////////////////////////////////

	VertexShader::VertexShader(_In_ String^ compiledVertexShaderObject)
	{
		m_useCVSO = true;
		m_CVSO = compiledVertexShaderObject;

		m_useInputElementDesc = false;
		m_loadfromFile = false;
		m_useShaderByteCode = false;
		m_shaderByteCode = nullptr;
		m_byteCodeLength = 0U;
	}
	VertexShader::VertexShader(_In_ String^ compiledVertexShaderObject, _In_ const Array<INPUT_ELEMENT_DESC>^ inputElementDesc)
	{
		m_useCVSO = true;
		m_CVSO = compiledVertexShaderObject;

		m_useInputElementDesc = true;
		m_inputElementDesc = inputElementDesc;

		m_loadfromFile = false;
		m_useShaderByteCode = false;
		m_shaderByteCode = nullptr;
		m_byteCodeLength = 0U;
	}
	VertexShader::VertexShader(_In_ String^ filename, _In_ String^ entryPoint)
	{
		m_fileName = filename;
		m_entryPoint = entryPoint;

		m_useInputElementDesc = false;

		m_loadfromFile = false;
		m_useCVSO = false;
		m_useShaderByteCode = false;
		m_shaderByteCode = nullptr;
		m_byteCodeLength = 0U;
	}
	VertexShader::VertexShader(_In_ String^ filename, _In_ String^ entryPoint, _In_ const Array<INPUT_ELEMENT_DESC>^ inputElementDesc)
	{
		m_fileName = filename;
		m_entryPoint = entryPoint;

		m_useInputElementDesc = true;
		m_inputElementDesc = inputElementDesc;

		m_loadfromFile = false;
		m_useCVSO = false;
		m_useShaderByteCode = false;
		m_shaderByteCode = nullptr;
		m_byteCodeLength = 0U;
	}
	VertexShader::VertexShader(_In_ void* ShaderBytecode, _In_ SizeT BytecodeLength, _In_ const Array<INPUT_ELEMENT_DESC>^ inputElementDesc)
	{
		m_useShaderByteCode = true;
		m_shaderByteCode = ShaderBytecode;
		m_byteCodeLength = BytecodeLength;

		m_useInputElementDesc = true;
		m_inputElementDesc = inputElementDesc;

		m_loadfromFile = false;
		m_useCVSO = false;
	}

	void VertexShader::Load(_In_ DeviceDX11 ^ device)
	{
		if (m_loadfromFile)
		{
			// Compile Vertex Shader from file
			ComilefromFile(device, m_fileName, m_entryPoint);

			if (!m_useInputElementDesc)
			{
				// Reflect InputLayout
				ReflectInputLayout(device);
			}
			else
			{
				CreateInputLayout(device);
			}
		}
		if (m_useCVSO)
		{
			// Load Compiled Vertex Shader Object from file
			LoadfromFile(device, m_CVSO);

			if (!m_useInputElementDesc)
			{
				// Reflect InputLayout
				ReflectInputLayout(device);
			}
			else
			{
				CreateInputLayout(device);
			}
		}
		if (m_useShaderByteCode)
		{
			// Load compiled Shader from Bytecode
			LoadfromByteArray(device, m_shaderByteCode, m_byteCodeLength);

			if (!m_inputLayout)
			{
				// Reflect InputLayout
				ReflectInputLayout(device);
			}
		}
	}

	void VertexShader::ComilefromFile(_In_ DeviceDX11^ device, _In_ String^ filename, _In_ String^ entryPoint)
	{
		if (!device || !filename || entryPoint)
			ThrowIfFailed(E_INVALIDARG);

		HRESULT hr;
		ComPtr<ID3DBlob> errorBlob;

		uint32 flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
		flags |= D3DCOMPILE_DEBUG;
#endif

		// Prefer higher CS shader profile when possible as CS 5.0 provides better performance on 11-class hardware.
		LPCSTR profile = (device->getDevice()->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "vs_5_0" : "vs_4_0";

		// Create path/filename string
		String^ path;
		String^ pathfilename;
		StorageFolder^ m_installedLocation = Package::Current->InstalledLocation;
		path = Platform::String::Concat(m_installedLocation->Path, "\\");
		pathfilename = Platform::String::Concat(path, filename);

		const D3D_SHADER_MACRO defines[] =
		{
			"EXAMPLE_DEFINE", "1",
			NULL, NULL
		};

		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &entryPoint->Data()[0], (int)entryPoint->Length(), NULL, 0, NULL, NULL);
		std::string strTo(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &entryPoint->Data()[0], (int)entryPoint->Length(), &strTo[0], size_needed, NULL, NULL);

		//Compile to Blob
		hr = D3DCompileFromFile(pathfilename->Data(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE, strTo.data(), profile, flags, 0, &m_vertexBlob, &errorBlob);
		ThrowIfFailed(hr);

		//Create the VertexShader
		hr = device->getDevice()->CreateVertexShader(m_vertexBlob->GetBufferPointer(), m_vertexBlob->GetBufferSize(), nullptr, &m_vertexShader);
		ThrowIfFailed(hr);
	}
	void VertexShader::LoadfromFile(_In_ DeviceDX11^ device, _In_ String^ compiledVertexShaderObject)
	{
		HRESULT hr;

		// Create path/filename string
		String^ path;
		String^ pathfilename;
		StorageFolder^ m_installedLocation = Package::Current->InstalledLocation;
		path = Platform::String::Concat(m_installedLocation->Path, "\\");
		pathfilename = Platform::String::Concat(path, compiledVertexShaderObject);

		hr = D3DReadFileToBlob(pathfilename->Data(), &m_vertexBlob);
		ThrowIfFailed(hr);

		hr = device->getDevice()->CreateVertexShader(m_vertexBlob->GetBufferPointer(), m_vertexBlob->GetBufferSize(), nullptr, &m_vertexShader);
		ThrowIfFailed(hr);
	}
	void VertexShader::LoadfromByteArray(_In_ DeviceDX11^ device, _In_ IntPtr pShaderBytecode, _In_ SizeT BytecodeLength)
	{
		HRESULT hr;

		hr = device->getDevice()->CreateVertexShader(pShaderBytecode.operator void *, BytecodeLength, nullptr, m_vertexShader.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);
	}

	void VertexShader::CreateInputLayout(_In_ DeviceDX11 ^ device)
	{
		HRESULT hr;

		hr = device->getDevice()->CreateInputLayout(wrapInputElementDesc(m_inputElementDesc), m_inputElementDesc->Length, m_vertexBlob.Get(), m_vertexBlob.Get()->GetBufferSize(), m_inputLayout.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);
	}
	void VertexShader::ReflectInputLayout(_In_ DeviceDX11^ device)
	{
		HRESULT hr;

		// Reflect shader info
		ComPtr<ID3D11ShaderReflection> pVertexShaderReflection;

		hr = D3DReflect(m_vertexBlob->GetBufferPointer(), m_vertexBlob->GetBufferSize(), IID_ID3D11ShaderReflection, &pVertexShaderReflection);
		ThrowIfFailed(hr);

		// Get shader info
		D3D11_SHADER_DESC shaderDesc;
		pVertexShaderReflection->GetDesc(&shaderDesc);

		// Read input layout description from shader info
		std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
		for (uint32 i = 0; i < shaderDesc.InputParameters; i++)
		{
			D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
			pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

			// fill out input element desc
			D3D11_INPUT_ELEMENT_DESC elementDesc;
			elementDesc.SemanticName = paramDesc.SemanticName;
			elementDesc.SemanticIndex = paramDesc.SemanticIndex;
			elementDesc.InputSlot = 0;
			elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			elementDesc.InstanceDataStepRate = 0;

			// determine DXGI format
			if (paramDesc.Mask == 1)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
			}
			else if (paramDesc.Mask <= 3)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
			}
			else if (paramDesc.Mask <= 7)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			}
			else if (paramDesc.Mask <= 15)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			}

			//save element desc
			inputLayoutDesc.push_back(elementDesc);
		}

		// Try to create Input Layout
		hr = device->getDevice()->CreateInputLayout(&inputLayoutDesc[0], (uint32)inputLayoutDesc.size(), m_vertexBlob->GetBufferPointer(), m_vertexBlob->GetBufferSize(), &m_inputLayout);
		ThrowIfFailed(hr);
	}

	//Getter
	ID3D11VertexShader* VertexShader::getShader()
	{
		return m_vertexShader.Get();
	}
	ID3D11InputLayout* VertexShader::getInputLayout()
	{
		return m_inputLayout.Get();
	}

	///////////////////////////////////////////////////////////////////
	/// Pixel Shader
	///////////////////////////////////////////////////////////////////
	PixelShader::PixelShader(_In_ String^ CSOFilename)
	{
		m_shaderByteCode = nullptr;
		m_BytecodeLength = 0U;
		m_csoFilename = CSOFilename;
		m_useBytecode = false;
	}
	PixelShader::PixelShader(_In_ void* ShaderBytecode, _In_ SizeT BytecodeLength)
	{
		m_shaderByteCode = ShaderBytecode;
		m_BytecodeLength = BytecodeLength;
		m_useBytecode = true;
	}

	void PixelShader::Load(_In_ DeviceDX11^ device)
	{
		if (m_useBytecode)
			LoadfromByteArray(device);
		else
			LoadfromFile(device);
	}

	void PixelShader::LoadfromFile(_In_ DeviceDX11^ device)
	{
		HRESULT hr;

		// Create path/filename string
		String^ path;
		String^ pathfilename;
		StorageFolder^ m_installedLocation = Package::Current->InstalledLocation;
		path = Platform::String::Concat(m_installedLocation->Path, "\\");
		pathfilename = Platform::String::Concat(path, m_csoFilename);

		hr = D3DReadFileToBlob(pathfilename->Data(), &m_pixelBlob);
		ThrowIfFailed(hr);

		hr = device->getDevice()->CreatePixelShader(m_pixelBlob->GetBufferPointer(), m_pixelBlob->GetBufferSize(), nullptr, &m_pixelShader);
		ThrowIfFailed(hr);
	}
	void PixelShader::LoadfromByteArray(_In_ DeviceDX11^ device)
	{
		HRESULT hr;

		hr = device->getDevice()->CreatePixelShader(m_shaderByteCode, m_BytecodeLength, nullptr, m_pixelShader.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);

		hr = D3DCreateBlob(m_BytecodeLength, m_pixelBlob.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);
	}

	//Getter
	ID3D11PixelShader* PixelShader::getShader()
	{
		return m_pixelShader.Get();
	}
}//namespace WOtech