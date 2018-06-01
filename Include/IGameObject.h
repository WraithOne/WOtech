////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: GameObject.h
///
///			Description:
///
///			Created:	10.04.2016
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_GAMEOBJECT_H
#define WO_GAMEOBJECT_H

//////////////
// INCLUDES //
//////////////

namespace WOtech
{
	public interface class IGameObject
	{
	public:
		virtual uint32 getID() = 0;
	};
}
#endif