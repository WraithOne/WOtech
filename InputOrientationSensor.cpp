////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: InputOrientationSensor.cpp
///
///			Created:	26.08.2016
///			Edited:		06.11.2016
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Input.h"

using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Platform;

namespace WOtech
{
	Boolean InputManager::OrientationSensorConnected()
	{
		return Boolean();
	}
	void InputManager::ActivateOrientationSensor(_In_ uint32 interval)
	{
		throw ref new NotImplementedException();
	}
	void InputManager::DeactivateOrientationSensor()
	{
		throw ref new NotImplementedException();
	}
	Boolean InputManager::OrientationSensorActive()
	{
		return Boolean();
	}
	void InputManager::OrientationSensorQuaternion(_In_ Windows::Devices::Sensors::SensorQuaternion^ quaternion)
	{
		throw ref new NotImplementedException();
	}
	void InputManager::OrientationSensorMatrix(_Out_ Windows::Devices::Sensors::SensorRotationMatrix^ martix)
	{
		throw ref new NotImplementedException();
	}
}// namespace WOtech