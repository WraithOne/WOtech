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
///			Edited:		27.02.2017
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_CONTENTMANAGER_H
#define WO_CONTENTMANAGER_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"

namespace WOtech
{
	/////////////////////////////////////////////////////////////////////////
	// Forward declarations
	//System
	ref class SpriteBatch;

	// 2D
	ref class Sprite;
	ref class AnimatedSprite;
	ref class Geomtry;
	ref class Font;
	ref class Text;

	// 3D
	ref class VertexShader;
	ref class PixelShader;
	ref class Texture;
	ref class VertexBuffer;
	ref class IndexBuffer;
	ref class Material;
	ref class MaterialInstance;
	ref class Mesh;

	// Audio
	ref class AudioSource;

	public ref class ContentManager sealed
	{
	private:
		ContentManager();
		~ContentManager();

	internal:
		void AddSprite(_In_ WOtech::Sprite^ sprite);
		void AddAnimatedSprite(_In_ WOtech::AnimatedSprite^ animatedSprite);
		void AddGeometry(_In_ WOtech::Geomtry^ geometry);
		void AddFont(_In_ WOtech::Font^ font);
		void AddText(_In_ WOtech::Text^ text);

		void AddVertexShader(_In_ WOtech::VertexShader^ vertexShader);
		void AddPixelShader(_In_ WOtech::PixelShader^ pixelShader);
		void AddTexture(_In_ WOtech::Texture^ texture);
		void AddVertexBuffer(_In_ WOtech::VertexBuffer^ vertexBuffer);
		void AddIndexBuffer(_In_ WOtech::IndexBuffer^ indexBuffer);
		void AddMaterial(_In_ WOtech::Material^ material);
		void AddMaterialInstance(_In_ WOtech::MaterialInstance^ materialInstance);
		void AddMesh(_In_ WOtech::Mesh^ mesh);

		void AddAudioSource(_In_ WOtech::AudioSource^ audioSource);

		void RemoveSprite(_In_ WOtech::Sprite^ sprite);
		void RemoveAnimatedSprite(_In_ WOtech::AnimatedSprite^ animatedSprite);
		void RemoveGeometry(_In_ WOtech::Geomtry^ geometry);
		void RemoveFont(_In_ WOtech::Font^ font);
		void RemoveText(_In_ WOtech::Text^ text);

		void RemoveVertexShader(_In_ WOtech::VertexShader^ vertexShader);
		void RemovePixelShader(_In_ WOtech::PixelShader^ pixelShader);
		void RemoveTexture(_In_ WOtech::Texture^ texture);
		void RemoveVertexBuffer(_In_ WOtech::VertexBuffer^ vertexBuffer);
		void RemoveIndexBuffer(_In_ WOtech::IndexBuffer^ indexBuffer);
		void RemoveMaterial(_In_ WOtech::Material^ material);
		void RemoveMaterialInstance(_In_ WOtech::MaterialInstance^ materialInstance);
		void RemoveMesh(_In_ WOtech::Mesh^ mesh);

		void RemoveAudioSource(_In_ WOtech::AudioSource^ audioSource);

	public:
		void OnSuspending();
		void OnResume(_In_ WOtech::SpriteBatch^ spriteBatch);

		static property ContentManager^ Instance
		{
			ContentManager^ get()
			{
				static ContentManager^ instance = ref new ContentManager();
				return instance;
			}
		}
	private:
		std::vector<WOtech::Sprite^>			m_spriteList;
		std::vector<WOtech::AnimatedSprite^>	m_animatedspriteList;
		std::vector<WOtech::Geomtry^>			m_geometryList;
		std::vector<WOtech::Font^>				m_fontList;
		std::vector<WOtech::Text^>				m_textList;

		std::vector<WOtech::VertexShader^>		m_vertexshaderList;
		std::vector<WOtech::PixelShader^>		m_pixelshaderList;
		std::vector<WOtech::Texture^>			m_textureList;
		std::vector<WOtech::VertexBuffer^>		m_vertexbufferList;
		std::vector<WOtech::IndexBuffer^>		m_indexbufferList;
		std::vector<WOtech::Material^>			m_materialList;
		std::vector<WOtech::MaterialInstance^>	m_materialinstanceList;
		std::vector<WOtech::Mesh^>				m_meshList;
		std::vector<WOtech::AudioSource^>		m_audiosourceList;
	};
}
#endif
