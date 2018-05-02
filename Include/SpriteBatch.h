////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: SpriteBatch.cpp
///
///			Description:
///
///			Created:	07.05.2014
///			Edited:		02.05.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_SPRITEBATCH_H
#define WO_SPRITEBATCH_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "2DComponents.h"

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////

namespace WOtech
{
	// Forward Declaration
	ref class DeviceDX11;

	public enum class SpriteSortMode
	{
		Immediate,
		Deferred,
		Texture,
		BacktoFront,
		FronttoBack
	};

	public ref class SpriteBatch sealed
	{
	public:
		/**
		Constructor
		@param Pointer to a valid DeviceDX11
		*/
		SpriteBatch(_In_ WOtech::DeviceDX11^ device);

		void BeginDraw();
		void BeginDraw(_In_ SpriteSortMode sortmode);

		void EndDraw();

		void DrawTextBlock(_In_ WOtech::TextBlock^ text);
		void DrawString(_In_ WOtech::Font^ font, _In_ float32 fontSize, _In_ WOtech::RECT layoutbox, _In_ WOtech::FONT_STYLE style, _In_ Windows::UI::Color color, _In_ float32 rotation, _In_ Platform::String^ text);

		void DrawBitmap(_In_ WOtech::Bitmap^ bitmap);
		void DrawBitmap(_In_ WOtech::Bitmap^ bitmap, _In_ WOtech::RECT srcRect, _In_ WOtech::RECT destRect, _In_ float32 opacity, _In_ float32 rotation);

		void DrawSprite(_In_ WOtech::Sprite^ sprite);
		void DrawSprite(_In_ WOtech::Sprite^ sprite, _In_ WOtech::RECT srcRect, _In_ WOtech::RECT destRect, _In_ float32 opacity, _In_ float32 rotation, _In_ WOtech::SPRITE_FLIP_MODE flipmode);

		void DrawAnimatedSprite(_In_ WOtech::AnimatedSprite^ animatedsprite, _In_ Platform::String^ name);

		void DrawGrid(_In_ WOtech::RECT area, _In_ Windows::UI::Color color, _In_ float32 rotation);

		void DrawCircle(_In_ CIRCLE circle);
		void DrawCircleOutlined(_In_ CIRCLE_OUTLINED circleOutlined);
		void DrawCircleFilled(_In_ CIRCLE_FILLED circleFilled);

		void DrawRectangle(_In_ RECTANGLE rectangle);
		void DrawRectangleOutlined(_In_ RECTANGLE_OUTLINED rectangleOutlined);
		void DrawRectangleFilled(_In_ RECTANGLE_FILLED rectangleFilled);

		void DrawGeometry(_In_ Geometry^ geometry, _In_ FLOAT strokeWidth);

		// Getter
		WOtech::Image^				getRenderTarget();
		Windows::Foundation::Size	getLogicalSize();
		WOtech::RECT				getRenderRect();

		// Setter
		[Windows::Foundation::Metadata::DefaultOverloadAttribute]
		void setRenderTarget(_In_ WOtech::Image^ rendertarget);
		void setRenderTarget(_In_ WOtech::Bitmap^ rendertarget);

		void ReleaseRendertarget();

	internal:
		void Initialize();

		ID2D1DeviceContext5*		GetDeviceContext();
		ID2D1Factory6*				getFactory();

	private:
		~SpriteBatch();

		void CreateGrid(_In_ Windows::UI::Color color);
		void setRotation(_In_ WOtech::RECT area, _In_ float32 rotation);

		void SortBatch();
		void DrawBatch();

		void Release();

	private:
		WOtech::DeviceDX11^								m_deviceDX11;

		Microsoft::WRL::ComPtr<ID2D1Factory6>			m_factory;
		Microsoft::WRL::ComPtr<ID2D1Device5>			m_device;
		Microsoft::WRL::ComPtr<ID2D1DeviceContext5>		m_deviceContext;
		Microsoft::WRL::ComPtr<ID2D1Bitmap1>			m_targetBitmap;

		Microsoft::WRL::ComPtr<IDWriteFactory5>			m_Wfactory;

		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>	m_fontBrush;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>	m_circleBrush;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>	m_rectangleBrush;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>	m_outlineBrush;
		Microsoft::WRL::ComPtr<ID2D1BitmapBrush1>		m_gridBrush;
		Windows::UI::Color								m_gridColor;

		SpriteSortMode									m_sortMode;
		Platform::Boolean								m_beginDraw;
	};// class SpriteBatch
}
#endif