#include "GameObject.h"
namespace EngineSpace
{

	GameObject::GameObject()
	{
		m_position = { 0.0f,0.0f,0.0f };
		m_rotationAxis = { 0.0f,0.0f,0.0f };
		m_scale = { 0.0f,0.0f,0.0f };

		
	}

	GameObject::~GameObject()
	{

	}

}
