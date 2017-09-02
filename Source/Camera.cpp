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
///			Edited:		02.09.2017
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
#undef min // Use __min instead.
#undef max // Use __max instead.

using namespace DirectX;
using namespace WOtech;

namespace WOtech
{
	Camera::Camera()
	{
		// Setup the view matrix.
		FLOAT3 eye;
		eye.X = 0.0f;
		eye.Y = 0.0f;
		eye.Z = 0.0f;

		FLOAT3 lookAt;
		lookAt.X = 0.0f;
		lookAt.Y = 0.0f;
		lookAt.Z = 1.0f;

		FLOAT3 up;
		up.X = 0.0f;
		up.Y = 1.0f;
		up.Z = 0.0f;

		SetViewParams(eye, lookAt, up);

		// Setup the projection matrix.
		// FOV 60
		// AspectRatio 16:9
		// NearPlane 0.01
		// Farplane 1000
		SetProjParams(60.0f, 1.7777f, 0.01f, 1000.0f);
	}

	void Camera::LookDirection(_In_ FLOAT3 lookDirection)
	{
		FLOAT3 lookAt;
		lookAt.X = m_eye.X + lookDirection.X;
		lookAt.Y = m_eye.Y + lookDirection.Y;
		lookAt.Z = m_eye.Z + lookDirection.Z;

		SetViewParams(m_eye, lookAt, m_up);
	}

	void Camera::Eye(_In_ FLOAT3 eye)
	{
		SetViewParams(eye, m_lookAt, m_up);
	}

	void Camera::SetViewParams(_In_ FLOAT3 eye, _In_ FLOAT3 lookAt, _In_ FLOAT3 up)
	{
		m_eye = eye;
		m_lookAt = lookAt;
		m_up = up;

		// Calculate the view matrix.
		XMMATRIX view = XMMatrixLookAtRH(
			XMLoadFloat3(&DirectX::XMFLOAT3(eye.X, eye.Y, eye.Z)),
			XMLoadFloat3(&DirectX::XMFLOAT3(lookAt.X, lookAt.Y, lookAt.Z)),
			XMLoadFloat3(&DirectX::XMFLOAT3(up.X, up.Y, up.Z))
		);

		XMVECTOR det;
		XMMATRIX inverseView = XMMatrixInverse(&det, view);
		XMStoreFloat4x4(&m_viewMatrix, view);
		XMStoreFloat4x4(&m_inverseView, inverseView);

		// The axis basis vectors and camera position are stored inside the
		// position matrix in the 4 rows of the camera's world matrix.
		// To figure out the yaw/pitch of the camera, we just need the Z basis vector.
		XMFLOAT3 zBasis;
		XMStoreFloat3(&zBasis, inverseView.r[2]);

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
		XMStoreFloat4x4(&m_projectionMatrix, XMMatrixPerspectiveFovRH(m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane));
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

	FLOAT3 Camera::Eye()
	{
		return m_eye;
	}

	FLOAT3 Camera::LookAt()
	{
		return m_lookAt;
	}

	FLOAT3 Camera::Up()
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