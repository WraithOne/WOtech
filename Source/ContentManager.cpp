////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: ContentManager.cpp
///
///			Created:	22.11.2016
///			Edited:		07.03.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "ContentManager.h"
#include "DeviceDX11.h"
#include "SpriteBatch.h"
#include "2DComponents.h"
#include "3DComponents.h"
#include "Audio.h"

using namespace WOtech;

namespace WOtech
{
	ContentManager::ContentManager()
	{
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
		m_materialinstanceList.clear();
		m_meshList.clear();

		m_audiosourceList.clear();
	}
	ContentManager::~ContentManager()
	{
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
		m_materialinstanceList.clear();
		m_meshList.clear();

		m_audiosourceList.clear();
	}

	///////////////////////////////////////////////////////////////////////////////////
	// ADD
	void ContentManager::AddSprite(_In_ WOtech::Sprite^ sprite)
	{
		m_spriteList.push_back(sprite);
	}
	void ContentManager::AddAnimatedSprite(_In_ WOtech::AnimatedSprite^ animatedSprite)
	{
		m_animatedspriteList.push_back(animatedSprite);
	}
	void ContentManager::AddGeometry(_In_ WOtech::Geomtry^ geometry)
	{
		m_geometryList.push_back(geometry);
	}
	void ContentManager::AddFont(_In_ WOtech::Font^ font)
	{
		m_fontList.push_back(font);
	}
	void ContentManager::AddText(_In_ WOtech::Text^ text)
	{
		m_textList.push_back(text);
	}

	void ContentManager::AddVertexShader(_In_ WOtech::VertexShader^ vertexShader)
	{
		m_vertexshaderList.push_back(vertexShader);
	}
	void ContentManager::AddPixelShader(_In_ WOtech::PixelShader^ pixelShader)
	{
		m_pixelshaderList.push_back(pixelShader);
	}
	void ContentManager::AddTexture(_In_ WOtech::Texture^ texture)
	{
		m_textureList.push_back(texture);
	}
	void ContentManager::AddVertexBuffer(_In_ WOtech::VertexBuffer^ vertexBuffer)
	{
		m_vertexbufferList.push_back(vertexBuffer);
	}
	void ContentManager::AddIndexBuffer(_In_ WOtech::IndexBuffer^ indexBuffer)
	{
		m_indexbufferList.push_back(indexBuffer);
	}
	void ContentManager::AddMaterial(_In_ WOtech::Material^ material)
	{
		m_materialList.push_back(material);
	}
	void ContentManager::AddMaterialInstance(_In_ WOtech::MaterialInstance^ materialInstance)
	{
		m_materialinstanceList.push_back(materialInstance);
	}
	void ContentManager::AddMesh(_In_ WOtech::Mesh^ mesh)
	{
		m_meshList.push_back(mesh);
	}

	void ContentManager::AddAudioSource(_In_ WOtech::AudioSource^ audioSource)
	{
		m_audiosourceList.push_back(audioSource);
	}

	///////////////////////////////////////////////////////////////////////////////////
	// REMOVE

	void ContentManager::RemoveSprite(_In_ WOtech::Sprite^ sprite)
	{
		std::vector<Sprite^>::iterator it;
		it = std::find(m_spriteList.begin(), m_spriteList.end(), sprite);
		m_spriteList.erase(it);
	}
	void ContentManager::RemoveAnimatedSprite(_In_ WOtech::AnimatedSprite^ animatedSprite)
	{
		std::vector<AnimatedSprite^>::iterator it;
		it = std::find(m_animatedspriteList.begin(), m_animatedspriteList.end(), animatedSprite);
		m_animatedspriteList.erase(it);
	}
	void ContentManager::RemoveGeometry(_In_ WOtech::Geomtry^ geometry)
	{
		std::vector<Geomtry^>::iterator it;
		it = std::find(m_geometryList.begin(), m_geometryList.end(), geometry);
		m_geometryList.erase(it);
	}
	void ContentManager::RemoveFont(_In_ WOtech::Font^ font)
	{
		std::vector<Font^>::iterator it;
		it = std::find(m_fontList.begin(), m_fontList.end(), font);
		m_fontList.erase(it);
	}
	void ContentManager::RemoveText(_In_ WOtech::Text^ text)
	{
		std::vector<Text^>::iterator it;
		it = std::find(m_textList.begin(), m_textList.end(), text);
		m_textList.erase(it);
	}

