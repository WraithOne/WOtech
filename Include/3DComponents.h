////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: 3DComponents.h
///
///			Description:
///
///			Created:	22.02.2016
///			Edited:		25.09.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_3DCOMPONENTS_H
#define WO_3DCOMPONENTS_H

//////////////
// INCLUDES //
//////////////
#include "Numerics.h"
#include "VertexTypes.h"

namespace WOtech
{
	// Forward Decl.
	ref class DeviceDX11;

	public enum class FORMAT_DXGI
	{
		FORMAT_UNKNOWN,
		FORMAT_R32G32B32A32_TYPELESS,
		FORMAT_R32G32B32A32_FLOAT,
		FORMAT_R32G32B32A32_UINT,
		FORMAT_R32G32B32A32_SINT,
		FORMAT_R32G32B32_TYPELESS,
		FORMAT_R32G32B32_FLOAT,
		FORMAT_R32G32B32_UINT,
		FORMAT_R32G32B32_SINT,
		FORMAT_R16G16B16A16_TYPELESS,
		FORMAT_R16G16B16A16_FLOAT,
		FORMAT_R16G16B16A16_UNORM,
		FORMAT_R16G16B16A16_UINT,
		FORMAT_R16G16B16A16_SNORM,
		FORMAT_R16G16B16A16_SINT,
		FORMAT_R32G32_TYPELESS,
		FORMAT_R32G32_FLOAT,
		FORMAT_R32G32_UINT,
		FORMAT_R32G32_SINT,
		FORMAT_R32G8X24_TYPELESS,
		FORMAT_D32_FLOAT_S8X24_UINT,
		FORMAT_R32_FLOAT_X8X24_TYPELESS,
		FORMAT_X32_TYPELESS_G8X24_UINT,
		FORMAT_R10G10B10A2_TYPELESS,
		FORMAT_R10G10B10A2_UNORM,
		FORMAT_R10G10B10A2_UINT,
		FORMAT_R11G11B10_FLOAT,
		FORMAT_R8G8B8A8_TYPELESS,
		FORMAT_R8G8B8A8_UNORM,
		FORMAT_R8G8B8A8_UNORM_SRGB,
		FORMAT_R8G8B8A8_UINT,
		FORMAT_R8G8B8A8_SNORM,
		FORMAT_R8G8B8A8_SINT,
		FORMAT_R16G16_TYPELESS,
		FORMAT_R16G16_FLOAT,
		FORMAT_R16G16_UNORM,
		FORMAT_R16G16_UINT,
		FORMAT_R16G16_SNORM,
		FORMAT_R16G16_SINT,
		FORMAT_R32_TYPELESS,
		FORMAT_D32_FLOAT,
		FORMAT_R32_FLOAT,
		FORMAT_R32_UINT,
		FORMAT_R32_SINT,
		FORMAT_R24G8_TYPELESS,
		FORMAT_D24_UNORM_S8_UINT,
		FORMAT_R24_UNORM_X8_TYPELESS,
		FORMAT_X24_TYPELESS_G8_UINT,
		FORMAT_R8G8_TYPELESS,
		FORMAT_R8G8_UNORM,
		FORMAT_R8G8_UINT,
		FORMAT_R8G8_SNORM,
		FORMAT_R8G8_SINT,
		FORMAT_R16_TYPELESS,
		FORMAT_R16_FLOAT,
		FORMAT_D16_UNORM,
		FORMAT_R16_UNORM,
		FORMAT_R16_UINT,
		FORMAT_R16_SNORM,
		FORMAT_R16_SINT,
		FORMAT_R8_TYPELESS,
		FORMAT_R8_UNORM,
		FORMAT_R8_UINT,
		FORMAT_R8_SNORM,
		FORMAT_R8_SINT,
		FORMAT_A8_UNORM,
		FORMAT_R1_UNORM,
		FORMAT_R9G9B9E5_SHAREDEXP,
		FORMAT_R8G8_B8G8_UNORM,
		FORMAT_G8R8_G8B8_UNORM,
		FORMAT_BC1_TYPELESS,
		FORMAT_BC1_UNORM,
		FORMAT_BC1_UNORM_SRGB,
		FORMAT_BC2_TYPELESS,
		FORMAT_BC2_UNORM,
		FORMAT_BC2_UNORM_SRGB,
		FORMAT_BC3_TYPELESS,
		FORMAT_BC3_UNORM,
		FORMAT_BC3_UNORM_SRGB,
		FORMAT_BC4_TYPELESS,
		FORMAT_BC4_UNORM,
		FORMAT_BC4_SNORM,
		FORMAT_BC5_TYPELESS,
		FORMAT_BC5_UNORM,
		FORMAT_BC5_SNORM,
		FORMAT_B5G6R5_UNORM,
		FORMAT_B5G5R5A1_UNORM,
		FORMAT_B8G8R8A8_UNORM,
		FORMAT_B8G8R8X8_UNORM,
		FORMAT_R10G10B10_XR_BIAS_A2_UNORM,
		FORMAT_B8G8R8A8_TYPELESS,
		FORMAT_B8G8R8A8_UNORM_SRGB,
		FORMAT_B8G8R8X8_TYPELESS,
		FORMAT_B8G8R8X8_UNORM_SRGB,
		FORMAT_BC6H_TYPELESS,
		FORMAT_BC6H_UF16,
		FORMAT_BC6H_SF16,
		FORMAT_BC7_TYPELESS,
		FORMAT_BC7_UNORM,
		FORMAT_BC7_UNORM_SRGB,
		FORMAT_AYUV,
		FORMAT_Y410,
		FORMAT_Y416,
		FORMAT_NV12,
		FORMAT_P010,
		FORMAT_P016,
		FORMAT_420_OPAQUE,
		FORMAT_YUY2,
		FORMAT_Y210,
		FORMAT_Y216,
		FORMAT_NV11,
		FORMAT_AI44,
		FORMAT_IA44,
		FORMAT_P8,
		FORMAT_A8P8,
		FORMAT_B4G4R4A4_UNORM,
		FORMAT_P208,
		FORMAT_V208,
		FORMAT_V408,
		FORMAT_FORCE_UINT
	};

