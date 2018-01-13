////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: ContentManager.cpp
///
///			Description:
///
///			Created:	22.11.2016
///			Edited:		13.01.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "ContentManager.h"
#include "2DComponents.h"
#include "3DComponents.h"
#include "DeviceDX11.h"
#include "SpriteBatch.h"
#include "Audio.h"

using namespace WOtech;

namespace WOtech
{
	ContentManager::ContentManager()
	{
		m_enabled = false;

		m_imageList.clear();
		m_bitmapList.clear();
		m_spriteList.clear();
		m_animatedspriteList.clear();
		m_geometryList.clear();
		m_fontList.clear();
		m_textList.clear();

		m_vertexshaderList.clear();
		m_pixelshaderList.clear();
		m_textureList.clear();
		m_vertexbufferList.clear();
		m_indexbufferList.clear();
		m_materialList.clear();
		m_meshList.clear();

		m_audiosourceList.clear();
	}
	ContentManager::~ContentManager()
	{
		m_imageList.clear();
		m_bitmapList.clear();
		m_spriteList.clear();
		m_animatedspriteList.clear();
		m_geometryList.clear();
		m_fontList.clear();
		m_textList.clear();

		m_vertexshaderList.clear();
		m_pixelshaderList.clear();
		m_textureList.clear();
		m_vertexbufferList.clear();
		m_indexbufferList.clear();
		m_materialList.clear();
		m_meshList.clear();

		m_audiosourceList.clear();
	}

	///////////////////////////////////////////////////////////////////////////////////
	// ADD
	void ContentManager::AddImage(_In_ WOtech::Image^ image)
	{
		if(m_enabled)
			m_imageList.push_back(image);
	}

	void ContentManager::AddBitmap(_In_ WOtech::Bitmap^ bitmap)
	{
		if (m_enabled)
			m_bitmapList.push_back(bitmap);
	}
	void ContentManager::AddSprite(_In_ WOtech::Sprite^ sprite)
	{
		if (m_enabled)
			m_spriteList.push_back(sprite);
	}
	void ContentManager::AddAnimatedSprite(_In_ WOtech::AnimatedSprite^ animatedSprite)
	{
		if (m_enabled)
			m_animatedspriteList.push_back(animatedSprite);
	}
	void ContentManager::AddGeometry(_In_ WOtech::Geometry^ geometry)
	{
		if (m_enabled)
			m_geometryList.push_back(geometry);
	}
	void ContentManager::AddFont(_In_ WOtech::Font^ font)
	{
		if (m_enabled)
			m_fontList.push_back(font);
	}
	void ContentManager::AddText(_In_ WOtech::Text^ text)
	{
		if (m_enabled)
			m_textList.push_back(text);
	}

	void ContentManager::AddVertexShader(_In_ WOtech::VertexShader^ vertexShader)
	{
		if (m_enabled)
			m_vertexshaderList.push_back(vertexShader);
	}
	void ContentManager::AddPixelShader(_In_ WOtech::PixelShader^ pixelShader)
	{
		if (m_enabled)
			m_pixelshaderList.push_back(pixelShader);
	}
	void ContentManager::AddTexture(_In_ WOtech::Texture^ texture)
	{
		if (m_enabled)
			m_textureList.push_back(texture);
	}
	void ContentManager::AddVertexBuffer(_In_ WOtech::VertexBuffer^ vertexBuffer)
	{
		if (m_enabled)
			m_vertexbufferList.push_back(vertexBuffer);
	}
	void ContentManager::AddIndexBuffer(_In_ WOtech::IndexBuffer^ indexBuffer)
	{
		if (m_enabled)
			m_indexbufferList.push_back(indexBuffer);
	}
	void ContentManager::AddMaterial(_In_ WOtech::IMaterial^ material)
	{
		if (m_enabled)
			m_materialList.push_back(material);
	}
	void ContentManager::AddMesh(_In_ WOtech::Mesh^ mesh)
	{
		if (m_enabled)
			m_meshList.push_back(mesh);
	}

	void ContentManager::AddAudioSource(_In_ WOtech::AudioSource^ audioSource)
	{
		if (m_enabled)
			m_audiosourceList.push_back(audioSource);
	}

	///////////////////////////////////////////////////////////////////////////////////
	// REMOVE

