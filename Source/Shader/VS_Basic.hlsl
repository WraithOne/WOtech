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

// Ein Konstantenpuffer, der die drei grundlegenden spaltengerichteten Matrizen f�r das Zusammensetzen von Geometrien speichert.
cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
};

// Pro-Vertex-Daten als Eingabe f�r den Vertex-Shader verwendet.
struct VertexShaderInput
{
	float3 pos : POSITION;
	float3 color : COLOR0;
};

// Pro-Pixel-Farbdaten an den Pixelshader �bergeben.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float3 color : COLOR0;
};

// Einfacher Shader f�r Vertex-Bearbeitung auf der GPU.
PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;
	float4 pos = float4(input.pos, 1.0f);

	// Die Position des Scheitelpunkts in den projektierten Raum transformieren.
	pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.pos = pos;

	// Die Farbe unver�ndert durchlaufen.
	output.color = input.color;

	return output;
}