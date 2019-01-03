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
#include <pch.h>
#include <2DComponents.h>

namespace WOtech
{
	public interface class IBatch2D
	{
		virtual UINT getID() = 0;
		virtual float getDepth() = 0;
	};

	public ref class Batch2D_Text sealed : public IBatch2D
	{
	public:
		Batch2D_Text(_In_ WOtech::TextBlock^ text, _In_ UINT ID, _In_ float depth);

		virtual UINT getID();
		virtual float getDepth();
		WOtech::TextBlock^ getText();

	private:
		UINT				m_batchID;
		float				m_depth;
		WOtech::TextBlock^	m_text;
	};
}
#endif