	void ContentManager::RemoveImage(_In_ WOtech::Image^ image)
	{
		if (m_enabled)
		{
			std::vector<Image^>::iterator it;
			it = std::find(m_imageList.begin(), m_imageList.end(), image);
			m_imageList.erase(it);
		}	
	}
	void ContentManager::RemoveBitmap(_In_ WOtech::Bitmap^ bitmap)
	{
		if (m_enabled)
		{
			std::vector<Bitmap^>::iterator it;
			it = std::find(m_bitmapList.begin(), m_bitmapList.end(), bitmap);
			m_bitmapList.erase(it);
		}	
	}
	void ContentManager::RemoveSprite(_In_ WOtech::Sprite^ sprite)
	{
		if (m_enabled)
		{
			std::vector<Sprite^>::iterator it;
			it = std::find(m_spriteList.begin(), m_spriteList.end(), sprite);
			m_spriteList.erase(it);
		}
	}
	void ContentManager::RemoveAnimatedSprite(_In_ WOtech::AnimatedSprite^ animatedSprite)
	{
		if (m_enabled)
		{
			std::vector<AnimatedSprite^>::iterator it;
			it = std::find(m_animatedspriteList.begin(), m_animatedspriteList.end(), animatedSprite);
			m_animatedspriteList.erase(it);
		}
	}
	void ContentManager::RemoveGeometry(_In_ WOtech::Geometry^ geometry)
	{
		if (m_enabled)
		{
			std::vector<Geometry^>::iterator it;
			it = std::find(m_geometryList.begin(), m_geometryList.end(), geometry);
			m_geometryList.erase(it);
		}
	}
	void ContentManager::RemoveFont(_In_ WOtech::Font^ font)
	{
		if (m_enabled)
		{
			std::vector<Font^>::iterator it;
			it = std::find(m_fontList.begin(), m_fontList.end(), font);
			m_fontList.erase(it);
		}
	}
	void ContentManager::RemoveText(_In_ WOtech::Text^ text)
	{
		if (m_enabled)
		{
			std::vector<Text^>::iterator it;
			it = std::find(m_textList.begin(), m_textList.end(), text);
			m_textList.erase(it);
		}
	}

	void ContentManager::RemoveVertexShader(_In_ WOtech::VertexShader^ vertexShader)
	{
		if (m_enabled)
		{
			std::vector<VertexShader^>::iterator it;
			it = std::find(m_vertexshaderList.begin(), m_vertexshaderList.end(), vertexShader);
			m_vertexshaderList.erase(it);
		}	
	}
	void ContentManager::RemovePixelShader(_In_ WOtech::PixelShader^ pixelShader)
	{
		if (m_enabled)
		{
			std::vector<PixelShader^>::iterator it;
			it = std::find(m_pixelshaderList.begin(), m_pixelshaderList.end(), pixelShader);
			m_pixelshaderList.erase(it);
		}
	}
	void ContentManager::RemoveTexture(_In_ WOtech::Texture^ texture)
	{
		if (m_enabled)
		{
			std::vector<Texture^>::iterator it;
			it = std::find(m_textureList.begin(), m_textureList.end(), texture);
			m_textureList.erase(it);
		}
	}
	void ContentManager::RemoveVertexBuffer(_In_ WOtech::VertexBuffer^ vertexBuffer)
	{
		if (m_enabled)
		{
			std::vector<VertexBuffer^>::iterator it;
			it = std::find(m_vertexbufferList.begin(), m_vertexbufferList.end(), vertexBuffer);
			m_vertexbufferList.erase(it);
		}
	}
	void ContentManager::RemoveIndexBuffer(_In_ WOtech::IndexBuffer^ indexBuffer)
	{
		if (m_enabled)
		{
			std::vector<IndexBuffer^>::iterator it;
			it = std::find(m_indexbufferList.begin(), m_indexbufferList.end(), indexBuffer);
			m_indexbufferList.erase(it);
		}	
	}
	void ContentManager::RemoveMaterial(_In_ WOtech::IMaterial^ material)
	{
		if (m_enabled)
		{
			std::vector<IMaterial^>::iterator it;
			it = std::find(m_materialList.begin(), m_materialList.end(), material);
			m_materialList.erase(it);
		}
	}
	void ContentManager::RemoveMesh(_In_ WOtech::Mesh^ mesh)
	{
		if (m_enabled)
		{
			std::vector<Mesh^>::iterator it;
			it = std::find(m_meshList.begin(), m_meshList.end(), mesh);
			m_meshList.erase(it);
		}
	}

	void ContentManager::RemoveAudioSource(_In_ WOtech::AudioSource^ audioSource)
	{
		if (m_enabled)
		{
			std::vector<AudioSource^>::iterator it;
			it = std::find(m_audiosourceList.begin(), m_audiosourceList.end(), audioSource);
			m_audiosourceList.erase(it);
		}
	}

