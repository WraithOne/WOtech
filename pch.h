////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: pch.h
///
///			Description:
///
///			Created:	01.03.2015
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "targetver.h"
// STL
#pragma warning(disable : 4324 4481)
#include <exception>

#include <memory>
#include <string>
#include <vector>
#include <list>
// Windows
#pragma warning( disable : 4251 4264)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#include <windows.h>
#include <windows.foundation.numerics.h>
#include <wrl.h>
#include <wrl/client.h>
#include <concrt.h>
#include <collection.h>
#include <ppltasks.h>
#include <wincodec.h>

// DirectX
#include <DXGItype.h>
#include <dxgi1_6.h>
#include <d3d11_4.h>
#include <d2d1_3.h>
#include <d2d1effects_2.h>
#include <d2d1_3helper.h>
#include <dwrite_3.h>

#include <DirectXColors.h>
#include <DirectXMath.h>

#include <xaudio2.h>
#include <xaudio2fx.h>

/////////////
// LINKING //
/////////////
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "Dwrite.lib")
#pragma comment (lib, "Windowscodecs.lib")

/////////////
// Macros  //
/////////////
#define IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS
#define IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS
#define _CRT_SECURE_NO_WARNINGS
#define IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCS