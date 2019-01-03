////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Materials.h
///
///			Description:
///
///			Created:	20.08.2017
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_MATERIALS_H
#define WO_MATERIALS_H

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <3DComponents.h>
#include <DXWrapper.h>

namespace WOtech
{
	// Stores the vector and Color´s for a Directional light
	struct DirectionalLight
	{
		DirectionalLight();

		DirectX::XMVECTOR Direction;
		DirectX::XMVECTOR DiffuseColor;
		DirectX::XMVECTOR SpecularColor;
	};

	// Strores the Matrices for Materials
	struct MaterialMatrices
	{
		MaterialMatrices();

		DirectX::XMMATRIX World;
		DirectX::XMMATRIX WorldInverse;
		DirectX::XMMATRIX View;
		DirectX::XMMATRIX Projection;
		DirectX::XMMATRIX worldView;

		void XM_CALLCONV setConstants(_In_ DirectX::XMMATRIX& worldViewProjectionConstant, _In_ DirectX::XMMATRIX& worldConstant, _In_ DirectX::XMMATRIX& worldInverseConstant);
	};

	// Stores the Materials Color
	struct MaterialColor
	{
		MaterialColor();

		DirectX::XMVECTOR DiffuseColor;
		float Alpha;

		void XM_CALLCONV setConstants(_In_ DirectX::XMVECTOR& diffuseColorConstant);
	};

	// Stores the Ambient and Directional Lights for Material
	struct MaterialLights : public MaterialColor
	{
		MaterialLights();

		static const int MaxDirectionalLights = 3;

		// Fields.
		DirectX::XMVECTOR EmissiveColor;
		DirectX::XMVECTOR AmbientLightColor;

		bool LightEnabled[MaxDirectionalLights];
		DirectionalLight DirectionalLights[MaxDirectionalLights];

		void XM_CALLCONV setConstants(_In_ MaterialMatrices const& matrices, _In_ DirectX::XMVECTOR& emissiveColor, _In_ DirectX::XMMATRIX& worldConstant, _In_ DirectX::XMVECTOR worldInverseTransposeConstant[3], _In_ DirectX::XMVECTOR& eyePositionConstant, _In_ DirectX::XMVECTOR& diffuseColorConstant, _In_ DirectX::XMVECTOR& emissiveColorConstant, _In_ bool lightingEnabled);
	};

	// Constant buffer layout. Must match the shader!
	struct MaterialConstants
	{
		DirectX::XMVECTOR diffuseColor;
		DirectX::XMVECTOR emissiveColor;
		DirectX::XMVECTOR specularColorAndPower;

		DirectX::XMVECTOR lightDirection[MaterialLights::MaxDirectionalLights];
		DirectX::XMVECTOR lightDiffuseColor[MaterialLights::MaxDirectionalLights];
		DirectX::XMVECTOR lightSpecularColor[MaterialLights::MaxDirectionalLights];

		DirectX::XMVECTOR eyePosition;

		DirectX::XMVECTOR fogColor;
		DirectX::XMVECTOR fogVector;

		DirectX::XMMATRIX world;
		DirectX::XMMATRIX worldInverse;
		DirectX::XMVECTOR worldInverseTranspose[3];
		DirectX::XMMATRIX worldViewProj;
	};

	// Interface for Materials with World,View and Projection Matrices
	public interface class IMaterialMatrices
	{
	public:
		virtual void setWorld(_In_ Windows::Foundation::Numerics::float4x4 world) = 0;
		virtual void setWorldInverse(_In_ Windows::Foundation::Numerics::float4x4 worldInverse) = 0;
		virtual void setView(_In_ Windows::Foundation::Numerics::float4x4 view) = 0;
		virtual void setProjection(_In_ Windows::Foundation::Numerics::float4x4 projection) = 0;
		virtual void setMatrices(_In_ Windows::Foundation::Numerics::float4x4 world, _In_ Windows::Foundation::Numerics::float4x4 worldInverse, _In_ Windows::Foundation::Numerics::float4x4 view, _In_ Windows::Foundation::Numerics::float4x4 projection) = 0;
	};

	// Interface for Materials with Directional Lightning
	public interface class IMaterialLights
	{
	public:
		virtual void SetLightingEnabled(_In_ bool value) = 0;
		virtual void SetPerPixelLighting(_In_ bool value) = 0;
		virtual void SetAmbientLightColor(_In_ Windows::Foundation::Numerics::float4 value) = 0;

		virtual void SetLightEnabled(_In_ int whichLight, _In_ bool value) = 0;
		virtual void SetLightDirection(_In_ int whichLight, _In_ Windows::Foundation::Numerics::float4 value) = 0;
		virtual void SetLightDiffuseColor(_In_ int whichLight, _In_ Windows::Foundation::Numerics::float4 value) = 0;
		virtual void SetLightSpecularColor(_In_ int whichLight, _In_ Windows::Foundation::Numerics::float4 value) = 0;

		virtual void EnableDefaultLighting() = 0;
	};

	public ref class BasicMaterial sealed : public IMaterial, IMaterialMatrices
	{
	public:
		BasicMaterial(_In_ VertexShader^ Vshader, _In_ PixelShader^ Pshader, _In_ DeviceDX11^ device);

		virtual void bindMaterial(_In_ DeviceDX11^ device);
		virtual void unbindMaterial(_In_ DeviceDX11^ device);

		virtual void setWorld(_In_ Windows::Foundation::Numerics::float4x4 world);
		virtual void setWorldInverse(_In_ Windows::Foundation::Numerics::float4x4 worldInverse);
		virtual void setView(_In_ Windows::Foundation::Numerics::float4x4 view);
		virtual void setProjection(_In_ Windows::Foundation::Numerics::float4x4 projection);
		virtual void setMatrices(_In_ Windows::Foundation::Numerics::float4x4 world, _In_ Windows::Foundation::Numerics::float4x4 worldInverse, _In_ Windows::Foundation::Numerics::float4x4 view, _In_ Windows::Foundation::Numerics::float4x4 projection);

	private:
		void setConstants(_In_ DeviceDX11^ device);

	private:
		WOtech::VertexShader^					m_vertexShader;
		WOtech::PixelShader^					m_pixelShader;

		MaterialMatrices						m_matrices;

		MaterialConstants						m_constants;

		// Uniform buffer
		Microsoft::WRL::ComPtr<ID3D11Buffer>	m_constantBuffer;
	};
}
#endif