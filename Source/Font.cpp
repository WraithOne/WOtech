////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Font.cpp
///
///			Description:
///
///			Created:	31.08.2014
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "2DComponents.h"
#include "FontFileLoader.h"
#include "Utilities.h"
#include "ContentManager.h"

namespace WOtech
{
	Font::Font(_In_ Platform::String^ filename)
	{
		m_fileName = filename;

		WOtech::ContentManager::Instance->AddFont(this);
	}

	void Font::Load()
	{
		HRESULT hr;
		uint32 key = 150;

		Microsoft::WRL::ComPtr<IDWriteFactory> p_Wfactory;

		// Create DWriteFactory
		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &p_Wfactory);
		ThrowIfFailed(hr);
		
		// Create Path(Filename String
		Platform::String^ path;
		Platform::String^ pathfilename;
		Windows::Storage::StorageFolder^ m_installedLocation = Windows::ApplicationModel::Package::Current->InstalledLocation;
		path = Platform::String::Concat(m_installedLocation->Path, "\\");
		pathfilename = Platform::String::Concat(path, m_fileName);

		// Load
		hr = LoadFontFromFile(pathfilename, key, p_Wfactory.Get(), &m_collection);
		ThrowIfFailed(hr);
	}

	void Font::UnLoad()
	{
		m_collection.Reset();
	}

	IDWriteFontCollection*	Font::getColletion()
	{
		return m_collection.Get();
	}
	IDWriteFontCollection** Font::getCollectionL()
	{
		return m_collection.GetAddressOf();
	}

	Font::~Font()
	{
		WOtech::ContentManager::Instance->RemoveFont(this);
	}

	Platform::String^ Font::getFontname()
	{
		if (m_collection != NULL)
		{
			Microsoft::WRL::ComPtr<IDWriteFontFamily> pFontFamily;
			Microsoft::WRL::ComPtr<IDWriteLocalizedStrings> pFamilyNames;

			m_collection->GetFontFamily(0, &pFontFamily);

			pFontFamily->GetFamilyNames(&pFamilyNames);

			uint32 length = 0;
			pFamilyNames->GetStringLength(0, &length);

			wchar_t* name = new wchar_t[length + 1];
			pFamilyNames->GetString(0, name, length + 1);

			std::wstring string = name;
			delete[] name;

			return ref new Platform::String(string.c_str());
		}

		return L"Failed";
	}
}//namespace WOtech