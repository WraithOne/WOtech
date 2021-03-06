////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: AudioComponents.h
///
///			Description:
///			Header file for Audio Components
///
///			Created:	06.10.2017
///			Edited:		23.09.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_AUDIOCOMPONENTS_H
#define WO_AUDIOCOMPONENTS_H

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////

//////////////
// INCLUDES //
//////////////

/////////////
// LINKING //
/////////////

namespace WOtech
{
	public enum class AUDIO_PROCESSOR
	{
		PROCESSOR1,
		PROCESSOR2,
		PROCESSOR3,
		PROCESSOR4,
		PROCESSOR5,
		PROCESSOR6,
		PROCESSOR7,
		PROCESSOR8,
		PROCESSOR9,
		PROCESSOR10,
		PROCESSOR11,
		PROCESSOR12,
		PROCESSOR13,
		PROCESSOR14,
		PROCESSOR15,
		PROCESSOR16,
		PROCESSOR17,
		PROCESSOR18,
		PROCESSOR19,
		PROCESSOR20,
		PROCESSOR21,
		PROCESSOR22,
		PROCESSOR23,
		PROCESSOR24,
		PROCESSOR25,
		PROCESSOR26,
		PROCESSOR27,
		PROCESSOR28,
		PROCESSOR29,
		PROCESSOR30,
		PROCESSOR31,
		PROCESSOR32,
		ANY_PROCESSOR,
		DEFAULT_PROCESSOR,
	};

	public enum class AUDIO_TYPE
	{
		EFFECT,
		MUSIC
	};

	public enum class AUDIO_PLAYBACK_STATE
	{
		STOPPED,
		PLAYING,
		PAUSED
	};

	public ref class BufferContext sealed
	{
	public:
		BufferContext();

		void setBufferContext(_In_ Platform::IntPtr pCurrentBufferContext);

		void getBufferContext(_Out_ Platform::IntPtr pCurrentBufferContext);
	private:
		void* m_pCurrentBufferContext = nullptr;
	};

	public ref class VoiceState sealed
	{
	public:
		VoiceState()
		{
			pCurrentBufferContext = ref new BufferContext;
		}
		property UINT32 BuffersQueued;
		property UINT64 SamplesPlayed;

	internal:
		BufferContext^ pCurrentBufferContext;
	};

	public ref class AudioSourceState sealed
	{
	public:
		AudioSourceState()
		{
			VoiceState = ref new WOtech::VoiceState;
		}
		property AUDIO_PLAYBACK_STATE PlaybackState;

	internal:
		VoiceState^ VoiceState;
	};

	public value struct DeviceDetails
	{
		Platform::String^ DeviceID;
		Platform::String^ DisplayName;
		Platform::Boolean isDefault;
		Platform::Boolean isEnabled;
	};
}
#endif