	void ContentManager::RemoveVertexShader(_In_ WOtech::VertexShader^ vertexShader)
	{
		std::vector<VertexShader^>::iterator it;
		it = std::find(m_vertexshaderList.begin(), m_vertexshaderList.end(), vertexShader);
		m_vertexshaderList.erase(it);
	}
	void ContentManager::RemovePixelShader(_In_ WOtech::PixelShader^ pixelShader)
	{
		std::vector<PixelShader^>::iterator it;
		it = std::find(m_pixelshaderList.begin(), m_pixelshaderList.end(), pixelShader);
		m_pixelshaderList.erase(it);
	}
	void ContentManager::RemoveTexture(_In_ WOtech::Texture^ texture)
	{
		std::vector<Texture^>::iterator it;
		it = std::find(m_textureList.begin(), m_textureList.end(), texture);
		m_textureList.erase(it);
	}
	void ContentManager::RemoveVertexBuffer(_In_ WOtech::VertexBuffer^ vertexBuffer)
	{
		std::vector<VertexBuffer^>::iterator it;
		it = std::find(m_vertexbufferList.begin(), m_vertexbufferList.end(), vertexBuffer);
		m_vertexbufferList.erase(it);
	}
	void ContentManager::RemoveIndexBuffer(_In_ WOtech::IndexBuffer^ indexBuffer)
	{
		std::vector<IndexBuffer^>::iterator it;
		it = std::find(m_indexbufferList.begin(), m_indexbufferList.end(), indexBuffer);
		m_indexbufferList.erase(it);
	}
	void ContentManager::RemoveMaterial(_In_ WOtech::Material^ material)
	{
		std::vector<Material^>::iterator it;
		it = std::find(m_materialList.begin(), m_materialList.end(), material);
		m_materialList.erase(it);
	}
	void ContentManager::RemoveMaterialInstance(_In_ WOtech::MaterialInstance^ materialInstance)
	{
		std::vector<MaterialInstance^>::iterator it;
		it = std::find(m_materialinstanceList.begin(), m_materialinstanceList.end(), materialInstance);
		m_materialinstanceList.erase(it);
	}
	void ContentManager::RemoveMesh(_In_ WOtech::Mesh^ mesh)
	{
		std::vector<Mesh^>::iterator it;
		it = std::find(m_meshList.begin(), m_meshList.end(), mesh);
		m_meshList.erase(it);
	}

	void ContentManager::RemoveAudioSource(_In_ WOtech::AudioSource^ audioSource)
	{
		std::vector<AudioSource^>::iterator it;
		it = std::find(m_audiosourceList.begin(), m_audiosourceList.end(), audioSource);
		m_audiosourceList.erase(it);
	}

	void ContentManager::OnSuspending()
	{
		for (auto a : m_spriteList)
			a->UnLoad();
		for (auto b : m_animatedspriteList)
			b->UnLoad();
		for (auto c : m_geometryList)
			c;
		for (auto d: m_fontList)
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
		for (auto l : m_materialinstanceList)
			l;
		for (auto m : m_meshList)
			m;
		for (auto m : m_audiosourceList)
			m;
	}
	void ContentManager::OnResume(_In_ WOtech::SpriteBatch^ spriteBatch)
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
		for (auto l : m_materialinstanceList)
			l;
		for (auto m : m_meshList)
			m;
		for (auto m : m_audiosourceList)
			m->LoadWave();
	}
}
