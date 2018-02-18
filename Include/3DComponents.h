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
///			Edited:		22.10.2017
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_3DCOMPONENTS_H
#define WO_3DCOMPONENTS_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Numerics.h"
#include "VertexTypes.h"

namespace WOtech
{
	// Forward Decl.
	ref class DeviceDX11;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Resource data formats, including fully-typed and typeless formats. A list of modifiers at the bottom of the page more fully describes each format type.  </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public enum class FORMAT_DXGI {
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

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Describes a local identifier for an adapter. </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public value struct LUID_DXGI
	{
		/// <summary>	Specifies a DWORD that contains the unsigned lower numbers of the id.< / summary>
		UINT64	LowPart;
		/// <summary>	Specifies a LONG that contains the signed high numbers of the id.< / summary>
		INT64	HighPart;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Describes an adapter (or video card) by using DXGI. </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public value struct ADAPTER_DXGI
	{
		/// <summary>	A string that contains the adapter description. On feature level 9 graphics hardware, GetDesc returns “Software Adapter” for the description string.< / summary>
		Platform::String^	Description;
		/// <summary>	The PCI ID of the hardware vendor. On feature level 9 graphics hardware, GetDesc returns zeros for the PCI ID of the hardware vendor.< / summary>
		UINT				VendorId;
		/// <summary>	The PCI ID of the hardware device. On feature level 9 graphics hardware, GetDesc returns zeros for the PCI ID of the hardware device.< / summary>
		UINT				DeviceId;
		/// <summary>	The PCI ID of the sub system. On feature level 9 graphics hardware, GetDesc returns zeros for the PCI ID of the sub system.< / summary>
		UINT				SubSysId;
		/// <summary>	The PCI ID of the revision number of the adapter. On feature level 9 graphics hardware, GetDesc returns zeros for the PCI ID of the revision number of the adapter.< / summary>
		UINT				Revision;
		/// <summary>	The number of bytes of dedicated video memory that are not shared with the CPU.< / summary>
		Platform::SizeT		DedicatedVideoMemory;
		/// <summary>	The number of bytes of dedicated system memory that are not shared with the CPU. This memory is allocated from available system memory at boot time.< / summary>
		Platform::SizeT		DedicatedSystemMemory;
		/// <summary>	The number of bytes of shared system memory. This is the maximum value of system memory that may be consumed by the adapter during operation. Any incidental memory consumed by the driver as it manages and uses video memory is additional.< / summary>
		Platform::SizeT		SharedSystemMemory;
		/// <summary>	A unique value that identifies the adapter. See LUID for a definition of the structure.< / summary>
		LUID_DXGI			AdapterLUID;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Flags that indicate how the back buffers should be rotated to fit the physical rotation of a monitor. </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public enum class MODE_ROTATION_DXGI
	{
		/// <summary>	Unspecified rotation.< / summary>
		DXGI_MODE_ROTATION_UNSPECIFIED = 0,
		/// <summary>	Specifies no rotation.< / summary>
		DXGI_MODE_ROTATION_IDENTITY = 1,
		/// <summary>	Specifies 90 degrees of rotation.< / summary>
		DXGI_MODE_ROTATION_ROTATE90 = 2,
		/// <summary>	Specifies 180 degrees of rotation.< / summary>
		DXGI_MODE_ROTATION_ROTATE180 = 3,
		/// <summary>	Specifies 270 degrees of rotation.< / summary>
		DXGI_MODE_ROTATION_ROTATE270 = 4
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Describes an output or physical connection between the adapter (video card) and a device. </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public value struct DXGI_OUTPUT_DESC
	{
		/// <summary>	A string that contains the name of the output device.< / summary>
		Platform::String^	DeviceName;
		/// <summary>	A RECT structure containing the bounds of the output in desktop coordinates. Desktop coordinates depend on the dots per inch (DPI) of the desktop. For info about writing DPI-aware Win32 apps, see High DPI.< / summary>
		WOtech::RECT		DesktopCoordinates;
		/// <summary>	True if the output is attached to the desktop; otherwise, false.< / summary>
		Platform::Boolean	AttachedToDesktop;
		/// <summary>	A member of the DXGI_MODE_ROTATION enumerated type describing on how an image is rotated by the output.< / summary>
		MODE_ROTATION_DXGI	Rotation;
		// TODO: HMONITOR   Monitor;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Represents a rational number. </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public value struct RATIONAL_DXGI
	{
		/// <summary>	An unsigned integer value representing the top of the rational number.< / summary>
		UINT Numerator;
		/// <summary>	An unsigned integer value representing the bottom of the rational number.< / summary>
		UINT Denominator;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Flags indicating the method the raster uses to create an image on a surface. </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public enum class MODE_SCANLINE_ORDER_DXGI
	{
		/// <summary>	Scanline order is unspecified.< / summary>
		DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED = 0,
		/// <summary>	The image is created from the first scanline to the last without skipping any.< / summary>
		DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE = 1,
		/// <summary>	The image is created beginning with the upper field.< / summary>
		DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST = 2,
		/// <summary>	The image is created beginning with the lower field.< / summary>
		DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST = 3
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Flags indicating how an image is stretched to fit a given monitor's resolution. </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public enum class MODE_SCALING_DXGI
	{
		/// <summary>	Unspecified scaling.< / summary>
		DXGI_MODE_SCALING_UNSPECIFIED = 0,
		/// <summary>	Specifies no scaling. The image is centered on the display. This flag is typically used for a fixed-dot-pitch display (such as an LED display).< / summary>
		DXGI_MODE_SCALING_CENTERED = 1,
		/// <summary>	Specifies stretched scaling.< / summary>
		DXGI_MODE_SCALING_STRETCHED = 2
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Describes a display mode. </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public value struct MODE_DESC_DXGI
	{
		/// <summary>	A value that describes the resolution width. If you specify the width as zero when you call the IDXGIFactory::CreateSwapChain method to create a swap chain, the runtime obtains the width from the output window and assigns this width value to the swap-chain description. You can subsequently call the IDXGISwapChain::GetDesc method to retrieve the assigned width value.< / summary>
		UINT                     Width;
		/// <summary>	A value describing the resolution height. If you specify the height as zero when you call the IDXGIFactory::CreateSwapChain method to create a swap chain, the runtime obtains the height from the output window and assigns this height value to the swap-chain description. You can subsequently call the IDXGISwapChain::GetDesc method to retrieve the assigned height value.< / summary>
		UINT                     Height;
		/// <summary>	A DXGI_RATIONAL structure describing the refresh rate in hertz< / summary>
		RATIONAL_DXGI            RefreshRate;
		/// <summary>	A DXGI_FORMAT structure describing the display format.< / summary>
		FORMAT_DXGI              Format;
		/// <summary>	A member of the DXGI_MODE_SCANLINE_ORDER enumerated type describing the scanline drawing mode.< / summary>
		MODE_SCANLINE_ORDER_DXGI ScanlineOrdering;
		/// <summary>	A member of the DXGI_MODE_SCALING enumerated type describing the scaling mode.< / summary>
		MODE_SCALING_DXGI        Scaling;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Specifies the parts of the depth stencil to clear.  </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public enum class CLEAR_FLAG
	{
		/// <summary>	Clear the depth buffer, using fast clear if possible, then place the resource in a compressed state.< / summary>
		CLEAR_DEPTH = 0x1L,
		/// <summary>	Clear the stencil buffer, using fast clear if possible, then place the resource in a compressed state.< / summary>
		CLEAR_STENCIL = 0x2L
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Type of data contained in an input slot. </summary>
	///
	/// <remarks>	WraithOne, 17.04.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public enum class INPUT_CLASSIFICATION
	{
		/// <summary>	Input data is per-vertex data.< / summary>
		D3D11_INPUT_PER_VERTEX_DATA = 0,
		/// <summary>	Input data is per-instance data.< / summary>
		D3D11_INPUT_PER_INSTANCE_DATA = 1
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	A description of a single element for the input-assembler stage. </summary>
	///
	/// <remarks>	WraithOne, 08.10.2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public value struct INPUT_ELEMENT_DESC
	{
		/// <summary>	The HLSL semantic associated with this element in a shader input-signature.< / summary>
		Platform::String^				SemanticName;
		/// <summary>	The semantic index for the element. A semantic index modifies a semantic, with an integer index number. A semantic index is only needed in a case where there is more than one element with the same semantic. For example, a 4x4 matrix would have four components each with the semantic name < / summary>
		UINT							SemanticIndex;
		/// <summary>	The data type of the element data. See FORMAT_DXGI.< / summary>
		FORMAT_DXGI						Format;
		/// <summary>	An integer value that identifies the input-assembler (see input slot). Valid values are between 0 and 15.< / summary>
		UINT							InputSlot;
		/// <summary>	Optional. Offset (in bytes) between each element. Use D3D11_APPEND_ALIGNED_ELEMENT for convenience to define the current element directly after the previous one, including any packing if necessary.< / summary>
		UINT					AlignedByteOffset;
		/// <summary>	Identifies the input data class for a single input slot.< / summary>
		INPUT_CLASSIFICATION			InputSlotClass;
		/// <summary>	The number of instances to draw using the same per-instance data before advancing in the buffer by one element. This value must be 0 for an element that contains per-vertex data (the slot class is set to D3D11_INPUT_PER_VERTEX_DATA).< / summary>
		UINT							InstanceDataStepRate;
	};

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

	private:
		Platform::String^ m_filenName;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
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
		void bindMaterial(_In_ DeviceDX11^ device);
		void unbindMaterial(_In_ DeviceDX11^ device);
	};

	public ref class Mesh sealed
	{
	public:
		Mesh(_In_ VertexBuffer^ vertexBuffer, _In_ IndexBuffer^ indexBuffer, _In_ IMaterial^ material);

		void setGeometry(_In_ VertexBuffer^ vertex, _In_ IndexBuffer^ index) { m_vertexBuffer = vertex, m_indexBuffer = index; }
		void setMaterial(_In_ IMaterial^ material) { m_material = material; }
		void setPosition(_In_  WOtech::FLOAT3 position) { m_position = position; }
		void setScaling(_In_ WOtech::FLOAT3 scaling) { m_scaling = scaling; }
		void setRotation(_In_ WOtech::FLOAT3 rotation) { m_rotation = rotation; }

		WOtech::FLOAT3 getPosition() { return m_position; }
		WOtech::FLOAT3 getScaling() { return m_scaling; }
		WOtech::FLOAT3 getRotation() { return m_rotation; }

		void bindMaterial(_In_ DeviceDX11^ device);
		void Render(_In_ DeviceDX11^ device);

		IMaterial^ GetMaterial() { return m_material; }

	private:
		VertexBuffer^		m_vertexBuffer;
		IndexBuffer^		m_indexBuffer;
		IMaterial^			m_material;
		WOtech::FLOAT3		m_position;
		WOtech::FLOAT3		m_scaling;
		WOtech::FLOAT3		m_rotation;
	};
}// WOtech
#endif