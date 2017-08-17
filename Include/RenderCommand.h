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
///			Edited:		18.08.2017
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_RENDERCOMMAND_H
#define WO_RENDERCOMMAND_H
//////////////
// INCLUDES //
//////////////
#include "pch.h"

namespace WOtech
{
	ref class Mesh;

	struct RendererUniforms
	{
		DirectX::XMFLOAT4X4 ModelMatrix;
		DirectX::XMFLOAT4X4 ViewMatrix;
		DirectX::XMFLOAT4X4 ProjectionMatrix;
	};

	struct RenderCommand
	{
		Mesh^ mesh;
		RendererUniforms uniforms;
	};

	typedef std::vector<RenderCommand> CommandQueue;
}
#endif
