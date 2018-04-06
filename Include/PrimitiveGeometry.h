#ifndef _PRIMITIVE_GEOMETERY_H
#define _PRIMITIVE_GEOMETERY_H


#include"GameObject.h"

namespace EngineSpace
{
	class PrimitiveGeometry
	{
	public:
		PrimitiveGeometry();
		~PrimitiveGeometry();

		static GameObject CreateBox();
		static GameObject::Mesh CreateGrid();
	
	private:

	};
}

#endif // !_PRIMITIVE_GEOMETERY_H


