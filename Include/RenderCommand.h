////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: RenderCommand.h
///
///			Description:
///
///			Created:	27.02.2016
///			Edited:		06.04.2016
///
////////////////////////////////////////////////////////////////////////////
#pragma once
//////////////
// INCLUDES //
//////////////
#include "pch.h"

namespace WOtech
{
	namespace Graphic
	{
		ref class Mesh;

		struct RendererUniforms
		{
			DirectX::XMMATRIX ViewMatrix;
			DirectX::XMMATRIX ProjectionMatrix;
			DirectX::XMMATRIX WorldMatrix;
			DirectX::XMMATRIX ModelMatrix;
		};

		struct RenderCommand 
		{
			Mesh^ mesh;
			RendererUniforms uniforms;
		};
	}
}
