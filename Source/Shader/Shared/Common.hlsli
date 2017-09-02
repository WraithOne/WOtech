////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Common.hlsli
///
///			Description:
///
///			Created:	15.04.2017
///			Edited:		02.09.2017
///
////////////////////////////////////////////////////////////////////////////

float ComputeFogFactor(float4 position)
{
	return saturate(dot(position, FogVector));
}

void ApplyFog(inout float4 color, float fogFactor)
{
	color.rgb = lerp(color.rgb, FogColor * color.a, fogFactor);
}

void AddSpecular(inout float4 color, float3 specular)
{
	color.rgb += specular * color.a;
}

float3 BiasX2(float3 x)
{
	return 2.0f * x - 1.0f;
}

struct CommonVSOutput
{
	float4 Pos_ps;
	float4 Diffuse;
	float3 Specular;
	float  FogFactor;
};

CommonVSOutput ComputeCommonVSOutput(float4 position)
{
	CommonVSOutput vout;

	vout.Pos_ps = mul(position, WorldViewProj);
	vout.Diffuse = DiffuseColor;
	vout.Specular = 0;
	vout.FogFactor = ComputeFogFactor(position);

	return vout;
}

#define SetCommonVSOutputParams \
	vout.PositionPS = cout.Pos_ps; \
	vout.Diffuse = cout.Diffuse; \
	vout.Specular = float4(cout.Specular, cout.FogFactor);

#define SetCommonVSOutputParamsNoFog \
	vout.PositionPS = cout.Pos_ps; \
	vout.Diffuse = cout.Diffuse;