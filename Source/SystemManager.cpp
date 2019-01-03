////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: SystemManager.cpp
///
///			Description:
///
///			Created:	18.03.2015
///			Edited:		12.05.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <SystemManager.h>

#include <DeviceDX11.h>
#include <SpriteBatch.h>
#include <Audio.h>
#include <Input.h>

namespace WOtech
{
	SystemManager::SystemManager() : m_enabled(true)
	{
		m_inputManagerList.clear();
		m_audioEngineList.clear();
		m_spriteBatchList.clear();
		m_deviceDX11List.clear();
	}

	SystemManager::~SystemManager()
	{
		m_inputManagerList.clear();
		m_audioEngineList.clear();
		m_spriteBatchList.clear();
		m_deviceDX11List.clear();
	}

	void SystemManager::AddDeviceDX11(_In_ WOtech::DeviceDX11^ renderer)
	{
		if(m_enabled)
			m_deviceDX11List.push_back(renderer);
	}
	void SystemManager::AddSpriteBatch(_In_ WOtech::SpriteBatch^ spritebatch)
	{
		if (m_enabled)
			m_spriteBatchList.push_back(spritebatch);
	}
	void SystemManager::AddAudioEngine(_In_ WOtech::AudioEngine^ audioEngine)
	{
		if (m_enabled)
			m_audioEngineList.push_back(audioEngine);
	}
	void SystemManager::AddInputManager(_In_ WOtech::InputManager^ inputManager)
	{
		if (m_enabled)
			m_inputManagerList.push_back(inputManager);
	}

	void SystemManager::RemoveDeviceDX11(_In_ WOtech::DeviceDX11 ^ devicedx11)
	{
		if (m_enabled)
		{
			std::vector<DeviceDX11^>::iterator it;
			it = std::find(m_deviceDX11List.begin(), m_deviceDX11List.end(), devicedx11);
			m_deviceDX11List.erase(it);
		}
	}
	void SystemManager::RemoveSpriteBatch(_In_ WOtech::SpriteBatch^ spritebatch)
	{
		if (m_enabled)
		{
			std::vector<SpriteBatch^>::iterator it;
			it = std::find(m_spriteBatchList.begin(), m_spriteBatchList.end(), spritebatch);
			m_spriteBatchList.erase(it);
		}
	}
	void SystemManager::RemoveAudioEngine(_In_ WOtech::AudioEngine^ audioEngine)
	{
		if (m_enabled)
		{
			std::vector<AudioEngine^>::iterator it;
			it = std::find(m_audioEngineList.begin(), m_audioEngineList.end(), audioEngine);
			m_audioEngineList.erase(it);
		}
	}
	void SystemManager::RemoveInputManager(_In_ WOtech::InputManager^ inputManager)
	{
		if (m_enabled)
		{
			std::vector<InputManager^>::iterator it;
			it = std::find(m_inputManagerList.begin(), m_inputManagerList.end(), inputManager);
			m_inputManagerList.erase(it);
		}	
	}

	WOtech::DeviceDX11^ SystemManager::GetDeviceDX11()
	{
		if(m_deviceDX11List.empty())
			throw ref new Platform::OutOfBoundsException();
		
		return m_deviceDX11List.at(0);
	}

	WOtech::SpriteBatch^ SystemManager::GetSpriteBatch()
	{
		if(m_spriteBatchList.empty())
			throw ref new Platform::OutOfBoundsException();

		return m_spriteBatchList.at(0);
	}

	WOtech::InputManager^ SystemManager::GetInputManager()
	{
		if (m_inputManagerList.empty())
			throw ref new Platform::OutOfBoundsException();

		return m_inputManagerList.at(0);
	}

	WOtech::AudioEngine^ SystemManager::GetAudioEngine()
	{
		if (m_audioEngineList.empty())
			throw ref new Platform::OutOfBoundsException();

		return m_audioEngineList.at(0);
	}

	void SystemManager::OnSuspending()
	{
		if (m_enabled)
		{
			for (auto i : m_deviceDX11List)
				i->Trim();
			for (auto j : m_audioEngineList)
				j->SuspendAudio();
			for (auto k : m_audioEngineList)
				k->SuspendAudio();
			for (auto l : m_inputManagerList)
				l->SuspendInput();
		}	
	}
	void SystemManager::OnResume()
	{
		if (m_enabled)
		{
			for (auto i : m_audioEngineList)
				i->ResumeAudio();
			for (auto j : m_inputManagerList)
				j->ResumeInput();
		}	
	}
	void SystemManager::OnWindowSizeChanged(_In_ Windows::Foundation::Size windowSize)
	{
		if (m_enabled)
		{
			for (auto i : m_spriteBatchList)
				i->ReleaseRendertarget();

			for (auto j : m_deviceDX11List)
			{
				j->setLogicalSize(windowSize);
			}

			for (auto k : m_spriteBatchList)
			{
				k->Initialize();
			}
		}	
	}
	void SystemManager::OnDpiChanged(_In_ float32 dpi)
	{
		if (m_enabled)
		{
			for (auto i : m_spriteBatchList)
				i->ReleaseRendertarget();

			for (auto j : m_deviceDX11List)
			{
				j->setDpi(dpi);
			}
			for (auto k : m_spriteBatchList)
			{
				k->Initialize();
			}
		}	
	}
	void SystemManager::OnOrientationChanged(_In_ Windows::Graphics::Display::DisplayOrientations currentOrientation)
	{
		if (m_enabled)
		{
			for (auto i : m_spriteBatchList)
				i->ReleaseRendertarget();

			for (auto j : m_deviceDX11List)
			{
				j->setCurrentOrientation(currentOrientation);
			}

			for (auto k : m_spriteBatchList)
			{
				k->Initialize();
			}
		}
	}
	void SystemManager::OnDisplayContentsInvalidated()
	{
		if (m_enabled)
		{
			for (auto i : m_spriteBatchList)
				i->ReleaseRendertarget();

			for (auto j : m_deviceDX11List)
			{
				j->ValidateDevice();
			}

			for (auto k : m_spriteBatchList)
			{
				k->Initialize();
			}
		}
	}
	void SystemManager::StereoEnabledChanged(_In_ Platform::Boolean stereoEnabled)
	{
		if (m_enabled)
		{

		}
	}
}