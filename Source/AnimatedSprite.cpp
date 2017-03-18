////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: AnimatedSprite.cpp
///
///			Description:
///
///			Created:	13.09.2014
///			Edited:		07.03.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "2DComponents.h"
#include "SpriteBatch.h"
#include "Utilities.h"
#include "ContentManager.h"

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI;
using namespace Windows::Storage;
using namespace Windows::ApplicationModel;
using namespace Microsoft::WRL;
using namespace WOtech::DXWrapper;

namespace WOtech
{
	AnimatedSprite::AnimatedSprite(_In_ Platform::String^ filename)
	{
		m_fileName = filename;
		m_position = Point(0.0f, 0.0f);
		m_size = Size(10.0f, 10.0f);
		m_rotation = 0.0f;
		m_opacity = 1.0f;
		m_interpolation = BITMAP_INTERPOLATION_MODE::BITMAP_INTERPOLATION_MODE_LINEAR;
		m_flipMode = SPRITE_FLIP_MODE::None;

		WOtech::ContentManager::Instance->AddAnimatedSprite(this);
	}

	void AnimatedSprite::Load(_In_ SpriteBatch^ spriteBatch)
	{
		HRESULT hr;

		ComPtr<IWICBitmapDecoder> pDecoder;
		ComPtr<IWICBitmapFrameDecode> pSource;
		ComPtr<IWICStream> pStream;
		ComPtr<IWICFormatConverter> pConverter;
		ComPtr<IWICBitmapScaler> pScaler;
		ComPtr<IWICImagingFactory> pWICFactory;

		m_Bitmap = nullptr;

		//hr = CoInitialize(NULL);

		// Create an instance of WICFactory
		hr = CoCreateInstance(CLSID_WICImagingFactory1, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)(&pWICFactory));
		ThrowIfFailed(hr);

		// Create Path/fulename String
		String^ path;
		String^ pathfilename;

		StorageFolder^ m_installedLocation = Package::Current->InstalledLocation;
		path = String::Concat(m_installedLocation->Path, "\\");
		pathfilename = String::Concat(path, m_fileName);
		LPCWSTR Filename = pathfilename->Data();

