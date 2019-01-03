////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Geometry.cpp
///
///			Description:
///
///			Created:	14.11.2016
///			Edited:		23.09.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <2DComponents.h>
#include <SpriteBatch.h>
#include <Utilities.h>
#include <DXWrapper.h>

namespace WOtech
{
	Geometry::Geometry()
	{
		// todo: Content Manager
	}
	void WOtech::Geometry::Create(_In_ WOtech::SpriteBatch^ spritebatch)
	{
		HRESULT hr;
		// Create GeometryPath
		hr = spritebatch->getFactory()->CreatePathGeometry(m_geometryPath.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);
		// Create Geometrybrush
		hr = spritebatch->GetDeviceContext()->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), m_geometryBrush.ReleaseAndGetAddressOf());
		ThrowIfFailed(hr);
	}

	void Geometry::OpenGeometry()
	{
		HRESULT hr;
		hr = m_geometryPath->Open(m_geometrySink.ReleaseAndGetAddressOf());
	}

	void Geometry::StartFigure(_In_ Windows::Foundation::Point startposition, _In_ WOtech::FIGURE_BEGIN begin)
	{
		m_geometrySink->BeginFigure(WOtech::DXWrapper::wrapPoint(startposition), WOtech::DXWrapper::wrapFigureBegin(begin));
	}
	void Geometry::addArc(_In_ WOtech::ArcSegment arcsegment)
	{
		m_geometrySink->AddArc(WOtech::DXWrapper::wrapArcSegment(arcsegment));
	}
	void Geometry::addBezier(_In_ WOtech::BezierSegment beziersegment)
	{
		m_geometrySink->AddBezier(WOtech::DXWrapper::wrapBezierSegment(beziersegment));
	}
	void Geometry::addLine(_In_ Windows::Foundation::Point lineend)
	{
		m_geometrySink->AddLine(WOtech::DXWrapper::wrapPoint(lineend));
	}
	void Geometry::EndFigure(_In_ WOtech::FIGURE_END figureend)
	{
		m_geometrySink->EndFigure(WOtech::DXWrapper::wrapFigureEnd(figureend));
	}

	void Geometry::CloseGeometry()
	{
		HRESULT hr;
		hr = m_geometrySink->Close();
		ThrowIfFailed(hr);
	}

	void Geometry::setColor(_In_ Windows::UI::Color color)
	{
		m_geometryBrush->SetColor(WOtech::DXWrapper::wrapColorD2D(color));
	}

	ID2D1PathGeometry* Geometry::getGeometry()
	{
		return m_geometryPath.Get();
	}
	ID2D1SolidColorBrush* Geometry::getBrush()
	{
		return m_geometryBrush.Get();
	}
	Geometry::~Geometry()
	{
		// todo: Content Manager
	}
}