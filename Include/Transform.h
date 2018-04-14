#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <DirectXMath.h>
//World Space Controller Stub.......................
namespace EngineSpace
{
	class Transform
	{
	public:
		Transform();
		~Transform();

		//Transformation Methods
		virtual void Translate(const DirectX::XMFLOAT3& translationVector);
		virtual void SetPosition(const DirectX::XMFLOAT3& positionVector);
		virtual void SetRotation(const DirectX::XMFLOAT3& rotateVector);
		virtual void SetScale(const DirectX::XMFLOAT3& scaleVector);

		DirectX::XMMATRIX GetXM_Translation() const{
			return m_matrix_translation;
		}

		DirectX::XMMATRIX GetXM_Scalar() const 
		{
			return m_matrix_scalar;
		}

		DirectX::XMMATRIX GetXM_Rotation() const
		{
			return m_matrix_rotation;
		}
		DirectX::XMMATRIX GetXM_WorldTransform() const
		{
			return m_matrix_scalar * m_matrix_rotation * m_matrix_translation;
		}

		DirectX::XMFLOAT3 m_position;
		DirectX::XMFLOAT3 m_rotationAxis;
		DirectX::XMFLOAT3 m_scale;

	private:
		DirectX::XMMATRIX m_matrix_translation;
		DirectX::XMMATRIX m_matrix_rotation;
		DirectX::XMMATRIX m_matrix_scalar;

	};
};

#endif // !_TRANSFORM_H



