////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: ContentManager.h
///
///			Description:
///
///			Created:	22.11.2016
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_CONTENTMANAGER_H
#define WO_CONTENTMANAGER_H

//////////////
// INCLUDES //
//////////////
#include <pch.h>

namespace WOtech
{
	/////////////////////////////////////////////////////////////////////////
	// Forward declarations
	//System
	ref class SpriteBatch;

	// 2D
	ref class Image;
	ref class Bitmap;
	ref class Sprite;
	ref class AnimatedSprite;
	ref class Geometry;
	ref class Font;
	ref class Text;

	// 3D
	ref class VertexShader;
	ref class PixelShader;
	ref class Texture;
	ref class VertexBuffer;
	ref class IndexBuffer;
	interface class IMaterial;
	ref class Mesh;

	// Audio
	ref class AudioSource;

	public ref class ContentManager sealed
	{
	private:
		ContentManager();
		~ContentManager();

	internal:
		void AddImage(_In_ WOtech::Image^ image);
		void AddBitmap(_In_ WOtech::Bitmap^ bitmap);
		void AddSprite(_In_ WOtech::Sprite^ sprite);
		void AddAnimatedSprite(_In_ WOtech::AnimatedSprite^ animatedSprite);
		void AddGeometry(_In_ WOtech::Geometry^ geometry);
		void AddFont(_In_ WOtech::Font^ font);
		void AddText(_In_ WOtech::Text^ text);

		void AddVertexShader(_In_ WOtech::VertexShader^ vertexShader);
		void AddPixelShader(_In_ WOtech::PixelShader^ pixelShader);
		void AddTexture(_In_ WOtech::Texture^ texture);
		void AddVertexBuffer(_In_ WOtech::VertexBuffer^ vertexBuffer);
		void AddIndexBuffer(_In_ WOtech::IndexBuffer^ indexBuffer);
		void AddMaterial(_In_ WOtech::IMaterial^ material);
		void AddMesh(_In_ WOtech::Mesh^ mesh);

		void AddAudioSource(_In_ WOtech::AudioSource^ audioSource);

		void RemoveImage(_In_ WOtech::Image^ image);
		void RemoveBitmap(_In_ WOtech::Bitmap^ bitmap);
		void RemoveSprite(_In_ WOtech::Sprite^ sprite);
		void RemoveAnimatedSprite(_In_ WOtech::AnimatedSprite^ animatedSprite);
		void RemoveGeometry(_In_ WOtech::Geometry^ geometry);
		void RemoveFont(_In_ WOtech::Font^ font);
		void RemoveText(_In_ WOtech::Text^ text);

		void RemoveVertexShader(_In_ WOtech::VertexShader^ vertexShader);
		void RemovePixelShader(_In_ WOtech::PixelShader^ pixelShader);
		void RemoveTexture(_In_ WOtech::Texture^ texture);
		void RemoveVertexBuffer(_In_ WOtech::VertexBuffer^ vertexBuffer);
		void RemoveIndexBuffer(_In_ WOtech::IndexBuffer^ indexBuffer);
		void RemoveMaterial(_In_ WOtech::IMaterial^ material);
		void RemoveMesh(_In_ WOtech::Mesh^ mesh);

		void RemoveAudioSource(_In_ WOtech::AudioSource^ audioSource);

	public:
		property Platform::Boolean Enable
		{
			Platform::Boolean get() { return m_enabled; };
			void set(_In_ Platform::Boolean enable) { m_enabled = enable; }
		}

		void OnSuspending();
		void OnResume(_In_ WOtech::SpriteBatch^ spriteBatch);
		void OnWindowSizeChanged(_In_ Windows::Foundation::Size windowSize);
		void OnDpiChanged(_In_ float32 dpi);
		void OnOrientationChanged(_In_ Windows::Graphics::Display::DisplayOrientations currentOrientation);
		void OnDisplayContentsInvalidated();
		void StereoEnabledChanged(_In_ Platform::Boolean stereoEnabled);

		static property ContentManager^ Instance
		{
			ContentManager^ get()
			{
				static ContentManager^ instance = ref new ContentManager();
				return instance;
			}
		}

	private:
		Platform::Boolean						m_enabled;

		std::vector<WOtech::Image^>				m_imageList;
		std::vector<WOtech::Bitmap^>			m_bitmapList;
		std::vector<WOtech::Sprite^>			m_spriteList;
		std::vector<WOtech::AnimatedSprite^>	m_animatedspriteList;
		std::vector<WOtech::Geometry^>			m_geometryList;
		std::vector<WOtech::Font^>				m_fontList;
		std::vector<WOtech::Text^>				m_textList;

		std::vector<WOtech::VertexShader^>		m_vertexshaderList;
		std::vector<WOtech::PixelShader^>		m_pixelshaderList;
		std::vector<WOtech::Texture^>			m_textureList;
		std::vector<WOtech::VertexBuffer^>		m_vertexbufferList;
		std::vector<WOtech::IndexBuffer^>		m_indexbufferList;
		std::vector<WOtech::IMaterial^>			m_materialList;
		std::vector<WOtech::Mesh^>				m_meshList;
		std::vector<WOtech::AudioSource^>		m_audiosourceList;
	};
}
#endif
