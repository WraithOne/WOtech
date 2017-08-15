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
///			Edited:		15.08.2017
///
////////////////////////////////////////////////////////////////////////////
#pragma once
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
	inline void ThrowIfFailed(_In_ HRESULT hr)
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
	inline float32 DegreetoRadian(_In_ float32 degree)
	{
		float32 radian;

		radian = degree*(DA_PI / 180);

		return radian;
	}

	// Ceck if value is between min and max
	inline float32 InRange(_In_ float32 value, _In_ float32 min, _In_ float32 max)
	{
		float32 output = 0.0f;
		if (value < min)
			output = min;
		else if (value > max)
			output = max;
		else
			output = value;

		return value;
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

	// PIX support
#define PIXBEGINEVENT(color, text)\
	PIXBeginEvent(color, text);

#define PIXBEGINEVENTCONTEXT(context, color, text)\
	PIXBeginEvent(context,color,text);

#define PIXENDEVENT()\
		PIXEndEvent();
#else
#define PIXBEGINEVENT(color, text)		\
	{									\
		UNREFERENCED_PARAMETER(color);	\
		UNREFERENCED_PARAMETER(text);	\
	}

#define PIXBEGINEVENTCONTEXT(context, color, text)	\
	{										\
		UNREFERENCED_PARAMETER(context);	\
		UNREFERENCED_PARAMETER(color);		\
		UNREFERENCED_PARAMETER(text);		\
	}

#define PIXENDEVENT();

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
	inline std::string utf8_encode(_In_ const std::wstring &wstr)
	{
		if (wstr.empty()) return std::string();
		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
		std::string strTo(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
		return strTo;
	}

	// Convert an UTF8 string to a wide Unicode String
	inline std::wstring utf8_decode(_In_ const std::string &str)
	{
		if (str.empty()) return std::wstring();
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
		std::wstring wstrTo(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
		return wstrTo;
	}
}//namespace WOtech
#endif