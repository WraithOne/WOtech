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
///			Edited:		17.08.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "2DComponents.h"
#include "SpriteBatch.h"

using namespace WOtech::DXWrapper;
using namespace Windows::Foundation;
using namespace Windows::UI;

namespace WOtech
{
	Geometry::Geometry()
	{
		// todo: Content Manager
	}
	void WOtech::Geometry::Create(SpriteBatch ^ spritebatch)
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

	void Geometry::StartFigure(Point startposition, FIGURE_BEGIN begin)
	{
		m_geometrySink->BeginFigure(wrapPoint(startposition), wrapFigureBegin(begin));
	}
	void Geometry::addArc(ARC_SEGMENT arcsegment)
	{
		m_geometrySink->AddArc(wrapArcSegment(arcsegment));
	}
	void Geometry::addBezier(BEZIER_SEGMENT beziersegment)
	{
		m_geometrySink->AddBezier(wrapBezierSegment(beziersegment));
	}
	void Geometry::addLine(Point lineend)
	{
		m_geometrySink->AddLine(wrapPoint(lineend));
	}
	void Geometry::EndFigure(FIGURE_END figureend)
	{
		m_geometrySink->EndFigure(wrapFigureEnd(figureend));
	}

	void Geometry::CloseGeometry()
	{
		HRESULT hr;
		hr = m_geometrySink->Close();
		ThrowIfFailed(hr);
	}

	void Geometry::setColor(Color color)
	{
		m_geometryBrush->SetColor(wrapColorD2D(color));
	}

	ID2D1PathGeometry * Geometry::getGeometry()
	{
		return m_geometryPath.Get();
	}
	ID2D1SolidColorBrush * Geometry::getBrush()
	{
		return m_geometryBrush.Get();
	}
	Geometry::~Geometry()
	{
		// todo: Content Manager
	}
}