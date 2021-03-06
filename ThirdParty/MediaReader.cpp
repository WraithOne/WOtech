//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

#include <pch.h>
#include <MediaReader.h>
#include <Utilities.h>

MediaReader::MediaReader()
{
	ZeroMemory(&m_waveFormat, sizeof(m_waveFormat));
	m_installedLocation = Windows::ApplicationModel::Package::Current->InstalledLocation;
	m_installedLocationPath = Platform::String::Concat(m_installedLocation->Path, "\\");
}

WAVEFORMATEX *MediaReader::GetOutputWaveFormatEx()
{
	return &m_waveFormat;
}

Platform::Array<byte>^ MediaReader::LoadMedia(_In_ Platform::String^ filename)
{
	WOtech::ThrowIfFailed(MFStartup(MF_VERSION));

	Platform::String^ finalpath = Platform::String::Concat(m_installedLocationPath, filename);

	Microsoft::WRL::ComPtr<IMFSourceReader> reader;
	WOtech::ThrowIfFailed(MFCreateSourceReaderFromURL(finalpath->Data(), nullptr, &reader));

	// Set the decoded output format as PCM.
	// XAudio2 on Windows can process PCM and ADPCM-encoded buffers.
	// When using MediaFoundation, this sample always decodes into PCM.
	Microsoft::WRL::ComPtr<IMFMediaType> mediaType;
	WOtech::ThrowIfFailed(MFCreateMediaType(&mediaType));

	WOtech::ThrowIfFailed(mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio));

	WOtech::ThrowIfFailed(mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM));

	WOtech::ThrowIfFailed(reader->SetCurrentMediaType(static_cast<uint32>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), 0, mediaType.Get()));

	// Get the complete WAVEFORMAT from the Media Type.
	Microsoft::WRL::ComPtr<IMFMediaType> outputMediaType;
	WOtech::ThrowIfFailed(reader->GetCurrentMediaType(static_cast<uint32>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), &outputMediaType));

	uint32 size = 0;
	WAVEFORMATEX* waveFormat;

	WOtech::ThrowIfFailed(MFCreateWaveFormatExFromMFMediaType(outputMediaType.Get(), &waveFormat, &size));

	CopyMemory(&m_waveFormat, waveFormat, sizeof(m_waveFormat));
	CoTaskMemFree(waveFormat);

	PROPVARIANT propVariant;
	WOtech::ThrowIfFailed(reader->GetPresentationAttribute(static_cast<uint32>(MF_SOURCE_READER_MEDIASOURCE), MF_PD_DURATION, &propVariant));
	// 'duration' is in 100ns units; convert to seconds, and round up
	// to the nearest whole byte.
	LONGLONG duration = propVariant.uhVal.QuadPart;
	unsigned int maxStreamLengthInBytes = static_cast<unsigned int>(
		((duration * static_cast<ULONGLONG>(m_waveFormat.nAvgBytesPerSec)) + 10000000) / 10000000);

	Platform::Array<byte>^ fileData = ref new Platform::Array<byte>(maxStreamLengthInBytes);

	Microsoft::WRL::ComPtr<IMFSample> sample;
	Microsoft::WRL::ComPtr<IMFMediaBuffer> mediaBuffer;
	DWORD flags = 0;

	int positionInData = 0;
	Platform::Boolean done = false;
	while (!done)
	{
		WOtech::ThrowIfFailed(reader->ReadSample(static_cast<uint32>(MF_SOURCE_READER_FIRST_AUDIO_STREAM), 0, nullptr, &flags, nullptr, &sample));

		if (sample != nullptr)
		{
			WOtech::ThrowIfFailed(sample->ConvertToContiguousBuffer(&mediaBuffer));

			BYTE *audioData = nullptr;
			DWORD sampleBufferLength = 0;
			WOtech::ThrowIfFailed(mediaBuffer->Lock(&audioData, nullptr, &sampleBufferLength));

			for (DWORD i = 0; i < sampleBufferLength; i++)
			{
				fileData[positionInData++] = audioData[i];
			}
		}
		if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
		{
			done = true;
		}
	}

	return fileData;
}