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
///			Edited:		01.05.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_VERTEXTYPES_H
#define WO_VERTEXTYPES_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"

namespace WOtech
{
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

	public ref struct VertexPositionColor sealed : public IVertexPosition, IVertexColor
	{
	public:
		static UINT Sizeof() { return (sizeof(Windows::Foundation::Numerics::float3) + sizeof(Windows::Foundation::Numerics::float4)); }
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

	public ref struct VertexPositionTexture sealed : public IVertexPosition, IVertexTexture
	{
	public:
		static UINT Sizeof() { return (sizeof(Windows::Foundation::Numerics::float3) + sizeof(Windows::Foundation::Numerics::float2)); }
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

	public ref struct VertexPositionNormal sealed : public IVertexPosition, IVertexNormal
	{
	public:
		static UINT Sizeof() { return (sizeof(Windows::Foundation::Numerics::float3) + sizeof(Windows::Foundation::Numerics::float3)); }
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

	public ref struct VertexPositionNormalColor sealed : public IVertexPosition, IVertexNormal, IVertexColor
	{
	public:
		static UINT Sizeof() { return (sizeof(Windows::Foundation::Numerics::float3) + sizeof(Windows::Foundation::Numerics::float3) + sizeof(Windows::Foundation::Numerics::float4)); }
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

	public ref struct VertexPositionColorTexture sealed : public IVertexPosition, IVertexColor, IVertexTexture
	{
	public:
		static UINT Sizeof() { return (sizeof(Windows::Foundation::Numerics::float3) + sizeof(Windows::Foundation::Numerics::float3) + sizeof(Windows::Foundation::Numerics::float2)); }
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

	public ref struct VertexPositionNormalTexture sealed : public IVertexPosition, IVertexNormal, IVertexTexture
	{
	public:
		static UINT Sizeof() { return (sizeof(Windows::Foundation::Numerics::float3) + sizeof(Windows::Foundation::Numerics::float3) + sizeof(Windows::Foundation::Numerics::float2)); }
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

	public ref struct VertexPositionNormalColorTexture sealed : public IVertexPosition, IVertexNormal, IVertexColor, IVertexTexture
	{
	public:
		static UINT Sizeof() { return (sizeof(Windows::Foundation::Numerics::float3) + sizeof(Windows::Foundation::Numerics::float3) + sizeof(Windows::Foundation::Numerics::float4) + sizeof(Windows::Foundation::Numerics::float2)); }
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