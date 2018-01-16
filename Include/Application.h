////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Application.h
///
///			Description:
///
///			Created:	14.01.2018
///			Edited:		14.01.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_APPLICATION_H
#define WO_APPLICATION_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Game.h"

namespace WOtech
{
	/////////////////////////////////////////////////////////////////////////
	// Forward declarations
	ref class DeviceDX11;
	ref class SpriteBatch;
	ref class AudioEngine;
	ref class InputManager;
	interface class IRenderer;

	ref class FrameworkView sealed : public Windows::ApplicationModel::Core::IFrameworkView
	{
	public:
		FrameworkView();

	
		// IFrameworkView Methods
		virtual void Initialize(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView);
		virtual void SetWindow(Windows::UI::Core::CoreWindow^ window);
		virtual void Load(Platform::String^ entryPoint);
		virtual void Run();
		virtual void Uninitialize();

	protected:
		// Application lifecycle event handlers.
		void OnActivated(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView, Windows::ApplicationModel::Activation::IActivatedEventArgs^ args);
		void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
		void OnResuming(Platform::Object^ sender, Platform::Object^ args);

		// Window event handlers.
		void OnWindowSizeChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ args);
		void OnVisibilityChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ args);
		void OnWindowClosed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CoreWindowEventArgs^ args);
		void OnWindowActivationChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowActivatedEventArgs^ args);

		// DisplayInformation event handlers.
		void OnDpiChanged(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);
		void OnOrientationChanged(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);
		void OnDisplayContentsInvalidated(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);
		void OnStereoEnabledChanged(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);

	private:
		bool					WindowClosed;    // change to true when it's time to close the window
		bool					WindowVisible;

		// Game Instance
		WOtech::Game^			m_game;

		// WOtech devices
		WOtech::DeviceDX11^		m_device;
		WOtech::IRenderer^		m_renderer;
		WOtech::SpriteBatch^	m_spriteBatch;
		WOtech::AudioEngine^	m_audioEngine;
		WOtech::InputManager^	m_inputManager;
	};

	ref class ViewSource : Windows::ApplicationModel::Core::IFrameworkViewSource
	{
	public:
		virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView()
		{
			return ref new FrameworkView();
		}
	};

	public ref class Application sealed
	{
	public:
		Application();
		void Run(Game^ game);

	private:
	};
} // namespace WOtech
#endif