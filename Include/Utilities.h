////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Utilities.h
///
///			Description:
///
///			Created:	12.05.2014
///			Edited:		06.04.2016
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_UTILITIES_H
#define WO_UTILITIES_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"

/////////////
// Defines //
/////////////
#define DA_PI 3.141592241f

namespace WOtech
{
	// Releases a COM object and nullifies pointer.
	template <typename InterfaceType>
	inline void SafeRelease(InterfaceType** currentObject)
	{
		if (*currentObject != NULL)
		{
			(*currentObject)->Release();
			*currentObject = NULL;
		}
	}

	// Acquires an additional reference, if non-null.
	template <typename InterfaceType>
	inline InterfaceType* SafeAcquire(InterfaceType* newObject)
	{
		if (newObject != NULL)
			newObject->AddRef();

		return newObject;
	}

	// Sets a new COM object, releasing the old one.
	template <typename InterfaceType>
	inline void SafeSet(InterfaceType** currentObject, InterfaceType* newObject)
	{
		SafeAcquire(newObject);
		SafeRelease(&currentObject);
		currentObject = newObject;
	}

	// Maps exceptions to equivalent HRESULTs,
	inline HRESULT ExceptionToHResult() throw()
	{
		try
		{
			throw;  // Rethrow previous exception.
		}
		catch (std::bad_alloc&)
		{
			return E_OUTOFMEMORY;
		}
		catch (...)
		{
			return E_FAIL;
		}
	}

	// Convert DirectX error codes to exceptions.
	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			// Set a breakpoint on this line to catch DX API errors.
			throw Platform::Exception::CreateException(hr);
		}
	}

	// Converts a length in device-independent pixels (DIPs) to a length in physical pixels.
	inline float32 ConvertDipsToPixels(_In_ float32 dips, _In_ float32 dpi)
	{
		static const float32 dipsPerInch = 96.0f;
		return floorf(dips * dpi / dipsPerInch + 0.5f); // Round to nearest integer.
	}

	// Converts Radian to Degree
	inline float32 RadiantoDegree(_In_ float32 radian)
	{
		float32 degree;

		degree = radian*(100 / DA_PI);

		return degree;
	}
	// Converts Degree to Radians
	inline float32 DegreetoRadian(float32 degree)
	{
		float32 radian;

		radian = degree*(DA_PI / 180);

		return radian;
	}

#if defined(_DEBUG)
	// Check for SDK Layer support.
	inline Platform::Boolean SDKLayersAvailable()
	{
		HRESULT hr = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_NULL,       // There is no need to create a real hardware device.
			0,
			D3D11_CREATE_DEVICE_DEBUG,  // Check for the SDK layers.
			nullptr,                    // Any feature level will do.
			0,
			D3D11_SDK_VERSION,          // Always set this to D3D11_SDK_VERSION for Windows Store apps.
			nullptr,                    // No need to keep the D3D device reference.
			nullptr,                    // No need to know the feature level.
			nullptr                     // No need to keep the D3D device context reference.
		);

		return SUCCEEDED(hr);
	}
#endif

	//  Template Singleton Class
	template <class T>
	class TSingleton
	{
	protected:

		static T *m_pSingleton;

	public:

		virtual ~TSingleton()
		{
		} // Destructor

		inline static T* Get()
		{
			if (!m_pSingleton)
				m_pSingleton = new T;

			return(m_pSingleton);
		}// Get

		static void Del()
		{
			if (m_pSingleton)
			{
				delete (m_pSingleton);
				m_pSingleton = NULL;
			}
		}//Del
	};

	template <class T>
	T* TSingleton<T>::m_pSingleton = 0;

	// Convert a wide Unicode string to an UTF8 string
	std::string utf8_encode(const std::wstring &wstr);

	// Convert an UTF8 string to a wide Unicode String
	std::wstring utf8_decode(const std::string &str);
}//namespace WOtech
#endif