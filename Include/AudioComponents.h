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
///			Edited:		01.06.2018
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

		//! setBufferContext.
		/*!
		\param Pointer to a buffer context provided in the XAUDIO2_BUFFER that is processed currently.
		*/
		void setBufferContext(_In_ Platform::IntPtr pCurrentBufferContext);
		//! getBufferContext.
		/*!
		\param Pointer to a buffer context provided in the XAUDIO2_BUFFER that is processed currently, or, if the voice is stopped currently, to the next buffer due to be processed. pCurrentBufferContext is NULL if there are no buffers in the queue.
		*/
		void getBufferContext(_Out_ Platform::IntPtr pCurrentBufferContext);
	private:
		void* m_pCurrentBufferContext = nullptr;
	};

	//!
	/*! Current Voice state. */
	public ref class VOICE_STATE sealed
	{
	public:
		VOICE_STATE()
		{
			pCurrentBufferContext = ref new BufferContext;
		}
		property UINT32 BuffersQueued;	/*!< Total Buffer´s qued.*/
		property UINT64 SamplesPlayed;	/*!< Sample´s play since last start, incl. loops.*/

	internal:
		BufferContext^ pCurrentBufferContext;	/*!< Pointer to current Buffer, NULL if none.*/
	};

	//!
	/*! Current Audiosource state. */
	public ref class AUDIOSOURCE_STATE sealed
	{
	public:
		AUDIOSOURCE_STATE()
		{
			VoiceState = ref new WOtech::VOICE_STATE;
		}
		property AUDIO_PLAYBACK_STATE PlaybackState;	/*!< current PlaybackState.*/

	internal:
		VOICE_STATE^ VoiceState;	/*!< current VoiceState.*/
	};

	//!
	/*! Device details. */
	public value struct DEVICE_DETAILS
	{
		Platform::String^ DeviceID;		/*!< Device ID.*/
		Platform::String^ DisplayName;	/*!< Device name.*/
		Platform::Boolean isDefault;	/*!< Is default Device.*/
		Platform::Boolean isEnabled;	/*!< Is Enabled.*/
	};
}
#endif