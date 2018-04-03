#include "PrimitiveGeometry.h"
#include"BufferManager.h"

namespace EngineSpace
{
	PrimitiveGeometry::PrimitiveGeometry()
	{
		
	}

	PrimitiveGeometry::~PrimitiveGeometry()
	{

	}

	GameObject PrimitiveGeometry::CreateBox()
	{
		GameObject object;
		object.mesh.vertexData.resize(8);
		object.mesh.indexData.resize(36);

		//Fill Unity Length Cube
		object.mesh.vertexData = {
		{ XMFLOAT3(-0.5f,-0.5f,-0.5f) ,XMFLOAT4(1.0f,1.0f,1.0f,1.0f) },
		{ XMFLOAT3(-0.5f,0.5f,-0.5f) ,XMFLOAT4(1.0f,1.0f,1.0f,1.0f) },
		{ XMFLOAT3(0.5f,0.5f,-0.5f) ,XMFLOAT4(1.0f,1.0f,1.0f,1.0f) },
		{ XMFLOAT3(0.5f,-0.5f,-0.5f) ,XMFLOAT4(1.0f,1.0f,1.0f,1.0f) },
		{ XMFLOAT3(-0.5f,-0.5f,0.5f) ,XMFLOAT4(1.0f,1.0f,1.0f,1.0f) },
		{ XMFLOAT3(-0.5f,0.5f,0.5f) ,XMFLOAT4(1.0f,1.0f,1.0f,1.0f) },
		{ XMFLOAT3(0.5f,0.5f,0.5f) ,XMFLOAT4(1.0f,1.0f,1.0f,1.0f) },
		{ XMFLOAT3(0.5f,-0.5f,0.5f) ,XMFLOAT4(1.0f,1.0f,1.0f,1.0f) },
		};

		//Set Up Indices
		object.mesh.indexData =
		{
			//Front Facing
			0,1,2,
			0,2,3,

			//Back Facing
			4,5,6,
			4,5,7,

			//Left Facing
			4,5,1,
			4,1,0,

			//Right Facing
			7,3,2,
			7,2,6,

			//Top Facing
			3,1,5,
			3,5,5,

			//Bottom Facing
			7,4,0,
			7,0,3
		};

		//Add to the global Buffer
		std::vector<Vertex_CPT>::iterator vBegin = object.mesh.vertexData.begin();
		std::vector<Vertex_CPT>::iterator vEnd = object.mesh.vertexData.end();
		std::vector<UINT>::iterator iBegin = object.mesh.indexData.begin();
		std::vector<UINT>::iterator iEnd = object.mesh.indexData.end();
		BufferManager::AddToVertexIndexList(vBegin, vEnd, iBegin, iEnd);
		
		return object;
	}
}