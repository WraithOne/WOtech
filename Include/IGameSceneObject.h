////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: GameSceneObject.h
///
///			Description:
///
///			Created:	10.04.2016
///			Edited:		05.01.2019
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_GAMESCENEOBJECT_H
#define WO_GAMESCENEOBJECT_H

//////////////
// INCLUDES //
//////////////

namespace WOtech
{
	public interface class IGameSceneObject
	{
	public:
		virtual uint32 getID() = 0;
	};
}
#endif