	void ContentManager::OnSuspending()
	{
		if (m_enabled)
		{
			for (auto a : m_spriteList)
				a->UnLoad();
			for (auto b : m_animatedspriteList)
				b->UnLoad();
			for (auto c : m_geometryList)
				c;
			for (auto d : m_fontList)
				d->UnLoad();
			for (auto e : m_textList)
				e;
			for (auto f : m_vertexshaderList)
				f;
			for (auto g : m_pixelshaderList)
				g;
			for (auto h : m_textureList)
				h;
			for (auto i : m_vertexbufferList)
				i;
			for (auto j : m_indexbufferList)
				j;
			for (auto k : m_materialList)
				k;
			//for (auto l : )
			//	l;
			for (auto m : m_meshList)
				m;
			for (auto n : m_audiosourceList)
				n;
			for (auto o : m_imageList)
				o->Reset();
			for (auto p : m_bitmapList)
				p->Reset();
		}
	}
	void ContentManager::OnResume(_In_ WOtech::SpriteBatch^ spriteBatch)
	{
		if (m_enabled)
		{
			for (auto a : m_spriteList)
				a->Load(spriteBatch);
			for (auto b : m_animatedspriteList)
				b->Load(spriteBatch);
			for (auto c : m_geometryList)
				c;
			for (auto d : m_fontList)
				d->Load();
			for (auto e : m_textList)
				e;
			for (auto f : m_vertexshaderList)
				f;
			for (auto g : m_pixelshaderList)
				g;
			for (auto h : m_textureList)
				h;
			for (auto i : m_vertexbufferList)
				i;
			for (auto j : m_indexbufferList)
				j;
			for (auto k : m_materialList)
				k;
			//for (auto l : )
			//	l;
			for (auto m : m_meshList)
				m;
			for (auto n : m_audiosourceList)
				n->LoadWave();
			for (auto o : m_imageList)
				o;
			for (auto p : m_bitmapList)
				p;
		}
	}
	void ContentManager::OnWindowSizeChanged(_In_ Windows::Foundation::Size windowSize)
	{
		if (m_enabled)
		{
			for (auto a : m_spriteList)
				a->UnLoad();
			for (auto b : m_animatedspriteList)
				b->UnLoad();
			for (auto c : m_geometryList)
				c;
			for (auto d : m_fontList)
				d->UnLoad();
			for (auto e : m_textList)
				e;
			for (auto f : m_vertexshaderList)
				f;
			for (auto g : m_pixelshaderList)
				g;
			for (auto h : m_textureList)
				h;
			for (auto i : m_vertexbufferList)
				i;
			for (auto j : m_indexbufferList)
				j;
			for (auto k : m_materialList)
				k;
			//for (auto l : )
			//	l;
			for (auto m : m_meshList)
				m;
			for (auto n : m_audiosourceList)
				n;
			for (auto o : m_imageList)
				o->Reset();
			for (auto p : m_bitmapList)
				p->Reset();
		}
	}
	void ContentManager::OnDpiChanged(_In_ float32 dpi)
	{
		if (m_enabled)
		{
			for (auto a : m_spriteList)
				a->UnLoad();
			for (auto b : m_animatedspriteList)
				b->UnLoad();
			for (auto c : m_geometryList)
				c;
			for (auto d : m_fontList)
				d->UnLoad();
			for (auto e : m_textList)
				e;
			for (auto f : m_vertexshaderList)
				f;
			for (auto g : m_pixelshaderList)
				g;
			for (auto h : m_textureList)
				h;
			for (auto i : m_vertexbufferList)
				i;
			for (auto j : m_indexbufferList)
				j;
			for (auto k : m_materialList)
				k;
			//for (auto l : )
			//	l;
			for (auto m : m_meshList)
				m;
			for (auto n : m_audiosourceList)
				n;
			for (auto o : m_imageList)
				o->Reset();
			for (auto p : m_bitmapList)
				p->Reset();
		}	
	}
	void ContentManager::OnOrientationChanged(_In_ Windows::Graphics::Display::DisplayOrientations currentOrientation)
	{
		if (m_enabled)
		{
			for (auto i : m_imageList)
				i->Reset();

			for (auto j : m_bitmapList)
				j->Reset();
		}
	}
	void ContentManager::OnDisplayContentsInvalidated()
	{
		if (m_enabled)
		{
			for (auto i : m_imageList)
				i->Reset();

			for (auto j : m_bitmapList)
				j->Reset();
		}
	}
	void ContentManager::StereoEnabledChanged(_In_ Platform::Boolean stereoEnabled)
	{
		if (m_enabled)
		{
			for (auto i : m_imageList)
				i->Reset();

			for (auto j : m_bitmapList)
				j->Reset();
		}
	}
}