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
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_RENDERCOMMAND_H
#define WO_RENDERCOMMAND_H
//////////////
// INCLUDES //
//////////////
#include <pch.h>

namespace WOtech
{
	ref class Mesh;

	public value struct RendererUniforms
	{
		Windows::Foundation::Numerics::float4x4 WorldMatrix;
		Windows::Foundation::Numerics::float4x4 WorldInverseMatrix;
		Windows::Foundation::Numerics::float4x4 ViewMatrix;
		Windows::Foundation::Numerics::float4x4 ProjectionMatrix;
	};

	struct RenderCommand
	{
		Mesh^ mesh;
		RendererUniforms uniforms;
	};

	typedef std::vector<RenderCommand> CommandQueue;
}
#endif
