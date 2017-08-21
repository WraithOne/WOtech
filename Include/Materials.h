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
///			Edited:		20.08.2017
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_MATERIALS_H
#define WO_MATERIALS_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "3DComponents.h"
#include "DXWrapper.h"

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
		DirectX::XMMATRIX View;
		DirectX::XMMATRIX Projection;
		DirectX::XMMATRIX worldView;

		void setConstants(DirectX::XMMATRIX& worldViewProjectionConstant);
	};

	// Stores the Materials Color
	struct MaterialColor
	{
		MaterialColor();

		DirectX::XMVECTOR DiffuseColor;
		float Alpha;

		void setConstants(DirectX::XMVECTOR& diffuseColorConstant);
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

		void setConstants(_In_ MaterialMatrices const& matrices, _In_ DirectX::XMVECTOR& emissiveColor, _In_ DirectX::XMMATRIX& worldConstant, _In_ DirectX::XMVECTOR worldInverseTransposeConstant[3], _In_ DirectX::XMVECTOR& eyePositionConstant, _In_ DirectX::XMVECTOR& diffuseColorConstant, _In_ DirectX::XMVECTOR& emissiveColorConstant, bool lightingEnabled);
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
		DirectX::XMVECTOR worldInverseTranspose[3];
		DirectX::XMMATRIX worldViewProj;
	};

	// Interface for Materials with World,View and Projection Matrices
	public interface class IMaterialMatrices
	{
	public:
		void setWorld(_In_ Windows::Foundation::Numerics::float4x4 world);
		void setView(_In_ Windows::Foundation::Numerics::float4x4 view);
		void setProjection(_In_ Windows::Foundation::Numerics::float4x4 projection);
		void setMatrices(_In_ Windows::Foundation::Numerics::float4x4 world, _In_ Windows::Foundation::Numerics::float4x4 view, _In_ Windows::Foundation::Numerics::float4x4 projection);
	};

	// Interface for Materials with Directional Lightning
	public interface class IMaterialLights
	{
	public:
		void SetLightingEnabled(_In_ bool value);
		void SetPerPixelLighting(_In_ bool value);
		void SetAmbientLightColor(_In_ Windows::Foundation::Numerics::float4 value);

		void SetLightEnabled(_In_ int whichLight, _In_ bool value);
		void SetLightDirection(_In_ int whichLight, _In_ Windows::Foundation::Numerics::float4 value);
		void SetLightDiffuseColor(_In_ int whichLight, _In_ Windows::Foundation::Numerics::float4 value);
		void SetLightSpecularColor(_In_ int whichLight, _In_ Windows::Foundation::Numerics::float4 value);

		void EnableDefaultLighting();	
	};

	public ref class BasicMaterial sealed : public IMaterial, IMaterialMatrices
	{
	public:
		BasicMaterial(_In_ VertexShader^ Vshader, _In_ PixelShader^ Pshader, _In_ DeviceDX11^ device);

		virtual void bindMaterial(_In_ DeviceDX11^ device);
		virtual void unbindMaterial(_In_ DeviceDX11^ device);

		virtual void setWorld(_In_ Windows::Foundation::Numerics::float4x4 world);
		virtual void setView(_In_ Windows::Foundation::Numerics::float4x4 view);
		virtual void setProjection(_In_ Windows::Foundation::Numerics::float4x4 projection);
		virtual void setMatrices(_In_ Windows::Foundation::Numerics::float4x4 world, _In_ Windows::Foundation::Numerics::float4x4 view, _In_ Windows::Foundation::Numerics::float4x4 projection);

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