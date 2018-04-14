#ifndef _PRIMITIVE_GEOMETERY_H
#define _PRIMITIVE_GEOMETERY_H


#include"GameObject.h"

namespace EngineSpace
{
	class Shape
	{
	public:
		Shape();
		~Shape();

		static GameObject Box();
		static GameObject CreateHills(float width, float depth, UINT m, UINT n);
	
	private:

	};
}

#endif // !_PRIMITIVE_GEOMETERY_H


