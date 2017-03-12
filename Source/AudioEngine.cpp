////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Audio.h
///
///			Description:
///
///			Created:	20.09.2014
///			Edited:		11.02.2017
///
////////////////////////////////////////////////////////////////////////////

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Audio.h"
#include "Utilities.h"
#include "SystemManager.h"

using Windows::Devices::Enumeration::DeviceClass;
using Windows::Devices::Enumeration::DeviceInformation;
using Windows::Devices::Enumeration::DeviceInformationCollection;
using namespace Windows::Media;
using namespace Windows::Foundation;

namespace WOtech
{
	AudioEngine::AudioEngine()
	{
		m_audioAvailable = false;
		m_effectMasterVoice = nullptr;
		m_musicMasterVoice = nullptr;

		SystemManager::Instance->AddAudioEngine(this);
	}

	AudioEngine::~AudioEngine()
	{
		if (m_effectMasterVoice != nullptr)
		{
			m_effectMasterVoice->DestroyVoice();
			m_effectDevice = nullptr;
		}

		if (m_musicMasterVoice != nullptr)
		{
			m_musicMasterVoice->DestroyVoice();
			m_musicDevice = nullptr;
		}

		m_audioAvailable = false;
		SystemManager::Instance->RemoveAudioEngine(this);
	}

	void AudioEngine::Initialize()
	{
		//default Processor
		XAUDIO2_PROCESSOR xaProcessor = XAUDIO2_DEFAULT_PROCESSOR;
		CreateDeviceIndependentResources(xaProcessor);


		// Default Device
		Platform::String^ deviceID = "0";

		CreateDevicedependentResources(deviceID);

	}

	void AudioEngine::CreateDeviceIndependentResources(_In_ UINT32 xaProcessor)
	{
		HRESULT hr;
		uint32 Flags = NULL;

		// Create the effect engine
		hr = XAudio2Create(&m_effectDevice, Flags, xaProcessor);
		ThrowIfFailed(hr);

		// Create the music engine
		hr = XAudio2Create(&m_musicDevice, Flags, xaProcessor);
		ThrowIfFailed(hr);

#if defined(_DEBUG)
		// Set the device�s to debug
		XAUDIO2_DEBUG_CONFIGURATION debugConfiguration = { 0 };
		debugConfiguration.BreakMask = XAUDIO2_LOG_ERRORS;
		debugConfiguration.TraceMask = XAUDIO2_LOG_ERRORS;
		m_effectDevice->SetDebugConfiguration(&debugConfiguration);
		m_musicDevice->SetDebugConfiguration(&debugConfiguration);
#endif
	}

	void AudioEngine::CreateDevicedependentResources(_In_ Platform::String^ deviceID)
	{
		HRESULT hr;
		uint32 flags = 0;

		// Check if devices are valid
		if (m_effectDevice == nullptr || m_musicDevice == nullptr)
			ThrowIfFailed(XAUDIO2_E_DEVICE_INVALIDATED);


		// Create Effectvoice
		hr = m_effectDevice->CreateMasteringVoice(&m_effectMasterVoice,
												XAUDIO2_DEFAULT_CHANNELS,
												XAUDIO2_DEFAULT_SAMPLERATE,
												flags,
												LPCWSTR(0),  // todo: get the real device ID
												NULL,
												_AUDIO_STREAM_CATEGORY::AudioCategory_GameEffects);
		ThrowIfFailed(hr);

		// Create Musicvoice
		hr = m_musicDevice->CreateMasteringVoice(&m_musicMasterVoice,
												XAUDIO2_DEFAULT_CHANNELS,
												XAUDIO2_DEFAULT_SAMPLERATE,
												flags,
												LPCWSTR(0),  // todo: get the real device ID
												NULL,
												_AUDIO_STREAM_CATEGORY::AudioCategory_GameMedia);
		ThrowIfFailed(hr);

		m_audioAvailable = true;
	}

