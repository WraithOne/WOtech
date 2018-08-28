////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Batch2D.h
///
///			Description:
///
///			Created:	28.08.2018
///			Edited:		28.08.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_BATCH2D_H
#define WO_BATCH2D_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "2DComponents.h"

namespace WOtech
{
	public interface class IBatch2D
	{
		virtual float getDepth() = 0;
	};

	public ref class Batch2D_Text sealed : public IBatch2D
	{
	public:
		Batch2D_Text(_In_ float depth, _In_ WOtech::TextBlock^ text);
		virtual float getDepth();
		WOtech::TextBlock^ getText();

	private:
		float m_depth;
		WOtech::TextBlock^	m_text;
	};
}
#endif