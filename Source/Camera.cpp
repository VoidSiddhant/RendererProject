#include "Camera.h"
#include "Util.h"
using namespace DirectX;

namespace EngineSpace
{
	Camera::Camera()
	{
		//Set Matrices
		XMStoreFloat4x4(&m_view, XMMatrixIdentity());
		XMStoreFloat4x4(&m_projection, XMMatrixIdentity());
		//Set View Properties
		m_position = XMFLOAT3(0.0f,0.0f,0.0f);
		m_up = XMFLOAT3(0.0f, 1.0f, 0.0f);;
		m_target = XMFLOAT3(0.0f, 0.0f, 1.0f);
		m_right = XMFLOAT3(1.0f, 0.0f, 0.0f);
		//Set Projection Properties
		m_nearZ = 1.0f;
		m_farZ = 1000.0f;
		m_fov = 0.25f * SG_UTIL_MATH_RF_PI;
		m_aspect = (float)SG_UTIL_SCREEN_WIDTH / (float)SG_UTIL_SCREEN_HEIGHT;
	}

	Camera::Camera(const XMFLOAT3& position, const XMFLOAT3& target, const XMFLOAT3& up)
	{
		//Set Matrices
		XMStoreFloat4x4(&m_projection, XMMatrixIdentity());
		XMStoreFloat4x4(&m_view, XMMatrixIdentity());
		//Set View Properties
		m_position = position;
		m_up = up;
		m_target = target;
		m_right = XMFLOAT3(1.0f, 0.0f, 0.0f);
		//Set Projection Properties
		m_nearZ = 1.0f;
		m_farZ = 1000.0f;
		m_fov = 0.25f * SG_UTIL_MATH_RF_PI;
		m_aspect = (float)SG_UTIL_SCREEN_WIDTH / (float)SG_UTIL_SCREEN_HEIGHT;
	}

	void Camera::SetUpDirection(const DirectX::XMFLOAT3& value)
	{
		m_up = value;
	}

	void Camera::SetLookDirection(const DirectX::XMFLOAT3& value)
	{
		m_target = value;
	}

	void Camera::SetFoV(float value)
	{
		m_fov = value;
	}

	void Camera::SetAspect(float ratio)
	{
		m_aspect = ratio;
	}

	void Camera::SetNearPlane(float zDistance)
	{
		m_nearZ = zDistance;
	}

	void Camera::SetFarPlane(float fDistance)
	{
		
		m_farZ = fDistance;
	}

	void Camera::Translate(const DirectX::XMFLOAT3& vector)
	{
		// mPosition += d*mRight
		XMVECTOR s = XMLoadFloat3(&vector);
		XMVECTOR r = XMLoadFloat3(&m_right);
		XMVECTOR p = XMLoadFloat3(&m_position);
		XMStoreFloat3(&m_position, XMVectorMultiplyAdd(s, r, p));

		// mPosition += d*mLook
		XMVECTOR l = XMLoadFloat3(&m_target);
		XMStoreFloat3(&m_position, XMVectorMultiplyAdd(s, l, p));
		XMStoreFloat3(&m_position, p);

		//Set Translation matrix
		Transform::SetPosition(m_position);
	}

	void Camera::SetRotation(const DirectX::XMFLOAT3& vector)
	{
		//Calculate new rotationAxis and matrix
		Transform::SetRotation(vector);

		//Transform the axis coordinate
		XMStoreFloat3(&m_right, DirectX::XMVector3TransformNormal(XMLoadFloat3(&m_right), GetXM_Rotation()));
		XMStoreFloat3(&m_up, DirectX::XMVector3TransformNormal(XMLoadFloat3(&m_up), GetXM_Rotation()));
		XMStoreFloat3(&m_target, DirectX::XMVector3TransformNormal(XMLoadFloat3(&m_target), GetXM_Rotation()));

	}

	void Camera::SetPosition(const DirectX::XMFLOAT3& vector)
	{
		// mPosition += d*mRight
		XMVECTOR s = XMLoadFloat3(&vector);
		XMVECTOR r = XMLoadFloat3(&m_right);
		XMVECTOR p = XMLoadFloat3(&m_position);
		XMStoreFloat3(&m_position, XMVectorMultiply(s, r));

		// mPosition += d*mLook
		XMVECTOR l = XMLoadFloat3(&m_target);
		XMStoreFloat3(&m_position, XMVectorMultiply(s, l));
		XMStoreFloat3(&m_position, p);

		//Set Translation matrix
		Transform::SetPosition(m_position);
	}

	void Camera::UpdateProjection()
	{
		//Update the Projection Matrix
		XMMATRIX projXMMat = XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_nearZ, m_farZ);
		XMStoreFloat4x4(&m_projection, projXMMat);
	}

	void Camera::UpdateView()
	{
		//XMStoreFloat4x4(&m_view,XMMatrixLookAtLH(XMLoadFloat3(&m_position), XMLoadFloat3(&m_target), XMLoadFloat3(&m_up)));
		//Update the View Matrix
		XMVECTOR R = XMLoadFloat3(&m_right);
		XMVECTOR U = XMLoadFloat3(&m_up);
		XMVECTOR L = XMLoadFloat3(&m_target);
		XMVECTOR P = XMLoadFloat3(&m_position);

		// Keep camera's axes orthogonal to each other and of unit length.
		L = XMVector3Normalize(L);
		U = XMVector3Normalize(XMVector3Cross(L, R));

		// U, L already ortho-normal, so no need to normalize cross product.
		R = XMVector3Cross(U, L);

		// Fill in the view matrix entries.
		float x = -XMVectorGetX(XMVector3Dot(P, R));
		float y = -XMVectorGetX(XMVector3Dot(P, U));
		float z = -XMVectorGetX(XMVector3Dot(P, L));
	
		XMStoreFloat3(&m_right, R);
		XMStoreFloat3(&m_up, U);
		XMStoreFloat3(&m_target, L);

		m_view(0, 0) = m_right.x;
		m_view(1, 0) = m_right.y;
		m_view(2, 0) = m_right.z;
		m_view(3, 0) = x;

		m_view(0, 1) = m_up.x;
		m_view(1, 1) = m_up.y;
		m_view(2, 1) = m_up.z;
		m_view(3, 1) = y;

		m_view(0, 2) = m_target.x;
		m_view(1, 2) = m_target.y;
		m_view(2, 2) = m_target.z;
		m_view(3, 2) = z;

		m_view(0, 3) = 0.0f;
		m_view(1, 3) = 0.0f;
		m_view(2, 3) = 0.0f;
		m_view(3, 3) = 1.0f;
	}

	Camera::~Camera()
	{

	}
}