	void AudioEngine::SuspendAudio()
	{
		if (m_audioAvailable)
		{
			m_effectDevice->StopEngine();
			m_musicDevice->StopEngine();
		}
	}

	void AudioEngine::ResumeAudio()
	{
		HRESULT hr;

		if (m_audioAvailable)
		{
			// resume Effect engine
			hr = m_effectDevice->StartEngine();
			ThrowIfFailed(hr);
			// Resume music engine
			hr = m_musicDevice->StartEngine();
			ThrowIfFailed(hr);
		}
		else
		{
			ThrowIfFailed(E_ABORT); // todo: hmmm
		}
	}

	void AudioEngine::SetMasterVolume(_In_ float32 effectVolume, _In_ float32 musicVolume)
	{
		HRESULT hr = E_INVALIDARG;// TODO: Error for uninit device

		if (m_effectMasterVoice)
		{
			hr = m_effectMasterVoice->SetVolume(effectVolume, NULL);
			ThrowIfFailed(hr);
		}

		if (m_musicMasterVoice)
		{
			hr = m_musicMasterVoice->SetVolume(musicVolume, NULL);
			ThrowIfFailed(hr);
		}

		ThrowIfFailed(hr);
	}

	IXAudio2* AudioEngine::GetEffectEngine()
	{
		return m_effectDevice.Get();
	}

	IXAudio2* AudioEngine::GetMusicEngine()
	{
		return m_musicDevice.Get();
	}

	void AudioEngine::GetMasterVolome(_Out_ float32 effectVolume, _Out_ float32 musicVolume)
	{
		float32 failed = 0.0f;

		if (m_effectMasterVoice)
			m_effectMasterVoice->GetVolume(&effectVolume);
		else
			effectVolume = failed;

		if (m_musicMasterVoice)
			m_musicMasterVoice->GetVolume(&musicVolume);
		else
			musicVolume = failed;
	}

	void AudioEngine::GetDeviceCount(_In_ IXAudio2* device, _Out_ uint32* devCount)
	{
		UNREFERENCED_PARAMETER(device);

#if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
		// There doesn't seem to be any audio device enumeration on Windows Phone.
		// In lieu of this, just treat things as if there is one and only one
		// audio device.
		*devcount = 1;
#else
		// TODO, WinRT: make xaudio2 device enumeration only happen once, and in the background
		auto operation = DeviceInformation::FindAllAsync(DeviceClass::AudioRender);
		while (operation->Status != Windows::Foundation::AsyncStatus::Completed)
		{
		}

		DeviceInformationCollection^ devices = operation->GetResults();
		*devCount = devices->Size;
#endif
	}

	void AudioEngine::GetDeviceDetails(_In_ IXAudio2* device, _In_  uint32 index, _Out_ DEVICE_DETAILS details)
	{
		UNREFERENCED_PARAMETER(device);

#if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
		// Windows Phone doesn't seem to have the same device enumeration APIs that
		// Windows 8/RT has, or it doesn't have them at all.  In lieu of this,
		// just treat things as if there is one, and only one, default device.
		if (index != 0)
		{
			return XAUDIO2_E_INVALID_CALL;
		}

		if (details)
		{
			wcsncpy_s(details->DeviceID, ARRAYSIZE(details->DeviceID), L"default", _TRUNCATE);
			wcsncpy_s(details->DisplayName, ARRAYSIZE(details->DisplayName), L"default", _TRUNCATE);
		}
		return S_OK;
#else
		auto operation = DeviceInformation::FindAllAsync(DeviceClass::AudioRender);
		while (operation->Status != Windows::Foundation::AsyncStatus::Completed)
		{
		}

		DeviceInformationCollection^ devices = operation->GetResults();
		if (index >= devices->Size)
		{
			ThrowIfFailed(XAUDIO2_E_INVALID_CALL);
		}

		DeviceInformation^ d = devices->GetAt(index);
		details.DeviceID = d->Id;
		details.DisplayName = d->Name;

#endif
	}
}//namespace WOtech