#include "Camera.h"

using namespace DirectX;

namespace EngineSpace
{
	Camera::Camera()
	{
		XMStoreFloat4x4(&mView, XMMatrixIdentity());
		XMStoreFloat4x4(&mProjection, XMMatrixIdentity());
		XMStoreFloat4x4(&mWorld, XMMatrixIdentity());

		mNearZ = 1.0f;
		mFarZ = 1000.0f;
		mFovY = 0.25f * MATHF_PI;
	}

	Camera::Camera(const XMFLOAT3& position, const XMFLOAT3& target, const XMFLOAT3& up)
	{
		XMStoreFloat4x4(&mView, XMMatrixIdentity());
		XMStoreFloat4x4(&mProjection, XMMatrixIdentity());
		XMStoreFloat4x4(&mWorld, XMMatrixIdentity());

		mPosition = XMLoadFloat3(&position);
		mUp = XMLoadFloat3(&up);
		mLook = XMLoadFloat3(&target);

		mNearZ = 1.0f;
		mFarZ = 1000.0f;

		mFovY = 0.25f * MATHF_PI;
	}


	void Camera::SetPosition(const XMFLOAT3& posVector)
	{
		mPosition = XMLoadFloat3(&posVector);
		
	}

	void Camera::SetRotation(const XMFLOAT3& value)
	{
		
	}

	void Camera::SetUpDirection(const DirectX::XMFLOAT3& value)
	{
		mUp = XMLoadFloat3(&value);
	}

	void Camera::SetTarget(const DirectX::XMFLOAT3& value)
	{
		mLook = XMLoadFloat3(&value);
	}

	void Camera::SetFoV(const float& fov)
	{
		mFovY = fov;
	}

	void Camera::Update()
	{
		//Update the View Matrix
		XMMATRIX viewXMMat =  XMMatrixLookAtLH(mPosition, mLook, mUp);
		XMStoreFloat4x4(&mView, viewXMMat);
		//Update the Projection Matrix
		XMMATRIX projXMMat = XMMatrixPerspectiveFovLH(mFovY, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, mNearZ, mFarZ);
		XMStoreFloat4x4(&mProjection, projXMMat);
	}

	Camera::~Camera()
	{

	}
}