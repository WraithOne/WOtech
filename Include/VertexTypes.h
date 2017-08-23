////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: VertexTypes.h
///
///			Description:
///
///			Created:	25.03.2017
///			Edited:		14.08.2017
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_VERTEXTYPES_H
#define WO_VERTEXTYPES_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include <windows.foundation.numerics.h>

namespace WOtech
{
	public value struct FLOAT2
	{
		float X;
		float Y;
	};

	public value struct FLOAT3
	{
		float X;
		float Y;
		float Z;
	};

	public value struct FLOAT4
	{
		float X;
		float Y;
		float Z;
		float W;
	};

	public value struct FLOAT4x4
	{
		float M11, M12, M13, M14;
		float M21, M22, M23, M24;
		float M31, M32, M33, M34;
		float M41, M42, M43, M44;
	};

	public interface struct IVertexPosition
	{
		property WOtech::FLOAT3 Position
		{
			WOtech::FLOAT3 get();
			void set(_In_ WOtech::FLOAT3 position);
		}
	};
	public interface struct IVertexColor
	{
		property WOtech::FLOAT4 Color
		{
			WOtech::FLOAT4 get();
			void set(_In_ WOtech::FLOAT4 color);
		}
	};
	public interface struct IVertexTexture
	{
		property WOtech::FLOAT2 TextureCoordinate
		{
			WOtech::FLOAT2 get();
			void set(_In_ WOtech::FLOAT2 textureCoordinate);
		}
	};
	public interface struct IVertexNormal
	{
		property WOtech::FLOAT3 Normal
		{
			WOtech::FLOAT3 get();
			void set(_In_ WOtech::FLOAT3 normal);
		}
	};

	public ref struct VertexPositionColor sealed : public IVertexPosition, IVertexColor
	{
	public:
		static UINT Sizeof() { return (sizeof(WOtech::FLOAT3) + sizeof(WOtech::FLOAT4)); }
		virtual property WOtech::FLOAT3 Position
		{
			WOtech::FLOAT3 get() { return m_Position; }
			void set(_In_ WOtech::FLOAT3 position) { m_Position = position; }
		}
		virtual property WOtech::FLOAT4 Color
		{
			WOtech::FLOAT4 get() { return m_Color; }
			void set(_In_ WOtech::FLOAT4 color) { m_Color = color; }
		}

	private:
		WOtech::FLOAT3 m_Position;
		WOtech::FLOAT4 m_Color;
	};

	public ref struct VertexPositionTexture sealed : public IVertexPosition, IVertexTexture
	{
	public:
		static UINT Sizeof() { return (sizeof(WOtech::FLOAT3) + sizeof(WOtech::FLOAT2)); }
		virtual property WOtech::FLOAT3 Position
		{
			WOtech::FLOAT3 get() { return m_Position; }
			void set(_In_ WOtech::FLOAT3 position) { m_Position = position; }
		}
		virtual property WOtech::FLOAT2 TextureCoordinate
		{
			WOtech::FLOAT2 get() { return m_TextureCoordinate; }
			void set(_In_ WOtech::FLOAT2 textureCoordinate) { m_TextureCoordinate = textureCoordinate; }
		}

	private:
		WOtech::FLOAT3 m_Position;
		WOtech::FLOAT2 m_TextureCoordinate;
	};

	public ref struct VertexPositionNormal sealed : public IVertexPosition, IVertexNormal
	{
	public:
		static UINT Sizeof() { return (sizeof(WOtech::FLOAT3) + sizeof(WOtech::FLOAT3)); }
		virtual property WOtech::FLOAT3 Position
		{
			WOtech::FLOAT3 get() { return m_Position; }
			void set(_In_ WOtech::FLOAT3 position) { m_Position = position; }
		}
		virtual property WOtech::FLOAT3 Normal
		{
			WOtech::FLOAT3 get() { return m_Normal; }
			void set(_In_ WOtech::FLOAT3 normal) { m_Normal = normal; }
		}

	private:
		WOtech::FLOAT3 m_Position;
		WOtech::FLOAT3 m_Normal;
	};

