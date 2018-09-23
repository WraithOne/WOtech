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
///			Header file for AudioEngine and AudioSource
///
///			Created:	01.05.2014
///			Edited:		23.09.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_AUDIO_H
#define WO_AUDIO_H

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Utilities.h"
#include "AudioComponents.h"

/////////////
// LINKING //
/////////////
#pragma comment(lib,"xaudio2.lib")

namespace WOtech
{
	public ref class AudioEngine sealed
	{
	public:
		AudioEngine();

		void Initialize();
		void Initialize(_In_ WOtech::AUDIO_PROCESSOR xaProcessor, _In_ Platform::String^ deviceID);

		void CreateDeviceIndependentResources(_In_ WOtech::AUDIO_PROCESSOR xaProcessor);
		void CreateDevicedependentResources(_In_ Platform::String^ deviceID);

		void SuspendAudio();
		void ResumeAudio();

		void SetMasterVolume(_In_ float32 effectVolume, _In_ float32 musicVolume);
		void GetMasterVolome(_Out_ float32* effectVolume, _Out_ float32* musicVolume);

	internal:
		IXAudio2* GetEffectEngine();
		IXAudio2* GetMusicEngine();

		void GetDeviceCount(_In_ IXAudio2* device, _Out_ uint32* devCount);
		void GetDeviceDetails(_In_ IXAudio2* device, _In_  uint32 index, _Out_ WOtech::DeviceDetails* details);

	private:
		~AudioEngine();

	private:
		Platform::Boolean					m_audioAvailable;

		Microsoft::WRL::ComPtr<IXAudio2>	m_effectDevice;
		IXAudio2MasteringVoice*				m_effectMasterVoice;

		Microsoft::WRL::ComPtr<IXAudio2>	m_musicDevice;
		IXAudio2MasteringVoice*				m_musicMasterVoice;
	};

	public ref class AudioSource sealed
	{
	public:
		AudioSource(_In_ Platform::String^ fileName, _In_ WOtech::AudioEngine^ audioEngine, _In_ WOtech::AUDIO_TYPE audioType);


		void LoadWave();

		void Play();
		void Pause();
		void Resume();
		void Stop();

		void setVolume(_In_ float32 volume);
		void getVolume(_Out_ float32* volume);

		void getPlaybackState(_Out_ WOtech::AUDIO_PLAYBACK_STATE* playbackState);
		void getState(_Out_ WOtech::AudioSourceState^ state);

	private:
		~AudioSource();

		void CreateSourceVoice();

		class VoiceCallback : public IXAudio2VoiceCallback
		{
		public:
			std::atomic<bool> finished;
			VoiceCallback() : finished(false) {}
			~VoiceCallback() {}

			//Called when the voice has just finished playing a contiguous audio stream.
			STDMETHOD_(void, OnStreamEnd)() { finished = true; }

			//Unused methods are stubs
			STDMETHOD_(void, OnVoiceProcessingPassEnd) () { }
			STDMETHOD_(void, OnVoiceProcessingPassStart) (uint32 SamplesRequired) {    }
			STDMETHOD_(void, OnBufferEnd) (void * pBufferContext) { finished = true; }
			STDMETHOD_(void, OnBufferStart) (void * pBufferContext) { finished = false; }
			STDMETHOD_(void, OnLoopEnd) (void * pBufferContext) {    }
			STDMETHOD_(void, OnVoiceError) (void * pBufferContext, HRESULT Error) { ThrowIfFailed(Error); }
		};

	private:
		Platform::String^				m_fileName;
		WOtech::AudioEngine^			m_audioEngine;
		WOtech::AUDIO_TYPE				m_audioType;

		Platform::Boolean				m_audioAvailable;
		WOtech::AUDIO_PLAYBACK_STATE	m_playbackState;

		VoiceCallback					m_voiceCallback;
		WAVEFORMATEX*					m_sourceFormat;
		IXAudio2SourceVoice*			m_sourceVoice;
		Platform::Array<byte>^			m_soundData;
	};
}
#endif