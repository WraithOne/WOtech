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
///			Edited:		22.12.2017
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

	public value struct RendererUniforms
	{
		WOtech::FLOAT4x4 WorldMatrix;
		WOtech::FLOAT4x4 WorldInverseMatrix;
		WOtech::FLOAT4x4 ViewMatrix;
		WOtech::FLOAT4x4 ProjectionMatrix;
	};

	struct RenderCommand
	{
		Mesh^ mesh;
		RendererUniforms uniforms;
	};

	typedef std::vector<RenderCommand> CommandQueue;
}
#endif
