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
///			Edited:		02.09.2017
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
	//!
	/*! Enumartion of available Audio typs. */
	public enum class AUDIO_TYPE
	{
		Effect,	/*!< Use for Sounds.*/
		Music	/*!< Use for Music.*/
	};

	//!
	/*! Enumartion of the current Playback state. */
	public enum class AUDIO_PLAYBACK_STATE
	{
		Stopped,	/*!< Playback stopped.*/
		Playing,	/*!< Playback.*/
		Paused		/*!< Playback paused.*/
	};

	//!
	/*! Pointer to a buffer context provided in the XAUDIO2_BUFFER that is processed currently. */
	public ref class BufferContext sealed
	{
	public:
		//! Constructor.
		/*!
		*/
		BufferContext();

	internal:
		//! setBufferContext.
		/*!
		\param Pointer to a buffer context provided in the XAUDIO2_BUFFER that is processed currently.
		*/
		void setBufferContext(_In_ void* pCurrentBufferContext);
		//! getBufferContext.
		/*!
		\param Pointer to a buffer context provided in the XAUDIO2_BUFFER that is processed currently, or, if the voice is stopped currently, to the next buffer due to be processed. pCurrentBufferContext is NULL if there are no buffers in the queue.
		*/
		void getBufferContext(_Out_ void* pCurrentBufferContext);
	private:
		void* m_pCurrentBufferContext;
	};

	//!
	/*! Current Voice state. */
	public ref class VOICE_STATE sealed
	{
	public:
		property UINT32 BuffersQueued;	/*!< Total Buffer큦 qued.*/
		property UINT64 SamplesPlayed;	/*!< Sample큦 play since last start, incl. loops.*/

	internal:
		BufferContext pCurrentBufferContext;	/*!< Pointer to current Buffer, NULL if none.*/
	};

	//!
	/*! Current Audiosource state. */
	public ref class AUDIOSOURCE_STATE sealed
	{
	public:
		property AUDIO_PLAYBACK_STATE PlaybackState;	/*!< current PlaybackState.*/

	internal:
		VOICE_STATE VoiceState;	/*!< current VoiceState.*/
	};

	//!
	/*! Device details. */
	public value struct DEVICE_DETAILS
	{
		Platform::String^ DeviceID;		/*!< Device ID.*/
		Platform::String^ DisplayName;	/*!< Device name.*/
	};

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
		void GetDeviceDetails(_In_ IXAudio2* device, _In_  uint32 index, _Out_ DEVICE_DETAILS* details);
	private:
		//! AudioEngine Deconstructor.
		/*!
		*/
		~AudioEngine();
	private:
		Platform::Boolean m_audioAvailable;

		Microsoft::WRL::ComPtr<IXAudio2> m_effectDevice;
		IXAudio2MasteringVoice*	m_effectMasterVoice;

		Microsoft::WRL::ComPtr<IXAudio2> m_musicDevice;
		IXAudio2MasteringVoice*	m_musicMasterVoice;
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
		void getPlaybackState(_Out_ AUDIO_PLAYBACK_STATE* playbackState);

		//! getState.
		/*!
		\param Gets the AudioSource state
		*/
		void getState(_Out_ AUDIOSOURCE_STATE^ state);

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