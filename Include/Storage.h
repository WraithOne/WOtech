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
///			Edited:		06.11.2016
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_STORAGE_H
#define WO_STORAGE_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"

namespace WOtech
{
	public ref class Storage_WINRT sealed
	{
	internal:
		Storage_WINRT();

	public:
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

		Platform::Boolean m_roamingChanged;
	};

	public ref class DA_Storage sealed
	{
	internal:
		DA_Storage();

	public:
		// Write
		void WriteLocalSetting(_In_ Platform::String^ containerName, _In_ Platform::String^ settingName, _In_ Platform::Object^ setting);
		void WriteLocalData(_In_ Platform::String^ fileName);

		void WriteRoamingSetting(_In_ Platform::String^ containerName, _In_ Platform::String^ settingName, _In_ Platform::Object^ setting);
		void WriteRoamingData(_In_ Platform::String^ fileName);

		// Read
		Platform::Boolean ReadLocalSetting(_In_ Platform::String^ containerName, _In_ Platform::String^ settingName, _Out_ Platform::Object^ setting);
		Platform::Boolean ReadLocalData(_In_ Platform::String^ fileName);

		Platform::Boolean ReadRoamingSetting(_In_ Platform::String^ containerName, _In_ Platform::String^ settingName, _Out_ Platform::Object^ setting);
		Platform::Boolean ReadRoamingData(_In_ Platform::String^ fileName);

		Platform::Boolean RoaminghasChanged();

	private:
		Storage_WINRT^ m_WINRT;

		Windows::Storage::ApplicationDataContainer^ m_localSettings;
		Windows::Storage::StorageFolder^			m_localFolder;
		Windows::Storage::ApplicationDataContainer^ m_roamingSettings;
		Windows::Storage::StorageFolder^			m_roamingFolder;

		Platform::Boolean m_roamingChanged;
	};
}

#endif