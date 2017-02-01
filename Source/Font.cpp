////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: Font.cpp
///
///			Created:	31.08.2014
///			Edited:		22.11.2016
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "2DComponents.h"
#include "FontFileLoader.h"
#include "Utilities.h"

using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::ApplicationModel;
using namespace Microsoft::WRL;

namespace WOtech
{
	Font::Font(_In_ Platform::String^ filename)
	{
		m_fileName = filename;

		// todo: Content Manager
	}

	void Font::Load()
	{
		HRESULT hr;
		uint32 key = 150;

		ComPtr<IDWriteFactory> p_Wfactory;

		// Create DWriteFactory
		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &p_Wfactory);
		ThrowIfFailed(hr);

		// Create Path(Filename String
		String^ path;
		String^ pathfilename;
		StorageFolder^ m_installedLocation = Package::Current->InstalledLocation;
		path = Platform::String::Concat(m_installedLocation->Path, "\\");
		pathfilename = Platform::String::Concat(path, m_fileName);

		// Load
		hr = LoadFontFromFile(pathfilename, key, p_Wfactory.Get(), &m_collection);
		ThrowIfFailed(hr);
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
		// todo: Content Manager
	}

	String^ Font::getFontname()
	{
		if (m_collection != NULL)
		{
			ComPtr<IDWriteFontFamily> pFontFamily;
			ComPtr<IDWriteLocalizedStrings> pFamilyNames;

			m_collection->GetFontFamily(0, &pFontFamily);

			pFontFamily->GetFamilyNames(&pFamilyNames);

			uint32 length = 0;
			pFamilyNames->GetStringLength(0, &length);

			wchar_t* name = new wchar_t[length + 1];
			pFamilyNames->GetString(0, name, length + 1);

			std::wstring string = name;
			delete[] name;

			return ref new String(string.c_str());
		}

		return L"Failed";
	}
}//namespace WOtech