#ifndef _CAMERA_H
#define _CAMERA_H

#include "Transform.h"


namespace EngineSpace
{
	//////////////////////////////////////////////////////////////
	///////////// CAMERA IMPLEMENTATION //////////////////////////
	/// Basic Implementation of a camera with fixed projetion ///
	/// and view matrix , only rotation of camera is possible ///
	/// around a fixed target,with fixed distance z			  ///
	//////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////
	class Camera : public Transform
	{
	public:
		Camera();
		Camera(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& target, const DirectX::XMFLOAT3& up);
		virtual ~Camera();
		void UpdateProjection();
		void UpdateView();

		//Transformation
		void SetPosition(const DirectX::XMFLOAT3& posVector);
		void SetRotation(const DirectX::XMFLOAT3& rotationVector);
		//View
		void SetLookDirection(const DirectX::XMFLOAT3& targetVector);
		void SetUpDirection(const DirectX::XMFLOAT3& upVector);
		//Call Update Projection() after calling below methods
		void SetFoV(const float fov);
		void SetAspect(const float ratio);
		void SetNearPlane(const float zDistance);
		void SetFarPlane(const float fDistance);

		//Getter Methods
		DirectX::XMMATRIX GetXM_Projection() const {
			return XMLoadFloat4x4(&m_projection);
		}

		DirectX::XMMATRIX GetXM_View() const {
			return XMLoadFloat4x4(&m_view);
		}

		//Camera Controller
		void Translate(const DirectX::XMFLOAT3& translateVector);
	
	
	private:
	
		
		//View Properties
		DirectX::XMFLOAT3 m_right;
		DirectX::XMFLOAT3 m_up;
		DirectX::XMFLOAT3 m_target;

		//Projection Properties
		float m_fov,m_aspect,m_nearZ,m_farZ;

		// View Frustum Properties
		float mNearWindowDistance;
		float mFarWindowDistance;
		float mNearWindowHeight;
		float mFarWindowHeight;

		//View and Projection Matrix
		DirectX::XMFLOAT4X4 m_view, m_projection;
	};
}
#endif