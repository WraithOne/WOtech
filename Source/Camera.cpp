////////////////////////////////////////////////////////////////////////////
///
///			WraithOne tech Engine
///
///			File: Camera.cpp
///
///			Created:	10.05.2014
///			Edited:		06.11.2016
///
////////////////////////////////////////////////////////////////////////////

//////////////
// INCLUDES //
//////////////
#include "pch.h"
#include "Graphic.h"

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#undef min // Use __min instead.
#undef max // Use __max instead.

using namespace DirectX;
using namespace WOtech::DXWrapper;
using namespace Windows::Foundation::Numerics;

namespace WOtech
{
	Camera::Camera()
	{
		// Setup the view matrix.
		float3 eye;
		eye.x = 0.0f;
		eye.y = 0.0f;
		eye.z = 0.0f;

		float3 lookAt;
		lookAt.x = 0.0f;
		lookAt.y = 0.0f;
		lookAt.z = 1.0f;

		float3 up;
		up.x = 0.0f;
		up.y = 1.0f;
		up.z = 0.0f;

		SetViewParams(eye, lookAt, up);

		// Setup the projection matrix.
		SetProjParams(XM_PI / 4, 1.0f, 1.0f, 1000.0f);
	}

	void Camera::LookDirection(_In_ float3 lookDirection)
	{
		float3 lookAt;
		lookAt.x = m_eye.x + lookDirection.x;
		lookAt.y = m_eye.y + lookDirection.y;
		lookAt.z = m_eye.z + lookDirection.z;

		SetViewParams(m_eye, lookAt, m_up);
	}

	void Camera::Eye(_In_ float3 eye)
	{
		SetViewParams(eye, m_lookAt, m_up);
	}

	void Camera::SetViewParams(_In_ float3 eye, _In_ float3 lookAt, _In_ float3 up)
	{
		m_eye = eye;
		m_lookAt = lookAt;
		m_up = up;

		// Calculate the view matrix.
		XMMATRIX view = XMMatrixLookAtLH(
			XMLoadFloat3(&DirectX::XMFLOAT3(eye.x,eye.y,eye.z)),
			XMLoadFloat3(&DirectX::XMFLOAT3(lookAt.x, lookAt.y, lookAt.z)),
			XMLoadFloat3(&DirectX::XMFLOAT3(up.x, up.y, up.z))
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
		m_fieldOfView = fieldOfView;
		m_aspectRatio = aspectRatio;
		m_nearPlane = nearPlane;
		m_farPlane = farPlane;
		XMStoreFloat4x4(&m_projectionMatrix,XMMatrixPerspectiveFovLH(m_fieldOfView,m_aspectRatio,m_nearPlane,m_farPlane));
	}

	float4x4 Camera::View()
	{
		return wrapXMFloat4x4(m_viewMatrix);
	}

	float4x4 Camera::Projection()
	{
		return wrapXMFloat4x4(m_projectionMatrix);
	}

	float4x4 Camera::World()
	{
		return wrapXMFloat4x4(m_inverseView);
	}

	float3 Camera::Eye()
	{
		return m_eye;
	}

	float3 Camera::LookAt()
	{
		return m_lookAt;
	}

	float3 Camera::Up()
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