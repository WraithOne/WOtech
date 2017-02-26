////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: ContentManager.h
///
///			Created:	22.11.2016
///			Edited:		26.02.2017
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
	public:
		ContentManager();
		~ContentManager();

		void OnSuspending();
		void OnResume();

	internal:

	public:
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

