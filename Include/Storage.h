////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Storage.h
///
///			Description:
///
///			Created:	09.01.2016
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_STORAGE_H
#define WO_STORAGE_H

//////////////
// INCLUDES //
//////////////
#include <pch.h>

namespace WOtech
{
	ref class RoamingDataHandler sealed
	{
	public:
		RoamingDataHandler();

		void DataChangeHandler(_In_ Windows::Storage::ApplicationData^ appData, _In_ Platform::Object^ o);

		property Windows::Storage::ApplicationDataContainer^ RoamingSettings
		{
			Windows::Storage::ApplicationDataContainer^ get() { return m_roamingSettings; }
		}
		property Windows::Storage::StorageFolder^ RoamingFolder
		{
			Windows::Storage::StorageFolder^ get() { return m_roamingFolder; }
		}
		property Platform::Boolean RoamingChanged
		{
			Platform::Boolean get() { return m_roamingChanged; }
			void set(Platform::Boolean comfirm) { m_roamingChanged = comfirm; }
		}
	private:
		Windows::Storage::ApplicationDataContainer^ m_roamingSettings;
		Windows::Storage::StorageFolder^			m_roamingFolder;

		Platform::Boolean							m_roamingChanged;
	};

	public ref class Storage sealed
	{
	public:
		Storage();

		// Write
		void WriteLocalSetting(_In_ Platform::String^ containerName, _In_ Platform::String^ settingName, _In_ Platform::Object^ setting);
		void WriteRoamingSetting(_In_ Platform::String^ containerName, _In_ Platform::String^ settingName, _In_ Platform::Object^ setting);

		void WriteLocalFile(_In_ Platform::String^ fileName, _In_ Platform::String^ text);
		void WriteLocalFile(_In_ Platform::String^ fileName, _In_ BYTE* buffer);
		void WriteLocalFile(_In_ Platform::String^ fileName, _In_ Windows::Storage::Streams::IBuffer^ buffer);

		void WriteRoamingFile(_In_ Platform::String^ fileName, _In_ Platform::String^ text);
		void WriteRoamingFile(_In_ Platform::String^ fileName, _In_ BYTE* buffer);
		void WriteRoamingFile(_In_ Platform::String^ fileName, _In_ Windows::Storage::Streams::IBuffer^ buffer);

		void WriteTemporaryFile(_In_ Platform::String^ fileName, _In_ Platform::String^ text);
		void WriteTemporaryFile(_In_ Platform::String^ fileName, _In_ BYTE* buffer);
		void WriteTemporaryFile(_In_ Platform::String^ fileName, _In_ Windows::Storage::Streams::IBuffer^ buffer);

		// Read
		Platform::Boolean ReadLocalSetting(_In_ Platform::String^ containerName, _In_ Platform::String^ settingName, _Out_ Platform::Object^ setting);
		Platform::Boolean ReadRoamingSetting(_In_ Platform::String^ containerName, _In_ Platform::String^ settingName, _Out_ Platform::Object^ setting);

		Platform::Boolean ReadLocalFile(_In_ Platform::String^ fileName, _Out_ Platform::String^ text);
		Platform::Boolean ReadLocalFile(_In_ Platform::String^ fileName, _Out_ BYTE* buffer);
		Platform::Boolean ReadLocalFile(_In_ Platform::String^ fileName, _Out_ Windows::Storage::Streams::IBuffer^ buffer);
		
		Platform::Boolean ReadRoamingFile(_In_ Platform::String^ fileName, _Out_ Platform::String^ text);
		Platform::Boolean ReadRoamingFile(_In_ Platform::String^ fileName, _Out_ BYTE* buffer);
		Platform::Boolean ReadRoamingFile(_In_ Platform::String^ fileName, _Out_ Windows::Storage::Streams::IBuffer^ buffer);

		Platform::Boolean ReadTemporaryFile(_In_ Platform::String^ fileName, _Out_ Platform::String^ text);
		Platform::Boolean ReadTemporaryFile(_In_ Platform::String^ fileName, _Out_ BYTE* buffer);
		Platform::Boolean ReadTemporaryFile(_In_ Platform::String^ fileName, _Out_ Windows::Storage::Streams::IBuffer^ buffer);

		Platform::Boolean RoaminghasChanged();

	private:
		RoamingDataHandler^							m_roamingHandler;

		Windows::Storage::ApplicationDataContainer^ m_localSettings;
		Windows::Storage::StorageFolder^			m_localFolder;
		Windows::Storage::ApplicationDataContainer^ m_roamingSettings;
		Windows::Storage::StorageFolder^			m_roamingFolder;

		Windows::Storage::StorageFolder^			m_temporaryFolder;

		Platform::Boolean							m_roamingChanged;
	};
}

#endif