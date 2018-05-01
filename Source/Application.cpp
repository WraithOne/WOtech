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
///			Edited:		01.05.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include <ppltasks.h>

#include "SystemManager.h"
#include "ContentManager.h"
#include "Include\Application.h"

#include "Include\DeviceDX11.h"
#include "Include\ForwardRenderer.h"
#include "Include\DeferredRenderer.h"
#include "Include\SpriteBatch.h"

#include "Include\Audio.h"

#include "Include\Input.h"
#include "VirtualController.h"

#include "Include\GameTimer.h"

using namespace concurrency;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;

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
		applicationView->Activated += ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &FrameworkView::OnActivated);

		CoreApplication::Suspending += ref new EventHandler<SuspendingEventArgs^>(this, &FrameworkView::OnSuspending);

		CoreApplication::Resuming += ref new EventHandler<Platform::Object^>(this, &FrameworkView::OnResuming);

		m_game->Initalize();
	}
	void FrameworkView::SetWindow(Windows::UI::Core::CoreWindow ^ window)
	{
		window->SizeChanged += ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &FrameworkView::OnWindowSizeChanged);

		window->VisibilityChanged += ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &FrameworkView::OnVisibilityChanged);

		window->Closed += ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^>(this, &FrameworkView::OnWindowClosed);

		DisplayInformation^ currentDisplayInformation = DisplayInformation::GetForCurrentView();

		currentDisplayInformation->DpiChanged += ref new TypedEventHandler<DisplayInformation^, Object^>(this, &FrameworkView::OnDpiChanged);

		currentDisplayInformation->OrientationChanged += ref new TypedEventHandler<DisplayInformation^, Object^>(this, &FrameworkView::OnOrientationChanged);

		DisplayInformation::DisplayContentsInvalidated += ref new TypedEventHandler<DisplayInformation^, Object^>(this, &FrameworkView::OnDisplayContentsInvalidated);
	}
	void FrameworkView::Load(Platform::String ^ entryPoint)
	{
		m_device = ref new WOtech::DeviceDX11();
		m_device->Create();

		m_renderer = ref new WOtech::ForwardRenderer(m_device);
		m_spriteBatch = ref new WOtech::SpriteBatch(m_device);

		m_audioEngine = ref new WOtech::AudioEngine();
		m_audioEngine->Initialize();

		m_inputManager = ref new WOtech::InputManager();
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
				CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

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
				CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);

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
		CoreWindow::GetForCurrentThread()->Activate();
	}
	void FrameworkView::OnSuspending(Platform::Object ^ sender, Windows::ApplicationModel::SuspendingEventArgs ^ args)
	{
		SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();

		create_task([this, deferral]()
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