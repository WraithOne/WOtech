////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			https://github.com/WraithOne/WOtech
///			by https://twitter.com/WraithOne
///
///			File: Camera.cpp
///
///			Description:
///
///			Created:	10.05.2014
///			Edited:		01.06.2018
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include <3DComponents.h>
#include <DXWrapper.h>
#include <Utilities.h>

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////

namespace WOtech
{
	Camera::Camera()
	{
		// Setup the view matrix.
		Windows::Foundation::Numerics::float3 eye;
		eye.x = 0.0f;
		eye.y = 0.0f;
		eye.z = 0.0f;

		Windows::Foundation::Numerics::float3 lookAt;
		lookAt.x = 0.0f;
		lookAt.y = 0.0f;
		lookAt.z = 1.0f;

		Windows::Foundation::Numerics::float3 up;
		up.x = 0.0f;
		up.y = 1.0f;
		up.z = 0.0f;

		SetViewParams(eye, lookAt, up);

		// Setup the projection matrix.
		// FOV 60
		// AspectRatio 16:9
		// NearPlane 0.01
		// Farplane 1000
		SetProjParams(60.0f, 1.7777f, 0.01f, 1000.0f);
	}

	void Camera::LookDirection(_In_ Windows::Foundation::Numerics::float3 lookDirection)
	{
		Windows::Foundation::Numerics::float3 lookAt;
		lookAt.x = m_eye.x + lookDirection.x;
		lookAt.y = m_eye.y + lookDirection.y;
		lookAt.z = m_eye.z + lookDirection.z;

		SetViewParams(m_eye, lookAt, m_up);
	}

	void Camera::Eye(_In_ Windows::Foundation::Numerics::float3 eye)
	{
		SetViewParams(eye, m_lookAt, m_up);
	}

	void Camera::SetViewParams(_In_ Windows::Foundation::Numerics::float3 eye, _In_ Windows::Foundation::Numerics::float3 lookAt, _In_ Windows::Foundation::Numerics::float3 up)
	{
		m_eye = eye;
		m_lookAt = lookAt;
		m_up = up;

		// Calculate the view matrix.
		DirectX::XMMATRIX view = DirectX::XMMatrixLookAtRH(
			XMLoadFloat3(&DirectX::XMFLOAT3(eye.x, eye.y, eye.z)),
			XMLoadFloat3(&DirectX::XMFLOAT3(lookAt.x, lookAt.y, lookAt.z)),
			XMLoadFloat3(&DirectX::XMFLOAT3(up.x, up.y, up.z))
		);

		DirectX::XMVECTOR det;
		DirectX::XMMATRIX inverseView = XMMatrixInverse(&det, view);
		XMStoreFloat4x4(&m_viewMatrix, view);
		XMStoreFloat4x4(&m_inverseView, inverseView);

		// The axis basis vectors and camera position are stored inside the
		// position matrix in the 4 rows of the camera's world matrix.
		// To figure out the yaw/pitch of the camera, we just need the Z basis vector.
		DirectX::XMFLOAT3 zBasis;
		DirectX::XMStoreFloat3(&zBasis, inverseView.r[2]);

		m_cameraYawAngle = atan2f(zBasis.x, zBasis.z);

		float32 len = sqrtf(zBasis.z * zBasis.z + zBasis.x * zBasis.x);
		m_cameraPitchAngle = atan2f(zBasis.y, len);
	}

	void Camera::SetProjParams(_In_ float32 fieldOfView, _In_ float32 aspectRatio, _In_ float32 nearPlane, _In_ float32 farPlane)
	{
		// Set attributes for the projection matrix.
		m_fieldOfView = DegreetoRadian(fieldOfView);
		m_aspectRatio = aspectRatio;
		if (aspectRatio < 1.0f)
		{
			// Portrait Oriantation
			m_fieldOfView *= 2.0f;// todo: add resolution/oriantation to arguments for proper scaling
		}
		m_nearPlane = nearPlane;
		m_farPlane = farPlane;
		XMStoreFloat4x4(&m_projectionMatrix, DirectX::XMMatrixPerspectiveFovRH(m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane));
	}

	DirectX::XMFLOAT4X4 Camera::ViewMatrix()
	{
		return m_viewMatrix;
	}

	DirectX::XMFLOAT4X4 Camera::ProjectionMatrix()
	{
		return m_projectionMatrix;
	}

	DirectX::XMFLOAT4X4 Camera::InverseMatrix()
	{
		return m_inverseView;
	}

	Windows::Foundation::Numerics::float3 Camera::Eye()
	{
		return m_eye;
	}

	Windows::Foundation::Numerics::float3 Camera::LookAt()
	{
		return m_lookAt;
	}

	Windows::Foundation::Numerics::float3 Camera::Up()
	{
		return m_up;
	}

	float32 Camera::NearClipPlane()
	{
		return m_nearPlane;
	}

	float32 Camera::FarClipPlane()
	{
		return m_farPlane;
	}

	float32 Camera::Pitch()
	{
		return m_cameraPitchAngle;
	}

	float32 Camera::Yaw()
	{
		return m_cameraYawAngle;
	}
}//namespace WOtech