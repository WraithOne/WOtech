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
///			Edited:		13.11.2016
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_3DCOMPONENTS_H
#define WO_3DCOMPONENTS_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "DXWrapper.h"

namespace WOtech
{
	// Forward Decl.
	ref class DeviceDX11;

	public ref class Camera sealed
	{
	public:
		Camera();

		void SetViewParams(_In_ Windows::Foundation::Numerics::float3 eye,
			_In_ Windows::Foundation::Numerics::float3 lookAt,
			_In_ Windows::Foundation::Numerics::float3 up);

		void SetProjParams(_In_ float32 fieldOfView, _In_ float32 aspectRatio, _In_ float32 nearPlane, _In_ float32 farPlane);

		void LookDirection(_In_ Windows::Foundation::Numerics::float3 lookDirection);
		void Eye(_In_ Windows::Foundation::Numerics::float3 position);

		float32	NearClipPlane();
		float32	FarClipPlane();
		float32	Pitch();
		float32	Yaw();

		Windows::Foundation::Numerics::float4x4 View();
		Windows::Foundation::Numerics::float4x4 Projection();
		Windows::Foundation::Numerics::float4x4 World();

		Windows::Foundation::Numerics::float3 Eye();
		Windows::Foundation::Numerics::float3 LookAt();
		Windows::Foundation::Numerics::float3 Up();

	private:
		DirectX::XMFLOAT4X4 m_viewMatrix;
		DirectX::XMFLOAT4X4 m_projectionMatrix;

		DirectX::XMFLOAT4X4 m_inverseView;

		Windows::Foundation::Numerics::float3 m_eye;
		Windows::Foundation::Numerics::float3 m_lookAt;
		Windows::Foundation::Numerics::float3 m_up;
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
		[Windows::Foundation::Metadata::DefaultOverloadAttribute]
		VertexShader(_In_ Platform::String^ compiledVertexShaderObject);
		VertexShader(_In_ Platform::String^ compiledVertexShaderObject, _In_ const Platform::Array<WOtech::DXWrapper::INPUT_ELEMENT_DESC>^ inputElementDesc);
		VertexShader(_In_ Platform::String^ filename, _In_ Platform::String^ entryPoint);
		VertexShader(_In_ Platform::String^ filename, _In_ Platform::String^ entryPoint, _In_ const Platform::Array<WOtech::DXWrapper::INPUT_ELEMENT_DESC>^ inputElementDesc);

		void Load(_In_ WOtech::DeviceDX11^ device);

	internal:
		VertexShader(_In_ void* pShaderBytecode, _In_ Platform::SizeT BytecodeLength, _In_ const Platform::Array<WOtech::DXWrapper::INPUT_ELEMENT_DESC>^ inputElementDesc);

		//Getter
		ID3D11VertexShader*	getShader();
		ID3D11InputLayout* getInputLayout();

	private:
		void ComilefromFile(_In_ WOtech::DeviceDX11^ device, _In_ Platform::String^ filename, _In_ Platform::String^ entryPoint);
		void LoadfromFile(_In_ WOtech::DeviceDX11^ device, _In_ Platform::String^ compiledVertexShaderObject);
		void LoadfromByteArray(_In_ WOtech::DeviceDX11^ device, _In_ Platform::IntPtr pShaderBytecode, _In_ Platform::SizeT BytecodeLength);

		void CreateInputLayout(_In_ WOtech::DeviceDX11^ device);
		void ReflectInputLayout(_In_ WOtech::DeviceDX11^ device);

	private:
		Platform::Boolean								m_loadfromFile;
		Platform::String^								m_fileName;
		Platform::String^								m_entryPoint;

		Platform::Boolean								m_useCVSO;
		Platform::String^								m_CVSO;

		Platform::Boolean								m_useShaderByteCode;
		Platform::IntPtr								m_shaderByteCode;
		SIZE_T											m_byteCodeLength;

		Platform::Boolean								m_useInputElementDesc;
		const Platform::Array<WOtech::DXWrapper::INPUT_ELEMENT_DESC>^	m_inputElementDesc;

		Microsoft::WRL::ComPtr<ID3D11VertexShader>		m_vertexShader;
		Microsoft::WRL::ComPtr<ID3DBlob>				m_vertexBlob;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>		m_inputLayout;
	};//class VertexShader

	public ref class PixelShader sealed
	{
	public:
		PixelShader(_In_ Platform::String^ CSOFilename);

		void Load(_In_ WOtech::DeviceDX11^ device);

	private:
		void LoadfromFile(_In_ WOtech::DeviceDX11^ device);
		void LoadfromByteArray(_In_ WOtech::DeviceDX11^ device);

	internal:
		PixelShader(_In_ void* ShaderBytecode, _In_ Platform::SizeT BytecodeLength);
		//Getter
		ID3D11PixelShader* getShader();

	private:
		Platform::Boolean m_useBytecode;

		Platform::String^ m_csoFilename;

		const void* m_shaderByteCode;
		SIZE_T m_BytecodeLength;

		Microsoft::WRL::ComPtr<ID3DBlob> m_pixelBlob;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
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

	public ref class Material sealed
	{
	public:
		Material(WOtech::VertexShader^ Vshader, WOtech::PixelShader^ Pshader, DeviceDX11^ device);
		void bindMaterial(DeviceDX11^ device);
		void unbindMaterial(DeviceDX11^ device);

		void addTexture(Texture^ texture, uint32 slot);

	private:
		VertexShader^ m_vertexShader;
		PixelShader^ m_pixelShader;

		uint32 m_numMatrials;
		std::vector<Texture^> m_textures;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> m_samplerState;
	};

	public ref class MaterialInstance sealed
	{
	public:
		MaterialInstance(Material^ material);

		void bindMaterialInstance(DeviceDX11^ device);
		void UnbindMaterialInstance(DeviceDX11^ device);

	private:
		Material^ m_material;
	};

	public ref class Mesh sealed
	{
	public:
		Mesh(VertexBuffer^ vertexBuffer, IndexBuffer^ indexBuffer, MaterialInstance^ materialInstance);

		inline void SetGeometry(VertexBuffer^ vertex, IndexBuffer^ index) { m_vertexBuffer = vertex, m_IndexBuffer = index; }
		inline void SetMaterial(MaterialInstance^ materialInstance) { m_MaterialInstance = materialInstance; }

		void Render(DeviceDX11^ device);

		inline MaterialInstance^ GetMaterialInstance() { return m_MaterialInstance; }

	private:
		VertexBuffer^		m_vertexBuffer;
		IndexBuffer^		m_IndexBuffer;
		MaterialInstance^	m_MaterialInstance;
	};

	public value struct RendererUniforms
	{
		Windows::Foundation::Numerics::float4x4 ViewMatrix;
		Windows::Foundation::Numerics::float4x4 ProjectionMatrix;
		Windows::Foundation::Numerics::float4x4 WorldMatrix;
		Windows::Foundation::Numerics::float4x4 ModelMatrix;
	};
}// WOtech
#endif