		hr = pWICFactory->CreateDecoderFromFilename(Filename, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
		ThrowIfFailed(hr);

		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
		ThrowIfFailed(hr);

		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pWICFactory->CreateFormatConverter(&pConverter);
		ThrowIfFailed(hr);

		hr = pConverter->Initialize(pSource.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
		ThrowIfFailed(hr);

		// Create a Direct2D bitmap from the WIC bitmap.
		hr = spriteBatch->GetDeviceContext()->CreateBitmapFromWicBitmap(pConverter.Get(), NULL, &m_Bitmap);
		ThrowIfFailed(hr);
	}
	void AnimatedSprite::UnLoad()
	{
		m_Bitmap.Reset();
	}
	Platform::Boolean AnimatedSprite::AddAnimation(_In_ String^ name, _In_ uint32 framecount, _In_ float32 frametime, _In_ Size framesize, _In_ Point sourceposition)
	{
		std::list<ANIMATION>::iterator iterator;

		for (iterator = m_animationList.begin(); iterator != m_animationList.end(); iterator++)
		{
			if (iterator->Name == name)
			{
				//g_pLogfile->Textout("Animation exists");
				return false;
			}
		}
		ANIMATION temp;

		temp.ActualFrame = 0;
		temp.Framecount = framecount;
		temp.FrameSize = framesize;
		temp.Frametime = frametime;
		temp.Lastime = 0.0f;
		temp.Name = name;
		temp.SourcePosition = sourceposition;

		m_animationList.push_back(temp);

		return true;
	}
	void AnimatedSprite::Update(_In_ String^ name, _In_ float32 elapsed)
	{
		std::list<ANIMATION>::iterator iterator;

		for (iterator = m_animationList.begin(); iterator != m_animationList.end(); iterator++)
		{
			if (iterator->Name == name)
			{
				iterator->Lastime += elapsed;
				if (iterator->Lastime > iterator->Frametime)
				{
					iterator->ActualFrame++;
					iterator->Lastime = elapsed;

					if (iterator->ActualFrame > iterator->Framecount)
						iterator->ActualFrame = 0;
					iterator->Lastime = 0.0f;
				}
			}
		}
	}
	void AnimatedSprite::Restart(_In_ String^ name)
	{
		std::list<ANIMATION>::iterator iterator;

		for (iterator = m_animationList.begin(); iterator != m_animationList.end(); iterator++)
		{
			if (iterator->Name == name)
			{
				iterator->ActualFrame = 0;
				iterator->Lastime = 0.0f;
			}
		}
	}

	ID2D1Bitmap* AnimatedSprite::getBitmap()
	{
		return m_Bitmap.Get();
	}
	AnimatedSprite::~AnimatedSprite()
	{
		WOtech::ContentManager::Instance->RemoveAnimatedSprite(this);
	}
	Point AnimatedSprite::getPosition()
	{
		return m_position;
	}
	Size AnimatedSprite::getSize()
	{
		return m_size;
	}
	Size AnimatedSprite::getFrameSize(_In_ String^ name)
	{
		std::list<ANIMATION>::iterator iterator;

		for (iterator = m_animationList.begin(); iterator != m_animationList.end(); iterator++)
		{
			if (iterator->Name == name)
			{
				return iterator->FrameSize;
			}
		}
		Size temp;
		temp.Width = 0.0f;
		temp.Height = 0.0f;

		return temp;
	}

	WOtech::DXWrapper::RECT AnimatedSprite::getFrame(_In_ String^ name)
	{
		std::list<ANIMATION>::iterator iterator;

		for (iterator = m_animationList.begin(); iterator != m_animationList.end(); iterator++)
		{
			if (iterator->Name == name)
			{
				WOtech::DXWrapper::RECT temp;
				float32 left = iterator->SourcePosition.X + (iterator->FrameSize.Width * iterator->ActualFrame);
				float32 top = iterator->SourcePosition.Y + iterator->FrameSize.Height;
				temp.X = left;
				temp.Y = top;
				temp.Width = left + iterator->FrameSize.Width;
				temp.Height = top + iterator->FrameSize.Height;

				return temp;
			}
		}
		return WOtech::DXWrapper::RECT{ 0.0f, 0.0f, 0.0f, 0.0f };
	}
	float32 AnimatedSprite::getOpacity()
	{
		return m_opacity;
	}
	float32 AnimatedSprite::getRotation()
	{
		return m_rotation;
	}
	SPRITE_FLIP_MODE AnimatedSprite::getFlipMode()
	{
		return m_flipMode;
	}
	BITMAP_INTERPOLATION_MODE AnimatedSprite::getInterpolation()
	{
		return m_interpolation;
	}

	void AnimatedSprite::setPosition(_In_ float32 x, _In_  float32 y)
	{
		m_position = { x,y };
	}
	void AnimatedSprite::setSize(_In_ float32 width, _In_ float32 height)
	{
		m_size = Size(width, height);
	}
	void AnimatedSprite::setOpacity(_In_ float32 opacity)
	{
		m_opacity = opacity;
	}
	void AnimatedSprite::setRotation(_In_ float32 degree)
	{
		m_rotation = degree;
	}
	void AnimatedSprite::setRotationinRadian(_In_ float32 radian)
	{
		m_rotation = WOtech::RadiantoDegree(radian);
	}
	void AnimatedSprite::setFlipMode(_In_ SPRITE_FLIP_MODE flipmode)
	{
		m_flipMode = flipmode;
	}
	void AnimatedSprite::setInterpolation(_In_ BITMAP_INTERPOLATION_MODE interpolation)
	{
		m_interpolation = interpolation;
	}
}//namespace WOtech