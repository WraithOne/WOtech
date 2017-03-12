////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Storage.cpp
///
///			Description:
///
///			Created:	09.01.2016
///			Edited:		06.11.2016
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Storage.h"

using namespace Windows::Storage;
using namespace Windows::Foundation;
using namespace Platform;

namespace WOtech
{
	DA_Storage::DA_Storage()
	{
		m_WINRT = ref new Storage_WINRT();

		m_localSettings = Windows::Storage::ApplicationData::Current->LocalSettings;
		m_localFolder = Windows::Storage::ApplicationData::Current->LocalFolder;
		m_roamingSettings = Windows::Storage::ApplicationData::Current->RoamingSettings;
		m_roamingFolder = Windows::Storage::ApplicationData::Current->RoamingFolder;
	}

	void DA_Storage::WriteLocalSetting(_In_ String^ containerName, _In_ String^ settingName, _In_ Object^ setting)
	{
		m_localSettings->CreateContainer(containerName, ApplicationDataCreateDisposition::Always);

		if (m_localSettings->Containers->HasKey(containerName))
		{
			auto values = m_localSettings->Containers->Lookup(containerName)->Values;
			values->Insert(settingName, setting);
		}
	}

	void DA_Storage::WriteLocalData(_In_ String^ fileName)
	{
	}

	void DA_Storage::WriteRoamingSetting(_In_ String^ containerName, _In_ String^ settingName, _In_ Object^ setting)
	{
		m_roamingSettings->CreateContainer(containerName, ApplicationDataCreateDisposition::Always);

		if (m_roamingSettings->Containers->HasKey(containerName))
		{
			auto values = m_roamingSettings->Containers->Lookup(containerName)->Values;
			values->Insert(settingName, setting);
		}
	}

	void DA_Storage::WriteRoamingData(_In_ String^ fileName)
	{
	}

	Platform::Boolean DA_Storage::ReadLocalSetting(_In_ String^ containerName, _In_ String^ settingName, _Out_ Object^ setting)
	{
		Platform::Boolean hasSetting = false;

		if (m_localSettings->Containers->HasKey(containerName))
		{
			if (m_localSettings->Containers->Lookup(containerName)->Values->HasKey(settingName))
			{
				setting = m_localSettings->Containers->Lookup(containerName)->Values->Lookup(settingName);
				hasSetting = true;
			}	
		}
		return hasSetting;
	}

	Platform::Boolean DA_Storage::ReadLocalData(_In_ String^ fileName)
	{
		return false;
	}

	Platform::Boolean DA_Storage::ReadRoamingSetting(_In_ Platform::String^ containerName, _In_  Platform::String^ settingName, _Out_ Platform::Object^ setting)
	{
		Platform::Boolean hasSetting = false;

		if (m_roamingSettings->Containers->HasKey(containerName))
		{
			if (m_roamingSettings->Containers->Lookup(containerName)->Values->HasKey(settingName))
			{
				setting = m_localSettings->Containers->Lookup(containerName)->Values->Lookup(settingName);
				hasSetting = true;
			}
		}
		return hasSetting;
	}

	Platform::Boolean DA_Storage::ReadRoamingData(_In_ String^ fileName)
	{
		return false;
	}

	Platform::Boolean DA_Storage::RoaminghasChanged()
	{
		if (m_WINRT->RoamingChanged)
		{
			m_WINRT->RoamingChanged = false;
			m_roamingSettings = m_WINRT->RoamingSettings;
			m_roamingFolder = m_WINRT->RoamingFolder;

			return true;
		}
		return false;
	}

	Storage_WINRT::Storage_WINRT()
	{
		Windows::Storage::ApplicationData::Current->DataChanged += ref new TypedEventHandler<ApplicationData^, Object^>(this, &Storage_WINRT::DataChangeHandler);
	}

	void Storage_WINRT::DataChangeHandler(_In_ ApplicationData ^ appData, _In_ Object ^ o)
	{
		m_roamingSettings = appData->Current->RoamingSettings;
		m_roamingFolder = appData->Current->RoamingFolder;

		m_roamingChanged = true;
	}
}