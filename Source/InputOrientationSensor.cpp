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
///			Edited:		01.06.2017
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include <pch.h>
#include <Input.h>

namespace WOtech
{
	Platform::Boolean InputManager::OrientationSensorConnected()
	{
		Windows::Devices::Sensors::OrientationSensor^ sensor = Windows::Devices::Sensors::OrientationSensor::GetDefault();
		if (sensor != nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void InputManager::ActivateOrientationSensor(_In_ Windows::Devices::Sensors::SensorReadingType Type, _In_ Windows::Devices::Sensors::SensorOptimizationGoal Goal, _In_ uint32 Interval)
	{
		m_orientationSensor = Windows::Devices::Sensors::OrientationSensor::GetDefault(Type, Goal);

		if (m_orientationSensor != nullptr)
		{
			m_orientationSensor->ReportInterval = (std::max)(m_orientationSensor->MinimumReportInterval, Interval);
			m_orientationToken = m_orientationSensor->ReadingChanged += ref new Windows::Foundation::TypedEventHandler<Windows::Devices::Sensors::OrientationSensor^, Windows::Devices::Sensors::OrientationSensorReadingChangedEventArgs^>(this, &InputManager::ReadingChanged);
			m_orientationActive = true;
		}
		else
		{
			throw ref new Platform::NotImplementedException;// TODO Exeption
		}
	}
	void InputManager::DeactivateOrientationSensor()
	{
		m_orientationSensor->ReportInterval = 0U;
		m_orientationSensor->ReadingChanged -= m_orientationToken;
		m_orientationActive = false;
	}
	Platform::Boolean InputManager::OrientationSensorActive()
	{
		return m_orientationActive;
	}
	void InputManager::OrientationSensorQuaternion(_Out_ Windows::Devices::Sensors::SensorQuaternion^ Quaternion)
	{
		Quaternion = m_orientationSensorReading->Quaternion;
	}
	void InputManager::OrientationSensorMatrix(_Out_ Windows::Devices::Sensors::SensorRotationMatrix^ Matrix)
	{
		Matrix = m_orientationSensorReading->RotationMatrix;
	}
}// namespace WOtech