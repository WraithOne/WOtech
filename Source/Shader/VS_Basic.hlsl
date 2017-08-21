////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: VS_Basic.hlsl
///
///			Description:
///
///			Created:	15.04.2017
///			Edited:		14.08.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "Shared\Parameters.hlsli"
#include "Shared\Structures.hlsli"
#include "Shared\Common.hlsli"
#include "Shared\Lighting.hlsli"

// Vertex shader: no fog.
VSOutputNoFog main(VSInput vin)
{
	VSOutputNoFog vout;

	CommonVSOutput cout = ComputeCommonVSOutput(vin.Position);
	SetCommonVSOutputParamsNoFog;

	return vout;
}