	public value struct LUID_DXGI
	{
		UINT64	LowPart;
		INT64	HighPart;
	};

	public value struct ADAPTER_DXGI
	{
		Platform::String^	Description;
		UINT				VendorId;
		UINT				DeviceId;
		UINT				SubSysId;
		UINT				Revision;
		Platform::SizeT		DedicatedVideoMemory;
		Platform::SizeT		DedicatedSystemMemory;
		Platform::SizeT		SharedSystemMemory;
		LUID_DXGI			AdapterLUID;
	};

	public enum class MODE_ROTATION_DXGI
	{
		DXGI_MODE_ROTATION_UNSPECIFIED = 0,
		DXGI_MODE_ROTATION_IDENTITY = 1,
		DXGI_MODE_ROTATION_ROTATE90 = 2,
		DXGI_MODE_ROTATION_ROTATE180 = 3,
		DXGI_MODE_ROTATION_ROTATE270 = 4
	};

	public value struct DXGI_OUTPUT_DESC
	{
		Platform::String^	DeviceName;
		Windows::Foundation::Rect		DesktopCoordinates;
		Platform::Boolean	AttachedToDesktop;
		MODE_ROTATION_DXGI	Rotation;
		// TODO: HMONITOR   Monitor;
	};

	public value struct RATIONAL_DXGI
	{
		UINT Numerator;
		UINT Denominator;
	};

	public enum class MODE_SCANLINE_ORDER_DXGI
	{
		DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED = 0,
		DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE = 1,
		DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST = 2,
		DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST = 3
	};

	public enum class MODE_SCALING_DXGI
	{
		DXGI_MODE_SCALING_UNSPECIFIED = 0,
		DXGI_MODE_SCALING_CENTERED = 1,
		DXGI_MODE_SCALING_STRETCHED = 2
	};

	public value struct MODE_DESC_DXGI
	{
		UINT                     Width;
		UINT                     Height;
		RATIONAL_DXGI            RefreshRate;
		FORMAT_DXGI              Format;
		MODE_SCANLINE_ORDER_DXGI ScanlineOrdering;
		MODE_SCALING_DXGI        Scaling;
	};

	public enum class CLEAR_FLAG
	{
		CLEAR_DEPTH = 0x1L,
		CLEAR_STENCIL = 0x2L
	};

	public enum class INPUT_CLASSIFICATION
	{
		D3D11_INPUT_PER_VERTEX_DATA = 0,
		D3D11_INPUT_PER_INSTANCE_DATA = 1
	};

	public value struct INPUT_ELEMENT_DESC
	{
		Platform::String^		SemanticName;
		UINT					SemanticIndex;
		FORMAT_DXGI				Format;
		UINT					InputSlot;
		UINT					AlignedByteOffset;
		INPUT_CLASSIFICATION	InputSlotClass;
		UINT					InstanceDataStepRate;
	};

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

		Windows::Foundation::Numerics::float3 Eye();
		Windows::Foundation::Numerics::float3 LookAt();
		Windows::Foundation::Numerics::float3 Up();

