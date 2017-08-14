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
	public interface struct IVertexData
	{
		UINT Sizeof();
	};
	public interface struct IVertexPosition
	{
		property Windows::Foundation::Numerics::float3 Position
		{
			Windows::Foundation::Numerics::float3 get();
			void set(_In_ Windows::Foundation::Numerics::float3 position);
		}
	};
	public interface struct IVertexColor
	{
		property Windows::Foundation::Numerics::float4 Color
		{
			Windows::Foundation::Numerics::float4 get();
			void set(_In_ Windows::Foundation::Numerics::float4 color);
		}
	};
	public interface struct IVertexTexture
	{
		property Windows::Foundation::Numerics::float2 TextureCoordinate
		{
			Windows::Foundation::Numerics::float2 get();
			void set(_In_ Windows::Foundation::Numerics::float2 textureCoordinate);
		}
	};
	public interface struct IVertexNormal
	{
		property Windows::Foundation::Numerics::float3 Normal
		{
			Windows::Foundation::Numerics::float3 get();
			void set(_In_ Windows::Foundation::Numerics::float3 normal);
		}
	};

	public ref struct VertexPositionColor sealed : public IVertexData, IVertexPosition, IVertexColor
	{
	public:
		virtual UINT Sizeof() { return (sizeof(m_Position) + sizeof(m_Color)); }
		virtual property Windows::Foundation::Numerics::float3 Position
		{
			Windows::Foundation::Numerics::float3 get() { return m_Position; }
			void set(_In_ Windows::Foundation::Numerics::float3 position) { m_Position = position; }
		}
		virtual property Windows::Foundation::Numerics::float4 Color
		{
			Windows::Foundation::Numerics::float4 get() { return m_Color; }
			void set(_In_ Windows::Foundation::Numerics::float4 color) { m_Color = color; }
		}

	private:
		Windows::Foundation::Numerics::float3 m_Position;
		Windows::Foundation::Numerics::float4 m_Color;
	};

	public ref struct VertexPositionTexture sealed : public IVertexData, IVertexPosition, IVertexTexture
	{
	public:
		virtual UINT Sizeof() { return (sizeof(m_Position) + sizeof(m_TextureCoordinate)); }
		virtual property Windows::Foundation::Numerics::float3 Position
		{
			Windows::Foundation::Numerics::float3 get() { return m_Position; }
			void set(_In_ Windows::Foundation::Numerics::float3 position) { m_Position = position; }
		}
		virtual property Windows::Foundation::Numerics::float2 TextureCoordinate
		{
			Windows::Foundation::Numerics::float2 get() { return m_TextureCoordinate; }
			void set(_In_ Windows::Foundation::Numerics::float2 textureCoordinate) { m_TextureCoordinate = textureCoordinate; }
		}

	private:
		Windows::Foundation::Numerics::float3 m_Position;
		Windows::Foundation::Numerics::float2 m_TextureCoordinate;
	};

	public ref struct VertexPositionNormal sealed : public IVertexData, IVertexPosition, IVertexNormal
	{
	public:
		virtual UINT Sizeof() { return (sizeof(m_Position) + sizeof(m_Normal)); }
		virtual property Windows::Foundation::Numerics::float3 Position
		{
			Windows::Foundation::Numerics::float3 get() { return m_Position; }
			void set(_In_ Windows::Foundation::Numerics::float3 position) { m_Position = position; }
		}
		virtual property Windows::Foundation::Numerics::float3 Normal
		{
			Windows::Foundation::Numerics::float3 get() { return m_Normal; }
			void set(_In_ Windows::Foundation::Numerics::float3 normal) { m_Normal = normal; }
		}

	private:
		Windows::Foundation::Numerics::float3 m_Position;
		Windows::Foundation::Numerics::float3 m_Normal;
	};

	public ref struct VertexPositionNormalColor sealed : public IVertexData, IVertexPosition, IVertexNormal, IVertexColor
	{
	public:
		virtual UINT Sizeof() { return (sizeof(m_Position) + sizeof(m_Normal) + sizeof(m_Color)); }
		virtual property Windows::Foundation::Numerics::float3 Position
		{
			Windows::Foundation::Numerics::float3 get() { return m_Position; }
			void set(_In_ Windows::Foundation::Numerics::float3 position) { m_Position = position; }
		}
		virtual property Windows::Foundation::Numerics::float3 Normal
		{
			Windows::Foundation::Numerics::float3 get() { return m_Normal; }
			void set(_In_ Windows::Foundation::Numerics::float3 normal) { m_Normal = normal; }
		}
		virtual property Windows::Foundation::Numerics::float4 Color
		{
			Windows::Foundation::Numerics::float4 get() { return m_Color; }
			void set(_In_ Windows::Foundation::Numerics::float4 color) { m_Color = color; }
		}

	private:
		Windows::Foundation::Numerics::float3 m_Position;
		Windows::Foundation::Numerics::float3 m_Normal;
		Windows::Foundation::Numerics::float4 m_Color;
	};

	public ref struct VertexPositionColorTexture sealed : public IVertexData, IVertexPosition, IVertexColor, IVertexTexture
	{
	public:
		virtual UINT Sizeof() { return (sizeof(m_Position) + sizeof(m_Color) + sizeof(m_TextureCoordinate)); }
		virtual property Windows::Foundation::Numerics::float3 Position
		{
			Windows::Foundation::Numerics::float3 get() { return m_Position; }
			void set(_In_ Windows::Foundation::Numerics::float3 position) { m_Position = position; }
		}
		virtual property Windows::Foundation::Numerics::float4 Color
		{
			Windows::Foundation::Numerics::float4 get() { return m_Color; }
			void set(_In_ Windows::Foundation::Numerics::float4 color) { m_Color = color; }
		}
		virtual property Windows::Foundation::Numerics::float2 TextureCoordinate
		{
			Windows::Foundation::Numerics::float2 get() { return m_TextureCoordinate; }
			void set(_In_ Windows::Foundation::Numerics::float2 textureCoordinate) { m_TextureCoordinate = textureCoordinate; }
		}

	private:
		Windows::Foundation::Numerics::float3 m_Position;
		Windows::Foundation::Numerics::float4 m_Color;
		Windows::Foundation::Numerics::float2 m_TextureCoordinate;
	};

	public ref struct VertexPositionNormalTexture sealed : public IVertexData, IVertexPosition, IVertexNormal, IVertexTexture
	{
	public:
		virtual UINT Sizeof() { return (sizeof(m_Position) + sizeof(m_Normal) + sizeof(m_TextureCoordinate)); }
		virtual property Windows::Foundation::Numerics::float3 Position
		{
			Windows::Foundation::Numerics::float3 get() { return m_Position; }
			void set(_In_ Windows::Foundation::Numerics::float3 position) { m_Position = position; }
		}
		virtual property Windows::Foundation::Numerics::float3 Normal
		{
			Windows::Foundation::Numerics::float3 get() { return m_Normal; }
			void set(_In_ Windows::Foundation::Numerics::float3 normal) { m_Normal = normal; }
		}
		virtual property Windows::Foundation::Numerics::float2 TextureCoordinate
		{
			Windows::Foundation::Numerics::float2 get() { return m_TextureCoordinate; }
			void set(_In_ Windows::Foundation::Numerics::float2 textureCoordinate) { m_TextureCoordinate = textureCoordinate; }
		}

	private:
		Windows::Foundation::Numerics::float3 m_Position;
		Windows::Foundation::Numerics::float3 m_Normal;
		Windows::Foundation::Numerics::float2 m_TextureCoordinate;
	};

	public ref struct VertexPositionNormalColorTexture sealed : public IVertexData, IVertexPosition, IVertexNormal, IVertexColor, IVertexTexture
	{
	public:
		virtual UINT Sizeof() { return (sizeof(m_Position) + sizeof(m_Normal) + sizeof(m_Color) + sizeof(m_TextureCoordinate)); }
		virtual property Windows::Foundation::Numerics::float3 Position
		{
			Windows::Foundation::Numerics::float3 get() { return m_Position; }
			void set(_In_ Windows::Foundation::Numerics::float3 position) { m_Position = position; }
		}
		virtual property Windows::Foundation::Numerics::float3 Normal
		{
			Windows::Foundation::Numerics::float3 get() { return m_Normal; }
			void set(_In_ Windows::Foundation::Numerics::float3 normal) { m_Normal = normal; }
		}
		virtual property Windows::Foundation::Numerics::float4 Color
		{
			Windows::Foundation::Numerics::float4 get() { return m_Color; }
			void set(_In_ Windows::Foundation::Numerics::float4 color) { m_Color = color; }
		}
		virtual property Windows::Foundation::Numerics::float2 TextureCoordinate
		{
			Windows::Foundation::Numerics::float2 get() { return m_TextureCoordinate; }
			void set(_In_ Windows::Foundation::Numerics::float2 textureCoordinate) { m_TextureCoordinate = textureCoordinate; }
		}

	private:
		Windows::Foundation::Numerics::float3 m_Position;
		Windows::Foundation::Numerics::float3 m_Normal;
		Windows::Foundation::Numerics::float4 m_Color;
		Windows::Foundation::Numerics::float2 m_TextureCoordinate;
	};
}
#endif