	public ref struct VertexPositionNormalColor sealed : public IVertexPosition, IVertexNormal, IVertexColor
	{
	public:
		static UINT Sizeof() { return (sizeof(WOtech::FLOAT3) + sizeof(WOtech::FLOAT3) + sizeof(WOtech::FLOAT4)); }
		virtual property WOtech::FLOAT3 Position
		{
			WOtech::FLOAT3 get() { return m_Position; }
			void set(_In_ WOtech::FLOAT3 position) { m_Position = position; }
		}
		virtual property WOtech::FLOAT3 Normal
		{
			WOtech::FLOAT3 get() { return m_Normal; }
			void set(_In_ WOtech::FLOAT3 normal) { m_Normal = normal; }
		}
		virtual property WOtech::FLOAT4 Color
		{
			WOtech::FLOAT4 get() { return m_Color; }
			void set(_In_ WOtech::FLOAT4 color) { m_Color = color; }
		}

	private:
		WOtech::FLOAT3 m_Position;
		WOtech::FLOAT3 m_Normal;
		WOtech::FLOAT4 m_Color;
	};

	public ref struct VertexPositionColorTexture sealed : public IVertexPosition, IVertexColor, IVertexTexture
	{
	public:
		static UINT Sizeof() { return (sizeof(WOtech::FLOAT3) + sizeof(WOtech::FLOAT3) + sizeof(WOtech::FLOAT2)); }
		virtual property WOtech::FLOAT3 Position
		{
			WOtech::FLOAT3 get() { return m_Position; }
			void set(_In_ WOtech::FLOAT3 position) { m_Position = position; }
		}
		virtual property WOtech::FLOAT4 Color
		{
			WOtech::FLOAT4 get() { return m_Color; }
			void set(_In_ WOtech::FLOAT4 color) { m_Color = color; }
		}
		virtual property WOtech::FLOAT2 TextureCoordinate
		{
			WOtech::FLOAT2 get() { return m_TextureCoordinate; }
			void set(_In_ WOtech::FLOAT2 textureCoordinate) { m_TextureCoordinate = textureCoordinate; }
		}

	private:
		WOtech::FLOAT3 m_Position;
		WOtech::FLOAT4 m_Color;
		WOtech::FLOAT2 m_TextureCoordinate;
	};

	public ref struct VertexPositionNormalTexture sealed : public IVertexPosition, IVertexNormal, IVertexTexture
	{
	public:
		static UINT Sizeof() { return (sizeof(WOtech::FLOAT3) + sizeof(WOtech::FLOAT3) + sizeof(WOtech::FLOAT2)); }
		virtual property WOtech::FLOAT3 Position
		{
			WOtech::FLOAT3 get() { return m_Position; }
			void set(_In_ WOtech::FLOAT3 position) { m_Position = position; }
		}
		virtual property WOtech::FLOAT3 Normal
		{
			WOtech::FLOAT3 get() { return m_Normal; }
			void set(_In_ WOtech::FLOAT3 normal) { m_Normal = normal; }
		}
		virtual property WOtech::FLOAT2 TextureCoordinate
		{
			WOtech::FLOAT2 get() { return m_TextureCoordinate; }
			void set(_In_ WOtech::FLOAT2 textureCoordinate) { m_TextureCoordinate = textureCoordinate; }
		}

	private:
		WOtech::FLOAT3 m_Position;
		WOtech::FLOAT3 m_Normal;
		WOtech::FLOAT2 m_TextureCoordinate;
	};

	public ref struct VertexPositionNormalColorTexture sealed : public IVertexPosition, IVertexNormal, IVertexColor, IVertexTexture
	{
	public:
		static UINT Sizeof() { return (sizeof(WOtech::FLOAT3) + sizeof(WOtech::FLOAT3) + sizeof(WOtech::FLOAT4) + sizeof(WOtech::FLOAT2)); }
		virtual property WOtech::FLOAT3 Position
		{
			WOtech::FLOAT3 get() { return m_Position; }
			void set(_In_ WOtech::FLOAT3 position) { m_Position = position; }
		}
		virtual property WOtech::FLOAT3 Normal
		{
			WOtech::FLOAT3 get() { return m_Normal; }
			void set(_In_ WOtech::FLOAT3 normal) { m_Normal = normal; }
		}
		virtual property WOtech::FLOAT4 Color
		{
			WOtech::FLOAT4 get() { return m_Color; }
			void set(_In_ WOtech::FLOAT4 color) { m_Color = color; }
		}
		virtual property WOtech::FLOAT2 TextureCoordinate
		{
			WOtech::FLOAT2 get() { return m_TextureCoordinate; }
			void set(_In_ WOtech::FLOAT2 textureCoordinate) { m_TextureCoordinate = textureCoordinate; }
		}

	private:
		WOtech::FLOAT3 m_Position;
		WOtech::FLOAT3 m_Normal;
		WOtech::FLOAT4 m_Color;
		WOtech::FLOAT2 m_TextureCoordinate;
	};
}
#endif