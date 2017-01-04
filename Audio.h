////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: Audio.h
///
///			Created:	01.05.2014
///			Edited:		22.11.2016
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
#include "MediaReader.h"

/////////////
// LINKING //
/////////////
#pragma comment(lib,"xaudio2.lib")

namespace WOtech
{
	public enum class AUDIO_TYPE
	{
		Effect,	// Use for Sounds
		Music	// Use for Music
	};

	public enum class AUDIO_PLAYBACK_STATE
	{
		Stopped,
		Playing,
		Paused
	};

	public value struct VOICE_STATE
	{
		Platform::IntPtr pCurrentBufferContext;// Pointer to current Buffer, NULL if none
		UINT32 BuffersQueued;// Total Buffer�s qued
		UINT64 SamplesPlayed;// Sample�s play since last start, incl loops
	};

	public value struct AUDIOSOURCE_STATE
	{
		AUDIO_PLAYBACK_STATE PlaybackState;// current PlaybackState
		VOICE_STATE VoiceState;// Current VoiceState
	};

	public value struct DEVICE_DETAILS
	{
		Platform::String^ DeviceID;// Device ID
		Platform::String^ DisplayName;// Device Name
	};

	
	public ref class AudioEngine sealed
	{
	public:
		//! AudioEngine Constructor.
		/*!
		*/
		AudioEngine();
		//! Initialize.
		/*!
		Initializes the AudioEngine with default options
		*/
		void Initialize();	
		//! CreateDeviceIndependentResources.
		/*!
		\param xaProcessor assign AudioEngine to specific CPU, default is XADUIO_DEFAULT_PROCESSOR..
		*/
		void CreateDeviceIndependentResources(_In_ UINT32 xaProcessor);
		//! CreateDevicedependentResources.
		/*!
		\param deviceID assign AudioEngine to a hardware device, default is 0. It can obtained from GetDeviceDetails.
		*/
		void CreateDevicedependentResources(_In_ Platform::String^ deviceID);
		//! SuspendAudio.
		/*!
		Stops playing audio and suspend the device.
		*/
		void SuspendAudio();
		//! ResumeAudio.
		/*!
		Restart�s the engine.
		*/
		void ResumeAudio();
		//! SetMasterVolume.
		/*!
		Sets the volume for Effects and Music Mastervoice
		/param Volume for Effectvoice from 0.0f to 1.0f
		/param Volume for Mastervoice from 0.0f to 1.0f
		*/
		void SetMasterVolume(_In_ float32 effectVolume, _In_ float32 musicVolume);
		//! GetMasterVolume.
		/*!
		Sets the volume for Effects and Music Mastervoice
		/param Volume for Effectvoice from 0.0f to 1.0f
		/param Volume for Mastervoice from 0.0f to 1.0f
		*/
		void GetMasterVolome(_Out_ float32 effectVolume, _Out_ float32 musicVolume);	

	internal:
		//! GetEffectEngine.
		/*!
		Returns the EffectEngine
		*/
		IXAudio2* GetEffectEngine();
		//! GetMusicEngine.
		/*!
		Returns the MusicEngine
		*/
		IXAudio2* GetMusicEngine();
		//! GetDeviceCount.
		/*!
		Gets the amount of physical audio devices
		/param The DirectX Audio device
		/param Amount of physical devices
		*/
		void GetDeviceCount(_In_ IXAudio2* device, _Out_ uint32* devCount);
		//! GetDeviceDetails.
		/*!
		Sets the volume for Effects and Music Mastervoice
		/param The DirectX Audio device
		/param number of the device
		/param Details of the physical device
		*/
		void GetDeviceDetails(_In_ IXAudio2* device, _In_  uint32 index, _Out_ DEVICE_DETAILS details);
	private:
		//! AudioEngine Deconstructor.
		/*!
		*/
		~AudioEngine();
	private:
		Platform::Boolean m_audioAvailable;

		Microsoft::WRL::ComPtr<IXAudio2> m_effectdevice;
		IXAudio2MasteringVoice*	m_effectMasterVoice;

		Microsoft::WRL::ComPtr<IXAudio2> m_musicdevice;
		IXAudio2MasteringVoice*	m_musicMasterVoice;
	}; //ref class AudioEngine

	public ref class AudioSource sealed
	{
	public:
		//! Constructor.
		/*!
		\param filename path and filename, eg.: Data\\SFX\\Soundfile.WAV.
		\param audioEngine to Load/Play/Control the sound.
		\param audioType Music or Effect.
		*/
		AudioSource(_In_ Platform::String^ filename, _In_ WOtech::AudioEngine^ audioEngine, _In_ WOtech::AUDIO_TYPE audioType);

		//! LoadWave.
		/*!
		Loads the Wavefile
		*/
		void LoadWave();
		//! Play.
		/*!
		Play�s the AudioSource
		*/
		void Play();
		//! Pause.
		/*!
		Pause�s the running AudioSource
		*/
		void Pause();
		//! Resume.
		/*!
		Resume�s the paused AudioSource
		*/
		void Resume();
		//! Stop.
		/*!
		Stop�s the AudioSource
		*/
		void Stop();
		//! setVolume.
		/*!
		\param Volume for the AudioSource , 0.0f - 1.0f
		*/
		void setVolume(_In_ float32 volume);
		//! getVolume.
		/*!
		\param Get�s the AudioSource volume
		*/
		void getVolume(_Out_ float32 volume);
		//! getPlaybackState.
		/*!
		\param Gets the AudioSource playback state
		*/
		void getPlaybackState(_Out_ AUDIO_PLAYBACK_STATE playbackstate);

		//! getState.
		/*!
		\param Gets the AudioSource state
		*/
		void getState(_Out_ AUDIOSOURCE_STATE state);

	private:
		//! Deconstructor.
		/*!
		*/
		~AudioSource();
		//! VoiceCallback
		/*!
		*/
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
		}; // class VoiceCallback

	private:
		Platform::String^									m_fileName;
		WOtech::AudioEngine^								m_audioEngine;
		WOtech::AUDIO_TYPE									m_audioType;

		Platform::Boolean									m_audioAvailable;
		AUDIO_PLAYBACK_STATE								m_playbackState;

		VoiceCallback										m_voiceCallback;
		IXAudio2SourceVoice*								m_sourceVoice;
		Platform::Array<byte>^								m_soundData;
		}; // ref class AudioSource
}//namespace WOtech
#endif