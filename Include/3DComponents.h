////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: GraphicComponent.h
///
///			Description:
///
///			Created:	22.02.2016
///			Edited:		22.08.2017
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_3DCOMPONENTS_H
#define WO_3DCOMPONENTS_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "DXWrapper.h"
#include "VertexTypes.h"

namespace WOtech
{
	// Forward Decl.
	ref class DeviceDX11;

	public ref class Camera sealed
	{
	public:
		Camera();

		void SetViewParams(_In_ WOtech::FLOAT3 eye,
			_In_ WOtech::FLOAT3 lookAt,
			_In_ WOtech::FLOAT3 up);

		void SetProjParams(_In_ float32 fieldOfView, _In_ float32 aspectRatio, _In_ float32 nearPlane, _In_ float32 farPlane);

		void LookDirection(_In_ WOtech::FLOAT3 lookDirection);
		void Eye(_In_ WOtech::FLOAT3 position);

		float32	NearClipPlane();
		float32	FarClipPlane();
		float32	Pitch();
		float32	Yaw();

		WOtech::FLOAT3 Eye();
		WOtech::FLOAT3 LookAt();
		WOtech::FLOAT3 Up();

	internal:
		DirectX::XMFLOAT4X4 ViewMatrix();
		DirectX::XMFLOAT4X4 ProjectionMatrix();
		DirectX::XMFLOAT4X4 InverseMatrix();

	private:
		DirectX::XMFLOAT4X4 m_viewMatrix;
		DirectX::XMFLOAT4X4 m_projectionMatrix;

		DirectX::XMFLOAT4X4 m_inverseView;

		WOtech::FLOAT3 m_eye;
		WOtech::FLOAT3 m_lookAt;
		WOtech::FLOAT3 m_up;
		float32 m_cameraYawAngle;
		float32 m_cameraPitchAngle;

		float32	m_fieldOfView;
		float32	m_aspectRatio;
		float32	m_nearPlane;
		float32	m_farPlane;
	};//class Camera

	public ref class VertexShader sealed
	{
	public:
		VertexShader(_In_ Platform::String^ compiledVertexShaderObject, _In_ WOtech::DeviceDX11^ device);
		VertexShader(_In_ Platform::String^ compiledVertexShaderObject, _In_ const Platform::Array<WOtech::DXWrapper::INPUT_ELEMENT_DESC>^ inputElementDesc, _In_ WOtech::DeviceDX11^ device);
		VertexShader(_In_ Platform::String^ filename, _In_ Platform::String^ entryPoint, _In_ int unUsed, _In_ WOtech::DeviceDX11^ device);
		VertexShader(_In_ Platform::String^ filename, _In_ Platform::String^ entryPoint, _In_ const Platform::Array<WOtech::DXWrapper::INPUT_ELEMENT_DESC>^ inputElementDesc, _In_ int unUsed, _In_ WOtech::DeviceDX11^ device);

		void Load(_In_ WOtech::DeviceDX11^ device);

	internal:
		VertexShader(_In_ void const* pShaderBytecode, _In_ Platform::SizeT BytecodeLength, _In_opt_ const Platform::Array<WOtech::DXWrapper::INPUT_ELEMENT_DESC>^ inputElementDesc, _In_ int unUsed, _In_ int unUsed2, _In_ WOtech::DeviceDX11^ device);

	internal:
		//Getter
		ID3D11VertexShader*	getShader();
		ID3D11InputLayout* getInputLayout();

	private:
		void ComilefromFile(_In_ WOtech::DeviceDX11^ device, _In_ Platform::String^ filename, _In_ Platform::String^ entryPoint);
		void LoadfromFile(_In_ WOtech::DeviceDX11^ device, _In_ Platform::String^ compiledVertexShaderObject);
		void LoadfromByteArray(_In_ WOtech::DeviceDX11^ device, _In_ void const* pShaderBytecode, _In_ Platform::SizeT BytecodeLength);

		void CreateInputLayout(_In_ WOtech::DeviceDX11^ device);
		void ReflectInputLayout(_In_ WOtech::DeviceDX11^ device);

	private:
		Platform::Boolean												m_loadfromFile;
		Platform::String^												m_fileName;
		Platform::String^												m_entryPoint;

		Platform::Boolean												m_useCVSO;
		Platform::String^												m_CVSO;

		Platform::Boolean												m_useShaderByteCode;
		const void*															m_shaderByteCode;
		SIZE_T															m_byteCodeLength;

		Platform::Boolean												m_useInputElementDesc;
		const Platform::Array<WOtech::DXWrapper::INPUT_ELEMENT_DESC>^	m_inputElementDesc;

		Microsoft::WRL::ComPtr<ID3D11VertexShader>						m_vertexShader;
		Microsoft::WRL::ComPtr<ID3DBlob>								m_vertexBlob;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>						m_inputLayout;
	};//class VertexShader

