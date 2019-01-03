////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Application.cpp
///
///			Description:
///
///			Created:	14.01.2018
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <ppltasks.h>

#include <SystemManager.h>
#include <ContentManager.h>
#include <Application.h>

#include <DeviceDX11.h>
#include <ForwardRenderer.h>
#include <DeferredRenderer.h>
#include <SpriteBatch.h>

#include <Audio.h>

#include <Input.h>
#include <VirtualController.h>

#include <GameTimer.h>

namespace WOtech
{
	FrameworkView::FrameworkView() : m_windowClosed(false), m_windowVisible(true)
	{
	}
	void FrameworkView::addGame(IGame ^ game)
	{
		m_game = game;
	}
	void FrameworkView::Initialize(Windows::ApplicationModel::Core::CoreApplicationView ^ applicationView)
	{
		applicationView->Activated += ref new Windows::Foundation::TypedEventHandler<Windows::ApplicationModel::Core::CoreApplicationView^, Windows::ApplicationModel::Activation::IActivatedEventArgs^>(this, &FrameworkView::OnActivated);

		Windows::ApplicationModel::Core::CoreApplication::Suspending += ref new Windows::Foundation::EventHandler<Windows::ApplicationModel::SuspendingEventArgs^>(this, &FrameworkView::OnSuspending);

		Windows::ApplicationModel::Core::CoreApplication::Resuming += ref new Windows::Foundation::EventHandler<Platform::Object^>(this, &FrameworkView::OnResuming);

		m_game->Initalize();
	}
	void FrameworkView::SetWindow(Windows::UI::Core::CoreWindow ^ window)
	{
		window->SizeChanged += ref new Windows::Foundation::TypedEventHandler<Windows::UI::Core::CoreWindow^, Windows::UI::Core::WindowSizeChangedEventArgs^>(this, &FrameworkView::OnWindowSizeChanged);

		window->VisibilityChanged += ref new Windows::Foundation::TypedEventHandler<Windows::UI::Core::CoreWindow^, Windows::UI::Core::VisibilityChangedEventArgs^>(this, &FrameworkView::OnVisibilityChanged);

		window->Closed += ref new Windows::Foundation::TypedEventHandler<Windows::UI::Core::CoreWindow^, Windows::UI::Core::CoreWindowEventArgs^>(this, &FrameworkView::OnWindowClosed);

		Windows::Graphics::Display::DisplayInformation^ currentDisplayInformation = Windows::Graphics::Display::DisplayInformation::GetForCurrentView();

		currentDisplayInformation->DpiChanged += ref new Windows::Foundation::TypedEventHandler<Windows::Graphics::Display::DisplayInformation^, Object^>(this, &FrameworkView::OnDpiChanged);

		currentDisplayInformation->OrientationChanged += ref new Windows::Foundation::TypedEventHandler<Windows::Graphics::Display::DisplayInformation^, Object^>(this, &FrameworkView::OnOrientationChanged);

		Windows::Graphics::Display::DisplayInformation::DisplayContentsInvalidated += ref new Windows::Foundation::TypedEventHandler<Windows::Graphics::Display::DisplayInformation^, Object^>(this, &FrameworkView::OnDisplayContentsInvalidated);
	}
	void FrameworkView::Load(Platform::String ^ entryPoint)
	{
		m_window = ref new WOtech::Window();

		m_device = ref new WOtech::DeviceDX11(m_window);
		m_device->Create();

		m_renderer = ref new WOtech::ForwardRenderer(m_device);

		m_spriteBatch = ref new WOtech::SpriteBatch(m_device);
		m_spriteBatch->Initialize();

		m_audioEngine = ref new WOtech::AudioEngine();
		m_audioEngine->Initialize();

		m_inputManager = ref new WOtech::InputManager(m_window);
		m_virtualController = ref new WOtech::VirtualController(m_inputManager);

		m_gametimer = ref new WOtech::GameTimer();

		m_game->Load();
	}
	void FrameworkView::Run()
	{
		while (!m_windowClosed)
		{
			if (m_windowVisible)
			{
				Windows::UI::Core::CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(Windows::UI::Core::CoreProcessEventsOption::ProcessAllIfPresent);

				// is stopped -> start again / start for first time
				if (!m_gametimer->Active())
					m_gametimer->Start();

				// updated gametime
				m_gametimer->Update();
				auto time = m_gametimer->GetTime();

				// Update
				m_game->Update(time);

				// Render
				m_game->Draw(time);
			}
			else
			{
				Windows::UI::Core::CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(Windows::UI::Core::CoreProcessEventsOption::ProcessOneAndAllPending);

				// stop running gametime
				if (m_gametimer->Active())
					m_gametimer->Stop();
			}
		}	
	}
	void FrameworkView::Uninitialize()
	{
		m_game->UnLoad();
	}
	void FrameworkView::OnActivated(Windows::ApplicationModel::Core::CoreApplicationView ^ applicationView, Windows::ApplicationModel::Activation::IActivatedEventArgs ^ args)
	{
		Windows::UI::Core::CoreWindow::GetForCurrentThread()->Activate();
	}
	void FrameworkView::OnSuspending(Platform::Object ^ sender, Windows::ApplicationModel::SuspendingEventArgs ^ args)
	{
		Windows::ApplicationModel::SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();

		concurrency::create_task([this, deferral]()
		{
			m_game->OnSuspending();

			WOtech::ContentManager::Instance->OnSuspending();
			WOtech::SystemManager::Instance->OnSuspending();

			deferral->Complete();
		});
		
	}
	void FrameworkView::OnResuming(Platform::Object ^ sender, Platform::Object ^ args)
	{
		WOtech::SystemManager::Instance->OnResume();
		WOtech::ContentManager::Instance->OnResume(m_spriteBatch);

		m_game->OnResuming();
	}
	void FrameworkView::OnWindowSizeChanged(Windows::UI::Core::CoreWindow ^ sender, Windows::UI::Core::WindowSizeChangedEventArgs ^ args)
	{
		auto size = args->Size;

		WOtech::ContentManager::Instance->OnWindowSizeChanged(size);
		WOtech::SystemManager::Instance->OnWindowSizeChanged(size);
	}
	void FrameworkView::OnVisibilityChanged(Windows::UI::Core::CoreWindow ^ sender, Windows::UI::Core::VisibilityChangedEventArgs ^ args)
	{
		m_windowVisible = args->Visible;
	}
	void FrameworkView::OnWindowClosed(Windows::UI::Core::CoreWindow ^ sender, Windows::UI::Core::CoreWindowEventArgs ^ args)
	{
		m_windowClosed = true;
	}
	void FrameworkView::OnWindowActivationChanged(Windows::UI::Core::CoreWindow ^ sender, Windows::UI::Core::WindowActivatedEventArgs ^ args)
	{
		
	}
	void FrameworkView::OnDpiChanged(Windows::Graphics::Display::DisplayInformation ^ sender, Platform::Object ^ args)
	{
		auto dpi = sender->LogicalDpi;// ToDo: logical or RAW

		WOtech::ContentManager::Instance->OnDpiChanged(dpi);
		WOtech::SystemManager::Instance->OnDpiChanged(dpi);
	}
	void FrameworkView::OnOrientationChanged(Windows::Graphics::Display::DisplayInformation ^ sender, Platform::Object ^ args)
	{
		auto orientation = sender->CurrentOrientation;

		WOtech::ContentManager::Instance->OnOrientationChanged(orientation);
		WOtech::SystemManager::Instance->OnOrientationChanged(orientation);
	}
	void FrameworkView::OnDisplayContentsInvalidated(Windows::Graphics::Display::DisplayInformation ^ sender, Platform::Object ^ args)
	{
		WOtech::ContentManager::Instance->OnDisplayContentsInvalidated();
		WOtech::SystemManager::Instance->OnDisplayContentsInvalidated();
	}
	void FrameworkView::OnStereoEnabledChanged(Windows::Graphics::Display::DisplayInformation ^ sender, Platform::Object ^ args)
	{
		auto enabled = sender->StereoEnabled;
		//WOtech::ContntManager::Instance->StereoEnabledChanged(enabled); ToDo
		//WOtech::SystemManager::Instance->StereoEnabledChanged(enabled); ToDo
	}

	Windows::ApplicationModel::Core::IFrameworkView ^ ViewSource::CreateView()
	{
		auto frameworkview = ref new FrameworkView();
		frameworkview->addGame(m_game);

		return frameworkview;
	}
	void ViewSource::addGame(WOtech::IGame^ game)
	{
		m_game = game;
	}
}