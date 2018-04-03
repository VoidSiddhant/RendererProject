#ifndef _CAMERA_H
#define _CAMERA_H

#include"Util.h"
namespace EngineSpace
{
	//////////////////////////////////////////////////////////////
	///////////// CAMERA IMPLEMENTATION //////////////////////////
	/// Basic Implementation of a camera with fixed projetion ///
	/// and view matrix , only rotation of camera is possible ///
	/// around a fixed target,with fixed distance z			  ///
	//////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////
	class Camera
	{
	public:
		Camera();
		Camera(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& target, const DirectX::XMFLOAT3& up);
		~Camera();
		void Update();

		//Setter Methods
		void SetPosition(const DirectX::XMFLOAT3& posVector);
		void SetRotation(const DirectX::XMFLOAT3& rotationVector);
		void SetFoV(const float& fov);
		void SetUpDirection(const DirectX::XMFLOAT3& upVector);
		void SetTarget(const DirectX::XMFLOAT3& targetVector);

		//Getter Methods
		XMMATRIX GetXM_Projection() const {
			return XMLoadFloat4x4(&mProjection);
		}

		XMMATRIX GetXM_View() const {
			return XMLoadFloat4x4(&mView);
		}

	private:
		// Camera coordinate system with coordinates relative to world space
		//Change it to XMFLOAT3
		DirectX::XMVECTOR mPosition;
		DirectX::XMVECTOR mRight;
		DirectX::XMVECTOR mUp;
		DirectX::XMVECTOR mLook;

		// View Frustum Properties
		float mNearZ;
		float mFarZ;
		float mAspect;
		float mFovY;
		float mNearWindowHeight;
		float mFarWindowHeight;

		//View and Projection Matrix
		DirectX::XMFLOAT4X4 mView, mProjection;
		//Remove this from Camera Class
		DirectX::XMFLOAT4X4 mWorld;
	};
}
#endif