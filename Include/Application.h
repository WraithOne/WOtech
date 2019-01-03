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
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_APPLICATION_H
#define WO_APPLICATION_H

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <IGame.h>

namespace WOtech
{
	/////////////////////////////////////////////////////////////////////////
	// Forward declarations
	ref class DeviceDX11;
	ref class SpriteBatch;
	interface class IRenderer;
	ref class AudioEngine;
	ref class InputManager;
	ref class VirtualController;
	ref class Window;

	ref class FrameworkView sealed : public Windows::ApplicationModel::Core::IFrameworkView
	{
	public:
		FrameworkView();
		void addGame(IGame^ game);
	
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
		bool						m_windowClosed;
		bool						m_windowVisible;

		// Game Instance
		WOtech::IGame^				m_game;

		// WOtech devices
		WOtech::Window^				m_window;

		WOtech::DeviceDX11^			m_device;
		WOtech::IRenderer^			m_renderer;
		WOtech::SpriteBatch^		m_spriteBatch;

		WOtech::AudioEngine^		m_audioEngine;

		WOtech::InputManager^		m_inputManager;
		WOtech::VirtualController^	m_virtualController;

		WOtech::GameTimer^			m_gametimer;
	};

	ref class ViewSource : Windows::ApplicationModel::Core::IFrameworkViewSource
	{
	public:
		virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView();

		void addGame(IGame^ game);

	private:
		IGame^ m_game;
	};
} // namespace WOtech

#endif