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
///			Edited:		10.05.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Storage.h"
#include <ppltasks.h>

using namespace concurrency;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::Foundation;
using namespace Platform;

namespace WOtech
{
	Storage::Storage()
	{
		m_roamingHandler = ref new RoamingDataHandler();

		m_roamingChanged = false;

		m_localSettings = Windows::Storage::ApplicationData::Current->LocalSettings;
		m_localFolder = Windows::Storage::ApplicationData::Current->LocalFolder;
		m_roamingSettings = Windows::Storage::ApplicationData::Current->RoamingSettings;
		m_roamingFolder = Windows::Storage::ApplicationData::Current->RoamingFolder;
		m_temporaryFolder = Windows::Storage::ApplicationData::Current->TemporaryFolder;
	}

	void Storage::WriteLocalSetting(_In_ String^ containerName, _In_ String^ settingName, _In_ Object^ setting)
	{
		m_localSettings->CreateContainer(containerName, ApplicationDataCreateDisposition::Always);

		if (m_localSettings->Containers->HasKey(containerName))
		{
			auto values = m_localSettings->Containers->Lookup(containerName)->Values;
			values->Insert(settingName, setting);
		}
	}
	void Storage::WriteRoamingSetting(_In_ String^ containerName, _In_ String^ settingName, _In_ Object^ setting)
	{
		m_roamingSettings->CreateContainer(containerName, ApplicationDataCreateDisposition::Always);

		if (m_roamingSettings->Containers->HasKey(containerName))
		{
			auto values = m_roamingSettings->Containers->Lookup(containerName)->Values;
			values->Insert(settingName, setting);
		}
	}

	[Windows::Foundation::Metadata::DefaultOverloadAttribute]
	void Storage::WriteLocalFile(_In_ String^ fileName, _In_ String^ text)
	{
		return;
	}
	void Storage::WriteLocalFile(_In_ String^ fileName, _In_ BYTE* buffer)
	{
		return;
	}
	void Storage::WriteLocalFile(_In_ String^ fileName, _In_ IBuffer^ buffer)
	{
		return;
	}

	[Windows::Foundation::Metadata::DefaultOverloadAttribute]
	void Storage::WriteRoamingFile(_In_ String^ fileName, _In_ String^ text)
	{
		return;
	}
	void Storage::WriteRoamingFile(_In_ String^ fileName, _In_ BYTE* buffer)
	{
		return;
	}
	void Storage::WriteRoamingFile(_In_ String^ fileName, _In_ IBuffer^ buffer)
	{
		return;
	}

	[Windows::Foundation::Metadata::DefaultOverloadAttribute]
	void Storage::WriteTemporaryFile(_In_ String^ fileName, _In_ String^ text)
	{
		return;
	}
	void Storage::WriteTemporaryFile(_In_ String^ fileName, _In_ BYTE* buffer)
	{
		return;
	}
	void Storage::WriteTemporaryFile(_In_ String^ fileName, _In_ IBuffer^ buffer)
	{
		return;
	}

	Platform::Boolean Storage::ReadLocalSetting(_In_ String^ containerName, _In_ String^ settingName, _Out_ Object^ setting)
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
	Platform::Boolean Storage::ReadRoamingSetting(_In_ String^ containerName, _In_  String^ settingName, _Out_ Object^ setting)
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

	[Windows::Foundation::Metadata::DefaultOverloadAttribute]
	Platform::Boolean Storage::ReadLocalFile(_In_ String^ fileName, _Out_ String^ text)
	{
		return false;
	}
	Platform::Boolean Storage::ReadLocalFile(_In_ String^ fileName, _Out_ BYTE* buffer)
	{
		return false;
	}
	Platform::Boolean Storage::ReadLocalFile(_In_ String^ fileName, _Out_ IBuffer^ buffer)
	{
		return false;
	}

	[Windows::Foundation::Metadata::DefaultOverloadAttribute]
	Platform::Boolean Storage::ReadRoamingFile(_In_ String^ fileName, _Out_ String^ text)
	{
		return false;
	}
	Platform::Boolean Storage::ReadRoamingFile(_In_ String^ fileName, _Out_ BYTE* buffer)
	{
		return false;
	}
	Platform::Boolean Storage::ReadRoamingFile(_In_ String^ fileName, _Out_ IBuffer^ buffer)
	{
		return false;
	}

	[Windows::Foundation::Metadata::DefaultOverloadAttribute]
	Platform::Boolean Storage::ReadTemporaryFile(_In_ String^ fileName, _Out_ String^ text)
	{
		return false;
	}
	Platform::Boolean Storage::ReadTemporaryFile(_In_ String^ fileName, _Out_ BYTE* buffer)
	{
		return false;
	}
	Platform::Boolean Storage::ReadTemporaryFile(_In_ String^ fileName, _Out_ IBuffer^ buffer)
	{
		return false;
	}

	Platform::Boolean Storage::RoaminghasChanged()
	{
		if (m_roamingHandler->RoamingChanged)
		{
			m_roamingHandler->RoamingChanged = false;
			m_roamingSettings = m_roamingHandler->RoamingSettings;
			m_roamingFolder = m_roamingHandler->RoamingFolder;

			return true;
		}
		return false;
	}

	RoamingDataHandler::RoamingDataHandler()
	{
		Windows::Storage::ApplicationData::Current->DataChanged += ref new TypedEventHandler<ApplicationData^, Object^>(this, &RoamingDataHandler::DataChangeHandler);
	}

	void RoamingDataHandler::DataChangeHandler(_In_ ApplicationData^ appData, _In_ Object^ o)
	{
		m_roamingSettings = appData->Current->RoamingSettings;
		m_roamingFolder = appData->Current->RoamingFolder;

		m_roamingChanged = true;
	}
}