////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Parameters.hlsli
///
///			Description:
///
///			Created:	15.04.2017
///			Edited:		02.09.2017
///
////////////////////////////////////////////////////////////////////////////

Texture2D<float4> Texture : register(t0);
sampler Sampler : register(s0);

cbuffer Parameters : register(b0)
{
	float4 DiffuseColor             : packoffset(c0);
	float3 EmissiveColor            : packoffset(c1);
	float3 SpecularColor            : packoffset(c2);
	float  SpecularPower : packoffset(c2.w);

	float3 LightDirection[3]        : packoffset(c3);
	float3 LightDiffuseColor[3]     : packoffset(c6);
	float3 LightSpecularColor[3]    : packoffset(c9);

	float3 EyePosition              : packoffset(c12);

	float3 FogColor                 : packoffset(c13);
	float4 FogVector                : packoffset(c14);

	float4x4 World                  : packoffset(c15);
	float4x4 WorldInverse           : packoffset(c19);
	float3x3 WorldInverseTranspose  : packoffset(c23);
	float4x4 WorldViewProj          : packoffset(c27);
};