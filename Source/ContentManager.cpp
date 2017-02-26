////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: ContentManager.cpp
///
///			Created:	22.11.2016
///			Edited:		27.02.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "ContentManager.h"


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
	void ContentManager::OnSuspending()
	{
		throw ref new Platform::NotImplementedException();
	}
	void ContentManager::OnResume()
	{
		throw ref new Platform::NotImplementedException();
	}
}
