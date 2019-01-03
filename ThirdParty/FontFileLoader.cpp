#include <pch.h>
#include <FontFileLoader.h>

namespace WOtech
{
	HRESULT LoadFontFromFile(Platform::String^ pFilename, uint32 fontId, IDWriteFactory* writeFactory, IDWriteFontCollection** pFontCollection)
	{
		Microsoft::WRL::ComPtr<IDWriteFontCollectionLoader> pFontCollectionLoader(new(std::nothrow) FileFontCollectionLoader(pFilename));

		HRESULT hr = writeFactory->RegisterFontCollectionLoader(pFontCollectionLoader.Get());

		if (SUCCEEDED(hr))
		{
			hr = writeFactory->CreateCustomFontCollection(pFontCollectionLoader.Get(), &fontId, sizeof(fontId), pFontCollection);

			if (FAILED(hr))
			{
				writeFactory->UnregisterFontCollectionLoader(pFontCollectionLoader.Get());
				return hr;
			}
		}

		hr = writeFactory->UnregisterFontCollectionLoader(pFontCollectionLoader.Get());

		return hr;
	}

	HRESULT LoadFontFromFile(Platform::String^ pFilename, Platform::String^ pFontname, uint32 fontId, float32 fontSize, IDWriteFactory* writeFactory, IDWriteTextFormat** pTextFormat)
	{
		Microsoft::WRL::ComPtr<IDWriteFontCollection> pFontCollection;

		HRESULT hr = LoadFontFromFile(pFilename, fontId, writeFactory, &pFontCollection);

		if (SUCCEEDED(hr))
		{
			hr = writeFactory->CreateTextFormat(pFontname->Data(), pFontCollection.Get(), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize, L"en-us", pTextFormat);
		}

		return hr;
	}

	FileFontCollectionLoader::FileFontCollectionLoader(Platform::String^ pFilename) : cRefCount_(0), filename_(pFilename)
	{
	}

	FileFontCollectionLoader::~FileFontCollectionLoader()
	{
	}

	IFACEMETHODIMP_(unsigned long) FileFontCollectionLoader::AddRef()
	{
		return ::InterlockedIncrement(&cRefCount_);
	}

	IFACEMETHODIMP_(unsigned long) FileFontCollectionLoader::Release()
	{
		unsigned long newCount = ::InterlockedDecrement(&cRefCount_);
		if (newCount == 0)
		{
			delete this;
			return 0;
		}

		return newCount;
	}

	IFACEMETHODIMP FileFontCollectionLoader::QueryInterface(IID const& riid, void** ppvObject)
	{
		if ((riid == IID_IUnknown) || (riid == __uuidof(IDWriteFontCollectionLoader)))
		{
			*ppvObject = this;
		}
		else
		{
			*ppvObject = NULL;
			return E_NOINTERFACE;
		}
		this->AddRef();

		return S_OK;
	}

	IFACEMETHODIMP FileFontCollectionLoader::CreateEnumeratorFromKey(IDWriteFactory* factory, void const* collectionKey, uint32 collectionKeySize, __out IDWriteFontFileEnumerator** fontFileEnumerator)
	{
		*fontFileEnumerator = NULL;

		IDWriteFontFileEnumerator* pEnumerator =
			new(std::nothrow) FileFontFileEnumerator(factory, filename_);

		HRESULT hr = ((pEnumerator != NULL) ? S_OK : E_OUTOFMEMORY);

		if (SUCCEEDED(hr))
		{
			pEnumerator->AddRef();
			*fontFileEnumerator = pEnumerator;
		}

		return hr;
	}

	FileFontFileEnumerator::FileFontFileEnumerator(IDWriteFactory* factory, Platform::String^ pFilename) : cRefCount_(0), factory_(factory), filename_(pFilename), isLoaded_(false)
	{
	}

	FileFontFileEnumerator::~FileFontFileEnumerator()
	{
	}

	IFACEMETHODIMP_(unsigned long) FileFontFileEnumerator::AddRef()
	{
		return ::InterlockedIncrement(&cRefCount_);
	}

	IFACEMETHODIMP_(unsigned long) FileFontFileEnumerator::Release()
	{
		unsigned long newCount = ::InterlockedDecrement(&cRefCount_);
		if (newCount == 0)
		{
			delete this;
			return 0;
		}

		return newCount;
	}

	IFACEMETHODIMP FileFontFileEnumerator::QueryInterface(IID const& riid, void** ppvObject)
	{
		if ((riid == IID_IUnknown) || (riid == __uuidof(IDWriteFontFileEnumerator)))
		{
			*ppvObject = this;
			AddRef();
			return S_OK;
		}
		else {
			*ppvObject = NULL;
			return E_NOINTERFACE;
		}
	}

	IFACEMETHODIMP FileFontFileEnumerator::MoveNext(OUT BOOL* hasCurrentFile)
	{
		HRESULT hr = S_OK;

		*hasCurrentFile = FALSE;
		currentFile_.Reset();

		if (!isLoaded_)
		{
			hr = factory_->CreateFontFileReference(filename_->Data(), NULL, &currentFile_);
			if (SUCCEEDED(hr))
			{
				*hasCurrentFile = TRUE;
				isLoaded_ = true;
			}
		}

		return hr;
	}

	IFACEMETHODIMP FileFontFileEnumerator::GetCurrentFontFile(__out IDWriteFontFile** fontFile)
	{
		if (currentFile_.Get() != NULL)
		{
			currentFile_.Get()->AddRef();
		}
		*fontFile = ((currentFile_.Get() != NULL) ? currentFile_.Get() : NULL);

		return (currentFile_.Get() != NULL) ? S_OK : E_FAIL;
	}
}