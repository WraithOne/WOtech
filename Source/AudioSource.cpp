////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: AudioSource.h
///
///			Description:
///
///			Created:	10.10.2014
///			Edited:		31.03.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Audio.h"

using namespace Platform;

namespace WOtech
{
	AudioSource::AudioSource(_In_ String^ fileName, _In_ AudioEngine^ audioEngine, _In_ AUDIO_TYPE audioType)
	{
		m_fileName = fileName;
		m_audioEngine = audioEngine;
		m_audioType = audioType;

		m_audioAvailable = false;
		m_sourceVoice = nullptr;
		m_playbackState = AUDIO_PLAYBACK_STATE::Stopped;

		// todo: Content Manager
	}

	AudioSource::~AudioSource()
	{
		// Interrupt sound effect if it is currently playing.
		ThrowIfFailed(m_sourceVoice->Stop());
		ThrowIfFailed(m_sourceVoice->FlushSourceBuffers());

		m_sourceVoice->DestroyVoice();

		m_audioAvailable = false;
		// todo: Content Manager
	}

	void AudioSource::LoadWave()
	{
		if (m_audioEngine->GetEffectEngine() == nullptr || m_audioEngine->GetMusicEngine() == nullptr)
		{
			// Audio is not available so just return.
			ThrowIfFailed(XAUDIO2_E_INVALID_CALL);
		}
		HRESULT hr;
		MediaReader^ mediaReader = ref new MediaReader;
		m_soundData = mediaReader->LoadMedia(m_fileName);

		WAVEFORMATEX *sourceFormat = { 0 };
		sourceFormat = mediaReader->GetOutputWaveFormatEx();

		if (m_audioType == AUDIO_TYPE::Effect)
		{
			// Create a source voice for this sound effect.
			hr = m_audioEngine->GetEffectEngine()->CreateSourceVoice(&m_sourceVoice, sourceFormat, 0, XAUDIO2_DEFAULT_FREQ_RATIO, &m_voiceCallback, NULL, NULL);
			ThrowIfFailed(hr);
		}
		else
		{
			// Create a source voice for this music track.
			hr = m_audioEngine->GetMusicEngine()->CreateSourceVoice(&m_sourceVoice, sourceFormat, 0, XAUDIO2_DEFAULT_FREQ_RATIO, &m_voiceCallback, NULL, NULL);
			ThrowIfFailed(hr);
		}

		m_audioAvailable = true;
	}

	void AudioSource::Play()
	{
		HRESULT hr;

		if ((m_audioAvailable == false) || (m_playbackState == AUDIO_PLAYBACK_STATE::Playing) || (m_playbackState == AUDIO_PLAYBACK_STATE::Paused))
		{
			// Audio is not available so just return.
			return;
		}

		XAUDIO2_BUFFER buffer = { 0 };
		XAUDIO2_VOICE_STATE voicestate;
		m_sourceVoice->GetState(&voicestate, NULL);

		if (voicestate.BuffersQueued <= 1)
		{
			// Interrupt sound effect if it is currently playing.
			hr = m_sourceVoice->Stop();
			ThrowIfFailed(hr);
			// Flush all buffers
			hr = m_sourceVoice->FlushSourceBuffers();
			ThrowIfFailed(hr);

			// Queue the memory buffer for playback and start the voice.
			buffer.AudioBytes = m_soundData->Length;
			buffer.pAudioData = m_soundData->Data;
			buffer.Flags = 0;

			// Submit Buffer to the Device
			hr = m_sourceVoice->SubmitSourceBuffer(&buffer);
			ThrowIfFailed(hr);

			// Start consuming the Buffer
			hr = m_sourceVoice->Start();
			ThrowIfFailed(hr);

			m_playbackState = AUDIO_PLAYBACK_STATE::Playing;
		}
		else
			ThrowIfFailed(XAUDIO2_E_INVALID_CALL);
	}

	void AudioSource::Pause()
	{
		if ((m_audioAvailable == false) || (m_playbackState != AUDIO_PLAYBACK_STATE::Playing))
		{
			// Audio is not available so just return.
			return;
		}
		HRESULT hr;

		// Stop all buffers
		hr = m_sourceVoice->Stop();
		m_playbackState = AUDIO_PLAYBACK_STATE::Paused;
		ThrowIfFailed(hr);
	}

	void AudioSource::Resume()
	{
		if ((m_audioAvailable == false) || (m_playbackState != AUDIO_PLAYBACK_STATE::Paused))
		{
			// Audio is not available so just return.
			return;
		}

		HRESULT hr;

		hr = m_sourceVoice->Start();
		ThrowIfFailed(hr);

		m_playbackState = AUDIO_PLAYBACK_STATE::Playing;
	}

	void AudioSource::Stop()
	{
		if (m_audioAvailable == false)
		{
			// Audio is not available so just return.
			return;
		}
		HRESULT hr;

		// Stop all buffers
		hr = m_sourceVoice->Stop();
		if (FAILED(hr))
			ThrowIfFailed(hr);

		// Flush
		hr = m_sourceVoice->FlushSourceBuffers();
		ThrowIfFailed(hr);

		m_playbackState = AUDIO_PLAYBACK_STATE::Stopped;
	}

	void AudioSource::setVolume(_In_ float32 volume)
	{
		HRESULT hr;

		hr = m_sourceVoice->SetVolume(volume);
		ThrowIfFailed(hr);
	}

	void AudioSource::getVolume(_Out_ float32* volume)
	{
		m_sourceVoice->GetVolume(volume);
	}

	void AudioSource::getPlaybackState(_Out_ AUDIO_PLAYBACK_STATE* playbackState)
	{
		playbackState = &m_playbackState;
	}

	void AudioSource::getState(_Out_ AUDIOSOURCE_STATE* state)
	{
		XAUDIO2_VOICE_STATE temp_state;

		m_sourceVoice->GetState(&temp_state);

		if (m_voiceCallback.finished)
			if (m_playbackState != AUDIO_PLAYBACK_STATE::Stopped)
				m_playbackState = AUDIO_PLAYBACK_STATE::Stopped;

		state->PlaybackState = m_playbackState;
		state->VoiceState.BuffersQueued = temp_state.BuffersQueued;
		state->VoiceState.SamplesPlayed = temp_state.SamplesPlayed;
		state->VoiceState.pCurrentBufferContext = DecodePointer(temp_state.pCurrentBufferContext);
	}
} //namespace WOtech