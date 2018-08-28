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
///			Edited:		28.08.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Audio.h"
#include "MediaReader.h"

namespace WOtech
{
	BufferContext::BufferContext()
	{
		m_pCurrentBufferContext = nullptr;
	}

	void BufferContext::setBufferContext(_In_ Platform::IntPtr pCurrentBufferContext)
	{
		m_pCurrentBufferContext = (void*)pCurrentBufferContext; // todo: safecheck
	}

	void BufferContext::getBufferContext(_Out_ Platform::IntPtr pCurrentBufferContext)
	{
		pCurrentBufferContext = m_pCurrentBufferContext;
	}

	AudioSource::AudioSource(_In_ Platform::String^ fileName, _In_ WOtech::AudioEngine^ audioEngine, _In_ WOtech::AUDIO_TYPE audioType)
	{
		m_fileName = fileName;
		m_audioEngine = audioEngine;
		m_audioType = audioType;

		m_audioAvailable = false;
		m_sourceVoice = nullptr;
		m_playbackState = WOtech::AUDIO_PLAYBACK_STATE::STOPPED;

		// todo: Content Manager
	}

	AudioSource::~AudioSource()
	{
		// Interrupt sound effect if it is currently playing.
		WOtech::ThrowIfFailed(m_sourceVoice->Stop());
		WOtech::ThrowIfFailed(m_sourceVoice->FlushSourceBuffers());

		m_sourceVoice->DestroyVoice();

		m_audioAvailable = false;
		// todo: Content Manager
	}

	void AudioSource::CreateSourceVoice()
	{
		HRESULT hr;

		if (m_audioEngine->GetEffectEngine() == nullptr || m_audioEngine->GetMusicEngine() == nullptr)
		{
			// Audio is not available.
			WOtech::ThrowIfFailed(XAUDIO2_E_INVALID_CALL);
		}

		if (m_audioType == WOtech::AUDIO_TYPE::EFFECT)
		{
			// Create a source voice for this sound effect.
			hr = m_audioEngine->GetEffectEngine()->CreateSourceVoice(&m_sourceVoice, m_sourceFormat, 0, XAUDIO2_DEFAULT_FREQ_RATIO, &m_voiceCallback, NULL, NULL);
			WOtech::ThrowIfFailed(hr);
		}
		else
		{
			// Create a source voice for this music track.
			hr = m_audioEngine->GetMusicEngine()->CreateSourceVoice(&m_sourceVoice, m_sourceFormat, 0, XAUDIO2_DEFAULT_FREQ_RATIO, &m_voiceCallback, NULL, NULL);
			WOtech::ThrowIfFailed(hr);
		}

		m_audioAvailable = true;
	}

	void AudioSource::LoadWave()
	{
		MediaReader^ mediaReader = ref new MediaReader;
		m_soundData = mediaReader->LoadMedia(m_fileName);

		m_sourceFormat = new WAVEFORMATEX;
		m_sourceFormat = mediaReader->GetOutputWaveFormatEx();

		CreateSourceVoice();
	}

	void AudioSource::Play()
	{
		HRESULT hr;

		if ((m_audioAvailable == false) || (m_playbackState == WOtech::AUDIO_PLAYBACK_STATE::PLAYING) || (m_playbackState == WOtech::AUDIO_PLAYBACK_STATE::PAUSED))
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
			WOtech::ThrowIfFailed(hr);
			// Flush all buffers
			hr = m_sourceVoice->FlushSourceBuffers();
			WOtech::ThrowIfFailed(hr);

			// Queue the memory buffer for playback and start the voice.
			buffer.AudioBytes = m_soundData->Length;
			buffer.pAudioData = m_soundData->Data;
			buffer.Flags = 0;

			// Submit Buffer to the Device
			hr = m_sourceVoice->SubmitSourceBuffer(&buffer);
			WOtech::ThrowIfFailed(hr);

			// Start consuming the Buffer
			hr = m_sourceVoice->Start();
			WOtech::ThrowIfFailed(hr);

			m_playbackState = WOtech::AUDIO_PLAYBACK_STATE::PLAYING;
		}
		else
			WOtech::ThrowIfFailed(XAUDIO2_E_INVALID_CALL);
	}

	void AudioSource::Pause()
	{
		if ((m_audioAvailable == false) || (m_playbackState != WOtech::AUDIO_PLAYBACK_STATE::PLAYING))
		{
			// Audio is not available so just return.
			return;
		}
		HRESULT hr;

		// Stop all buffers
		hr = m_sourceVoice->Stop();
		m_playbackState = WOtech::AUDIO_PLAYBACK_STATE::PAUSED;
		WOtech::ThrowIfFailed(hr);
	}

	void AudioSource::Resume()
	{
		if ((m_audioAvailable == false) || (m_playbackState != WOtech::AUDIO_PLAYBACK_STATE::PAUSED))
		{
			// Audio is not available so just return.
			return;
		}

		HRESULT hr;

		hr = m_sourceVoice->Start();
		WOtech::ThrowIfFailed(hr);

		m_playbackState = WOtech::AUDIO_PLAYBACK_STATE::PLAYING;
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
			WOtech::ThrowIfFailed(hr);

		// Flush
		hr = m_sourceVoice->FlushSourceBuffers();
		WOtech::ThrowIfFailed(hr);

		m_playbackState = WOtech::AUDIO_PLAYBACK_STATE::STOPPED;
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

	void AudioSource::getPlaybackState(_Out_ WOtech::AUDIO_PLAYBACK_STATE* playbackState)
	{
		playbackState = &m_playbackState;
	}

	void AudioSource::getState(_Out_ WOtech::AUDIOSOURCE_STATE^ state)
	{
		XAUDIO2_VOICE_STATE temp_state;

		m_sourceVoice->GetState(&temp_state);

		if (m_voiceCallback.finished)
			if (m_playbackState != WOtech::AUDIO_PLAYBACK_STATE::STOPPED)
				m_playbackState = WOtech::AUDIO_PLAYBACK_STATE::STOPPED;

		state->PlaybackState = m_playbackState;
		state->VoiceState->BuffersQueued = temp_state.BuffersQueued;
		state->VoiceState->SamplesPlayed = temp_state.SamplesPlayed;
		state->VoiceState->pCurrentBufferContext->setBufferContext(temp_state.pCurrentBufferContext);
	}
} //namespace WOtech