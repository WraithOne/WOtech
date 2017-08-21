////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: PS_Basic.hlsl
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

// Pixel shader: no fog.
float4 main(PSInputNoFog pin) : SV_Target0
{
	return pin.Diffuse;
}