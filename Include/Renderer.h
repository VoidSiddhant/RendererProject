#ifndef _RENDERER_H
#define _RENDERER_H

#include "Util.h"
#include "Shader.h"
#include "Transform.h"

namespace EngineSpace
{
	class Renderer : public Transform
	{
	public:
		Renderer();
		~Renderer();

		void Draw();
	private:
		
	};
};

#endif // !_RENDERER_H

