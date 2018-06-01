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
///			Edited:		01.06.2018
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
	//! AudioEngine
	/*! Manages all audio engine states, the audio processing thread, the voice graph, and so forth.  */
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
		//! Initialize.
		/*!
		Initializes the AudioEngine.
		\param xaProcessor assign AudioEngine to specific CPU, default is XADUIO_DEFAULT_PROCESSOR.
		\param deviceID assign AudioEngine to a hardware device, default is 0. It can obtained from GetDeviceDetails.
		*/
		void Initialize(_In_ WOtech::AUDIO_PROCESSOR xaProcessor, _In_ Platform::String^ deviceID);
		//! CreateDeviceIndependentResources.
		/*!
		\param xaProcessor assign AudioEngine to specific CPU, default is XADUIO_DEFAULT_PROCESSOR.
		*/
		void CreateDeviceIndependentResources(_In_ WOtech::AUDIO_PROCESSOR xaProcessor);
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
		Restart큦 the engine.
		*/
		void ResumeAudio();
		//! SetMasterVolume.
		/*!
		Sets the volume for Effects and Music Mastervoice
		\param Volume for Effectvoice from 0.0f to 1.0f
		\param Volume for Mastervoice from 0.0f to 1.0f
		*/
		void SetMasterVolume(_In_ float32 effectVolume, _In_ float32 musicVolume);
		//! GetMasterVolume.
		/*!
		Sets the volume for Effects and Music Mastervoice
		\param Volume for Effectvoice from 0.0f to 1.0f
		\param Volume for Mastervoice from 0.0f to 1.0f
		*/
		void GetMasterVolome(_Out_ float32* effectVolume, _Out_ float32* musicVolume);

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
		\param The DirectX Audio device
		\param Amount of physical devices
		*/
		void GetDeviceCount(_In_ IXAudio2* device, _Out_ uint32* devCount);
		//! GetDeviceDetails.
		/*!
		Sets the volume for Effects and Music Mastervoice
		\param The DirectX Audio device
		\param number of the device
		\param Details of the physical device
		*/
		void GetDeviceDetails(_In_ IXAudio2* device, _In_  uint32 index, _Out_ WOtech::DEVICE_DETAILS* details);
	private:
		//! AudioEngine Deconstructor.
		/*!
		*/
		~AudioEngine();
	private:
		Platform::Boolean					m_audioAvailable;

		Microsoft::WRL::ComPtr<IXAudio2>	m_effectDevice;
		IXAudio2MasteringVoice*				m_effectMasterVoice;

		Microsoft::WRL::ComPtr<IXAudio2>	m_musicDevice;
		IXAudio2MasteringVoice*				m_musicMasterVoice;
	}; //ref class AudioEngine

	   //! AudioSource
	   /*! Use a source voice to submit audio data to the AudioEngine processing pipeline.You must send voice data to a mastering voice to be heard, either directly or through intermediate submix voices.   */
	public ref class AudioSource sealed
	{
	public:
		//! Constructor.
		/*!
		\param filename path and filename, eg.: Data\\SFX\\Soundfile.WAV.
		\param audioEngine to Load/Play/Control the sound.
		\param audioType Music or Effect.
		*/
		AudioSource(_In_ Platform::String^ fileName, _In_ WOtech::AudioEngine^ audioEngine, _In_ WOtech::AUDIO_TYPE audioType);

		//! LoadWave.
		/*!
		Loads the Wavefile
		*/
		void LoadWave();
		//! Play.
		/*!
		Play큦 the AudioSource
		*/
		void Play();
		//! Pause.
		/*!
		Pause큦 the running AudioSource
		*/
		void Pause();
		//! Resume.
		/*!
		Resume큦 the paused AudioSource
		*/
		void Resume();
		//! Stop.
		/*!
		Stop큦 the AudioSource
		*/
		void Stop();
		//! setVolume.
		/*!
		\param Volume for the AudioSource , 0.0f - 1.0f
		*/
		void setVolume(_In_ float32 volume);
		//! getVolume.
		/*!
		\param Get큦 the AudioSource volume
		*/
		void getVolume(_Out_ float32* volume);
		//! getPlaybackState.
		/*!
		\param Gets the AudioSource playback state
		*/
		void getPlaybackState(_Out_ WOtech::AUDIO_PLAYBACK_STATE* playbackState);

		//! getState.
		/*!
		\param Gets the AudioSource state
		*/
		void getState(_Out_ WOtech::AUDIOSOURCE_STATE^ state);

	private:
		//! Deconstructor.
		/*!
		*/
		~AudioSource();
		//! CreateSourceVoice
		/*!
		*/
		void CreateSourceVoice();
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
		Platform::String^				m_fileName;
		WOtech::AudioEngine^			m_audioEngine;
		WOtech::AUDIO_TYPE				m_audioType;

		Platform::Boolean				m_audioAvailable;
		WOtech::AUDIO_PLAYBACK_STATE	m_playbackState;

		VoiceCallback					m_voiceCallback;
		WAVEFORMATEX*					m_sourceFormat;
		IXAudio2SourceVoice*			m_sourceVoice;
		Platform::Array<byte>^			m_soundData;
	}; // ref class AudioSource
}//namespace WOtech
#endif