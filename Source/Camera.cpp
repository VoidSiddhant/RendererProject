#include "Camera.h"

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
		m_target = XMFLOAT3(0.0f, 0.0f, 0.0f);;
		//Set Projection Properties
		m_nearZ = 1.0f;
		m_farZ = 1000.0f;
		m_fov = 0.25f * MATHF_PI;
		m_aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
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
		//Set Projection Properties
		m_nearZ = 1.0f;
		m_farZ = 1000.0f;
		m_fov = 0.25f * MATHF_PI;
		m_aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	}


	void Camera::SetPosition(const XMFLOAT3& posVector)
	{
		m_position = posVector;
	}

	void Camera::SetRotation(const XMFLOAT3& value)
	{
		
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

	void Camera::UpdateProjection()
	{
		//Update the Projection Matrix
		XMMATRIX projXMMat = XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_nearZ, m_farZ);
		XMStoreFloat4x4(&m_projection, projXMMat);

	}

	void Camera::UpdateView()
	{
		//Update the View Matrix
		XMMATRIX viewXMMat =  XMMatrixLookAtLH(XMLoadFloat3(&m_position), XMLoadFloat3(&m_target), XMLoadFloat3(&m_up));
		XMStoreFloat4x4(&m_view, viewXMMat);
	}

	Camera::~Camera()
	{

	}
}