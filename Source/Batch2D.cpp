////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Batch2D.cpp
///
///			Description:
///
///			Created:	01.11.2017
///			Edited:		28.08.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Include/Batch2D.h"

namespace WOtech
{
	Batch2D_Text::Batch2D_Text(_In_ float depth, _In_ WOtech::TextBlock^ text)
	{
		m_depth = depth;
		m_text = text;
	}
	float Batch2D_Text::getDepth()
	{
		return m_depth;
	}
	WOtech::TextBlock^ Batch2D_Text::getText()
	{
		return m_text;
	}
}