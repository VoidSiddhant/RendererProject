#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Vertex.h"
#include "Transform.h"

namespace EngineSpace
{
	class GameObject : public Transform
	{
	public:
		typedef struct MeshData
		{
			std::vector<Vertex_CPT> vertexData;
			std::vector<UINT> indexData;
		} Mesh;

		GameObject();
		~GameObject();

		Mesh mesh;

	private:

	};
}
#endif // !_GAMEOBJECT_H