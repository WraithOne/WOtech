////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: InputOrientationSensor.cpp
///
///			Description:
///
///			Created:	26.08.2016
///			Edited:		29.01.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Input.h"

using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::Devices::Sensors;
using namespace Windows::Foundation;
using namespace Platform;

namespace WOtech
{
	Boolean InputManager::OrientationSensorConnected()
	{
		OrientationSensor^ sensor = OrientationSensor::GetDefault();
		if (sensor != nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void InputManager::ActivateOrientationSensor(_In_ SensorReadingType Type, _In_ SensorOptimizationGoal Goal, _In_ uint32 Interval)
	{
		m_orientationSensor = OrientationSensor::GetDefault(Type, Goal);

		if (m_orientationSensor != nullptr)
		{
			m_orientationSensor->ReportInterval = (std::max)(m_orientationSensor->MinimumReportInterval, Interval);
			m_orientationToken = m_orientationSensor->ReadingChanged += ref new TypedEventHandler<OrientationSensor^, OrientationSensorReadingChangedEventArgs^>(this, &InputManager::ReadingChanged);
			m_orientationActive = true;
		}
		else
		{
			throw ref new NotImplementedException;// TODO Exeption
		}
	}
	void InputManager::DeactivateOrientationSensor()
	{
		m_orientationSensor->ReportInterval = 0U;
		m_orientationSensor->ReadingChanged -= m_orientationToken;
		m_orientationActive = false;
	}
	Boolean InputManager::OrientationSensorActive()
	{
		return m_orientationActive;
	}
	void InputManager::OrientationSensorQuaternion(_Out_ SensorQuaternion^ Quaternion)
	{
		Quaternion = m_orientationSensorReading->Quaternion;
	}
	void InputManager::OrientationSensorMatrix(_Out_ SensorRotationMatrix^ Matrix)
	{
		Matrix = m_orientationSensorReading->RotationMatrix;
	}
}// namespace WOtech