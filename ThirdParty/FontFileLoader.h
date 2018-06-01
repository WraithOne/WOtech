#ifndef WO_FONTFILELOADER_H
#define WO_FONTFILELOADER_H

#include <dwrite.h>

namespace WOtech
{
	HRESULT LoadFontFromFile(Platform::String^ pFilename, uint32 fontId, IDWriteFactory* writeFactory, IDWriteFontCollection** pFontCollection);

	HRESULT LoadFontFromFile(Platform::String^ pFilename, Platform::String^ pFontname, uint32 fontId, float32 fontSize, IDWriteFactory* writeFactory, IDWriteTextFormat** pTextFormat);

	class FileFontCollectionLoader : public IDWriteFontCollectionLoader
	{
	public:
		FileFontCollectionLoader(Platform::String^ pFilename);

		virtual ~FileFontCollectionLoader();

		IFACEMETHOD_(unsigned long, AddRef) ();

		IFACEMETHOD_(unsigned long, Release) ();

		IFACEMETHOD(QueryInterface) (IID const& riid, void** ppvObject);

		IFACEMETHOD(CreateEnumeratorFromKey)(IDWriteFactory* factory, void const* collectionKey, uint32 collectionKeySize, __out IDWriteFontFileEnumerator** fontFileEnumerator);

	private:
		LONG cRefCount_;
		Platform::String^ filename_;
	};

	class FileFontFileEnumerator : public IDWriteFontFileEnumerator
	{
	public:
		FileFontFileEnumerator(IDWriteFactory* factory, Platform::String^ pFilename);

		virtual ~FileFontFileEnumerator();

		IFACEMETHOD_(unsigned long, AddRef) ();

		IFACEMETHOD_(unsigned long, Release) ();

		IFACEMETHOD(QueryInterface) (IID const& riid, void** ppvObject);

		IFACEMETHOD(MoveNext) (OUT BOOL* hasCurrentFile);

		IFACEMETHOD(GetCurrentFontFile) (__out IDWriteFontFile** fontFile);

	private:
		LONG cRefCount_;
		Microsoft::WRL::ComPtr<IDWriteFactory> factory_;
		Microsoft::WRL::ComPtr<IDWriteFontFile> currentFile_;
		Platform::String^ filename_;
		Platform::Boolean isLoaded_;
	};
}
#endif
