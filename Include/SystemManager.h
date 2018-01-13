////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: SystemManager.h
///
///			Description:
///
///			Created:	18.03.2015
///			Edited:		13.01.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_SYSTEMMANAGER_H
#define WO_SYSTEMMANAGER_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"

/////////////
// Defines //
/////////////

namespace WOtech
{
	/////////////////////////////////////////////////////////////////////////
	// Forward declarations
	ref class DeviceDX11;
	ref class SpriteBatch;
	ref class AudioEngine;
	ref class InputManager;

	public ref class SystemManager sealed
	{
	private:
		SystemManager();
		~SystemManager();

	internal:
		// ADD
		void AddDeviceDX11(_In_ WOtech::DeviceDX11^ devicedx11);
		void AddSpriteBatch(_In_ WOtech::SpriteBatch^ spritebatch);
		void AddAudioEngine(_In_ WOtech::AudioEngine^ audioEngine);
		void AddInputManager(_In_ WOtech::InputManager^ inputManager);

		// REMOVE
		void RemoveDeviceDX11(_In_ WOtech::DeviceDX11^ devicedx11);
		void RemoveSpriteBatch(_In_ WOtech::SpriteBatch^ spritebatch);
		void RemoveAudioEngine(_In_ WOtech::AudioEngine^ audioEngine);
		void RemoveInputManager(_In_ WOtech::InputManager^ inputManager);

	public:
		property Platform::Boolean Enable
		{
			Platform::Boolean get() { return m_enabled; };
			void set(_In_ Platform::Boolean enable) { m_enabled = enable; }
		}

		void OnSuspending();
		void OnResume();
		void OnWindowSizeChanged(_In_ Windows::Foundation::Size windowSize);
		void OnDpiChanged(_In_ float32 dpi);
		void OnOrientationChanged(_In_ Windows::Graphics::Display::DisplayOrientations currentOrientation);
		void OnDisplayContentsInvalidated();
		void StereoEnabledChanged(_In_ Platform::Boolean stereoEnabled);

		static property SystemManager^ Instance
		{
			SystemManager^ get()
			{
				static SystemManager^ instance = ref new SystemManager();
				return instance;
			}
		}

	private:
		Platform::Boolean						m_enabled;

		std::vector<WOtech::DeviceDX11^>		m_deviceDX11List;
		std::vector<WOtech::SpriteBatch^>		m_spriteBatchList;
		std::vector<WOtech::AudioEngine^>		m_audioEngineList;
		std::vector<WOtech::InputManager^>		m_inputManagerList;
	};
}
#endif
