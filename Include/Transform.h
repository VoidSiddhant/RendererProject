#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Util.h"
//Transform Stub.......................
namespace EngineSpace
{
	class Transform
	{
	public:
		Transform();
		virtual ~Transform();

		//Transformation Methods
		void Translate(DirectX::XMFLOAT3 translationVector);
		void Rotate();
		void Scale();


	private:
		DirectX::XMFLOAT4X4 m_worl4x4;
	};
}

#endif // !_TRANSFORM_H



