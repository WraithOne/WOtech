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
///			Edited:		01.02.2017
///
////////////////////////////////////////////////////////////////////////////
#ifndef WO_GAMEOBJECT_H
#define WO_GAMEOBJECT_H

//////////////
// INCLUDES //
//////////////
#include "pch.h"

namespace WOtech
{
	public interface class IGameObject
	{
	public:
		UINT32 getID();
	};
}
#endif