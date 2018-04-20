#include "Transform.h"

namespace EngineSpace
{

	Transform::Transform()
	{
		DirectX::XMStoreFloat4x4(&m_matrix_translation,DirectX::XMMatrixIdentity());
		DirectX::XMStoreFloat4x4(&m_matrix_rotation, DirectX::XMMatrixIdentity());
		DirectX::XMStoreFloat4x4(&m_matrix_scalar, DirectX::XMMatrixIdentity());
	}


	Transform::~Transform()
	{

	}

	void Transform::Translate(const DirectX::XMFLOAT3& translationVector)
	{
		// or load in xmvector both values add and store back in xmfloat also store in matrix
		DirectX::XMVECTOR vec = DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&m_position), DirectX::XMLoadFloat3(&m_position));
		DirectX::XMStoreFloat3(&m_position, vec);
		DirectX::XMStoreFloat4x4(&m_matrix_translation,DirectX::XMMatrixTranslation(m_position.x,m_position.y,m_position.z));
	}

	void Transform::SetPosition(const DirectX::XMFLOAT3& positionVector)
	{
		m_position = positionVector;
		DirectX::XMStoreFloat4x4(&m_matrix_translation,DirectX::XMMatrixTranslation(m_position.x, m_position.y, m_position.z));
	}

	void Transform::SetRotation(const DirectX::XMFLOAT3& vector)
	{
		// Store angles of each axis
		m_rotationAxis = vector;
		DirectX::XMStoreFloat4x4(&m_matrix_rotation,DirectX::XMMatrixRotationRollPitchYawFromVector(DirectX::XMLoadFloat3(&m_rotationAxis)));
	}

	void Transform::SetScale(const DirectX::XMFLOAT3& scaleVector)
	{
		m_scale = scaleVector;
		DirectX::XMStoreFloat4x4(&m_matrix_scalar,DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z));
	}

}