	public ref class PixelShader sealed
	{
	internal:
		PixelShader(_In_ void const* ShaderBytecode, _In_ Platform::SizeT BytecodeLength, _In_ WOtech::DeviceDX11^ device);

	public:
		PixelShader(_In_ Platform::String^ CSOFilename, _In_ WOtech::DeviceDX11^ device);

		void Load(_In_ WOtech::DeviceDX11^ device);

	private:
		void LoadfromFile(_In_ WOtech::DeviceDX11^ device);
		void LoadfromByteArray(_In_ WOtech::DeviceDX11^ device);

	internal:
		//Getter
		ID3D11PixelShader* getShader();

	private:
		Platform::Boolean							m_useBytecode;

		Platform::String^							m_csoFilename;

		const void*									m_shaderByteCode;
		SIZE_T										m_BytecodeLength;

		Microsoft::WRL::ComPtr<ID3DBlob>			m_pixelBlob;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pixelShader;
	};//class Pixelshader

	public ref class Texture sealed
	{
	public:
		Texture(_In_ Platform::String^ filename);

		Platform::Boolean Load(_In_ DeviceDX11^ device);
		void SubmitTexture(_In_ DeviceDX11^ device, _In_ uint32 slot);

		// Getter
		Platform::String^ getFilename();

	internal:
		ID3D11ShaderResourceView* getTexture();

	private:
		Platform::String^ m_filenName;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	}; // class Texture

	public ref class VertexBuffer sealed
	{
	public:
		void SubmitBuffer(_In_ DeviceDX11^ device);

		void setOffset(_In_ UINT32 offset);
		void setStride(_In_ UINT32 stride);

		UINT32 getStride();
		UINT32 getOffset();

	internal:
		VertexBuffer(_In_ void* data, _In_  UINT32 size, _In_  UINT32 stride, _In_ UINT32 offset, _In_  DeviceDX11^ device);

	private:
		void CreateBuffer(_In_ void* data, _In_  UINT32 size, _In_  DeviceDX11^ device);

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
		UINT32 m_stride;
		UINT32 m_offset;
	};

	public ref class IndexBuffer sealed
	{
	public:
		void SubmitBuffer(_In_ DeviceDX11^ device);
		inline uint32 getCount() { return m_count; }

	private:
		void CreateBuffer(_In_ void* data, _In_  UINT32 count, _In_  DeviceDX11^ device);

	internal:
		IndexBuffer(_In_ void* data, _In_  UINT32 count, _In_  DeviceDX11^ device);

	private:
		UINT32 m_count;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
	};

	public interface class IMaterial
	{
	public:
		void bindMaterial(_In_ DeviceDX11^ device);
		void unbindMaterial(_In_ DeviceDX11^ device);
	};

	public ref class Mesh sealed
	{
	public:
		Mesh(_In_ VertexBuffer^ vertexBuffer, _In_ IndexBuffer^ indexBuffer, _In_ IMaterial^ material);

		void SetGeometry(_In_ VertexBuffer^ vertex, _In_ IndexBuffer^ index) { m_vertexBuffer = vertex, m_indexBuffer = index; }
		void SetMaterial(_In_ IMaterial^ material) { m_material = material; }

		void bindMaterial(_In_ DeviceDX11^ device);
		void Render(_In_ DeviceDX11^ device);

		IMaterial^ GetMaterial() { return m_material; }

	private:
		VertexBuffer^		m_vertexBuffer;
		IndexBuffer^		m_indexBuffer;
		IMaterial^			m_material;
	};
}// WOtech
#endif