	internal:
		DirectX::XMFLOAT4X4 ViewMatrix();
		DirectX::XMFLOAT4X4 ProjectionMatrix();
		DirectX::XMFLOAT4X4 InverseMatrix();

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
		VertexShader(_In_ Platform::String^ compiledVertexShaderObject, _In_ WOtech::DeviceDX11^ device);
		VertexShader(_In_ Platform::String^ compiledVertexShaderObject, _In_ const Platform::Array<WOtech::INPUT_ELEMENT_DESC>^ inputElementDesc, _In_ WOtech::DeviceDX11^ device);
		VertexShader(_In_ Platform::String^ filename, _In_ Platform::String^ entryPoint, _In_ int unUsed, _In_ WOtech::DeviceDX11^ device);
		VertexShader(_In_ Platform::String^ filename, _In_ Platform::String^ entryPoint, _In_ const Platform::Array<WOtech::INPUT_ELEMENT_DESC>^ inputElementDesc, _In_ int unUsed, _In_ WOtech::DeviceDX11^ device);
		VertexShader(_In_ Platform::IntPtr pShaderBytecode, _In_ Platform::SizeT BytecodeLength, _In_opt_ const Platform::Array<WOtech::INPUT_ELEMENT_DESC>^ inputElementDesc, _In_ int unUsed, _In_ int unUsed2, _In_ WOtech::DeviceDX11^ device);

		void Load(_In_ WOtech::DeviceDX11^ device);

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
		const void*														m_shaderByteCode;
		SIZE_T															m_byteCodeLength;

		Platform::Boolean												m_useInputElementDesc;
		const Platform::Array<WOtech::INPUT_ELEMENT_DESC>^				m_inputElementDesc;

		Microsoft::WRL::ComPtr<ID3D11VertexShader>						m_vertexShader;
		Microsoft::WRL::ComPtr<ID3DBlob>								m_vertexBlob;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>						m_inputLayout;
	};//class VertexShader

	public ref class PixelShader sealed
	{
	public:
		PixelShader(_In_ Platform::String^ CSOFilename, _In_ WOtech::DeviceDX11^ device);
		PixelShader(_In_ Platform::IntPtr ShaderBytecode, _In_ Platform::SizeT BytecodeLength, _In_ WOtech::DeviceDX11^ device);

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
		D3D11_SHADER_RESOURCE_VIEW_DESC getDescription();

	private:
		Platform::String^ m_filenName;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_texture;
		D3D11_SHADER_RESOURCE_VIEW_DESC						m_texDESC;
	}; // class Texture

	public ref class VertexBuffer sealed
	{
	public:
		VertexBuffer(_In_ Platform::IntPtr data, _In_  UINT32 size, _In_  UINT32 stride, _In_ UINT32 offset, _In_  DeviceDX11^ device);

		void SubmitBuffer(_In_ DeviceDX11^ device);

		void setOffset(_In_ UINT32 offset);
		void setStride(_In_ UINT32 stride);

		UINT32 getStride();
		UINT32 getOffset();

	private:
		void CreateBuffer(_In_ Platform::IntPtr data, _In_  UINT32 size, _In_  DeviceDX11^ device);

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
		virtual void bindMaterial(_In_ DeviceDX11^ device) = 0;
		virtual void unbindMaterial(_In_ DeviceDX11^ device) = 0;
	};

	public ref class Mesh sealed
	{
	public:
		Mesh(_In_ VertexBuffer^ vertexBuffer, _In_ IndexBuffer^ indexBuffer, _In_ IMaterial^ material);

		void setGeometry(_In_ VertexBuffer^ vertex, _In_ IndexBuffer^ index) { m_vertexBuffer = vertex, m_indexBuffer = index; }
		void setMaterial(_In_ IMaterial^ material) { m_material = material; }
		void setPosition(_In_  Windows::Foundation::Numerics::float3 position) { m_position = position; }
		void setScaling(_In_ Windows::Foundation::Numerics::float3 scaling) { m_scaling = scaling; }
		void setRotation(_In_ Windows::Foundation::Numerics::float3 rotation) { m_rotation = rotation; }

		Windows::Foundation::Numerics::float3 getPosition() { return m_position; }
		Windows::Foundation::Numerics::float3 getScaling() { return m_scaling; }
		Windows::Foundation::Numerics::float3 getRotation() { return m_rotation; }

		void bindMaterial(_In_ DeviceDX11^ device);
		void Render(_In_ DeviceDX11^ device);

		IMaterial^ GetMaterial() { return m_material; }

	private:
		VertexBuffer^		m_vertexBuffer;
		IndexBuffer^		m_indexBuffer;
		IMaterial^			m_material;
		Windows::Foundation::Numerics::float3		m_position;
		Windows::Foundation::Numerics::float3		m_scaling;
		Windows::Foundation::Numerics::float3		m_rotation;
	};
}// WOtech
#endif