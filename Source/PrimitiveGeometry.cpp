#include "PrimitiveGeometry.h"
#include"BufferManager.h"

namespace EngineSpace
{
	Shape::Shape()
	{
		
	}

	Shape::~Shape()
	{

	}

	GameObject Shape::Box()
	{
		GameObject object;
		object.mesh.vertexData.resize(8);
		object.mesh.indexData.resize(36);

		//Fill Unity Length Cube
		object.mesh.vertexData = {
		{ DirectX::XMFLOAT3(-0.5f,-0.5f,-0.5f) ,DirectX::XMFLOAT4(1.0f,0.0f,0.0f,1.0f) },
		{ DirectX::XMFLOAT3(-0.5f,0.5f,-0.5f) ,DirectX::XMFLOAT4(0.0f,1.0f,1.0f,1.0f) },
		{ DirectX::XMFLOAT3(0.5f,0.5f,-0.5f) ,DirectX::XMFLOAT4(1.0f,0.0f,1.0f,1.0f) },
		{ DirectX::XMFLOAT3(0.5f,-0.5f,-0.5f) ,DirectX::XMFLOAT4(0.0f,1.0f,1.0f,0.0f) },
		{ DirectX::XMFLOAT3(-0.5f,-0.5f,0.5f) ,DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f) },
		{ DirectX::XMFLOAT3(-0.5f,0.5f,0.5f) ,DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f) },
		{ DirectX::XMFLOAT3(0.5f,0.5f,0.5f) ,DirectX::XMFLOAT4(1.0f,0.0f,1.0f,1.0f) },
		{ DirectX::XMFLOAT3(0.5f,-0.5f,0.5f) ,DirectX::XMFLOAT4(0.0f,1.0f,1.0f,1.0f) },
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

	

	GameObject Shape::CreateHills(float width, float depth, UINT m, UINT n)
	{
		//Create Grid
		GameObject object;

		UINT vertexCount = m * n;
		UINT faceCount = (m - 1)*(n - 1) * 2;
		//
		// Create the vertices.
		//

		float halfWidth = 0.5f*width;
		float halfDepth = 0.5f*depth;

		float dx = width / (n - 1);
		float dz = depth / (m - 1);

		float du = 1.0f / (n - 1);
		float dv = 1.0f / (m - 1);

		object.mesh.vertexData.resize(vertexCount);
		for (UINT i = 0; i < m; ++i)
		{
			float z = halfDepth - i * dz;
			for (UINT j = 0; j < n; ++j)
			{
				float x = -halfWidth + j * dx;

				object.mesh.vertexData[i*n + j].position = DirectX::XMFLOAT3(x, 0.0f, z);
				//object.mesh.vertexData[i*n + j].Normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
			//	object.mesh.vertexData[i*n + j].TangentU = DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f);

				// Stretch texture over grid.
				//object.mesh.vertexData[i*n + j].TexC.x = j * du;
				//object.mesh.vertexData[i*n + j].TexC.y = i * dv;
			}
		}

		Vertex_CPT* vertices = &object.mesh.vertexData[0];
		for (size_t i = 0; i < object.mesh.vertexData.size(); ++i)
		{
			DirectX::XMFLOAT3 p = object.mesh.vertexData[i].position;

			p.y = SG_UTIL_Math_RFGetHeight(p.x, p.z);

			vertices[i].position = p;

			// Color the vertex based on its height.
			if (p.y < -10.0f)
			{
				// Sandy beach color.
				vertices[i].color = DirectX::XMFLOAT4(1.0f, 0.96f, 0.62f, 1.0f);
			}
			else if (p.y < 5.0f)
			{
				// Light yellow-green.
				vertices[i].color = DirectX::XMFLOAT4(0.48f, 0.77f, 0.46f, 1.0f);
			}
			else if (p.y < 12.0f)
			{
				// Dark yellow-green.
				vertices[i].color = DirectX::XMFLOAT4(0.1f, 0.48f, 0.19f, 1.0f);
			}
			else if (p.y < 20.0f)
			{
				// Dark brown.
				vertices[i].color = DirectX::XMFLOAT4(0.45f, 0.39f, 0.34f, 1.0f);
			}
			else
			{
				// White snow.
				vertices[i].color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}

		//
		// Create the indices.
		//

		object.mesh.indexData.resize(faceCount * 3); // 3 indices per face

												// Iterate over each quad and compute indices.
		UINT k = 0;
		for (UINT i = 0; i < m - 1; ++i)
		{
			for (UINT j = 0; j < n - 1; ++j)
			{
				object.mesh.indexData[k] = i * n + j;
				object.mesh.indexData[k + 1] = i * n + j + 1;
				object.mesh.indexData[k + 2] = (i + 1)*n + j;

				object.mesh.indexData[k + 3] = (i + 1)*n + j;
				object.mesh.indexData[k + 4] = i * n + j + 1;
				object.mesh.indexData[k + 5] = (i + 1)*n + j + 1;

				k += 6; // next quad
			}
		}

		//Handle BufferManager
		BufferManager::AddToVertexIndexList(object.mesh.vertexData.begin(), object.mesh.vertexData.end(), object.mesh.indexData.begin(), object.mesh.indexData.end());

		return object;
	}


}