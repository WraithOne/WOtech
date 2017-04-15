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
///			Edited:		15.04.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "Shared\Parameters.hlsli"
#include "Shared\Structures.hlsli"
#include "Shared\Common.hlsli"
#include "Shared\lighting.hlsli"

// Pixel shader: basic.
float4 main(PSInput pin) : SV_Target0
{
	float4 color = pin.Diffuse;

	ApplyFog(color, pin.Specular.w);

	return color;
}