#ifndef _BUFFER_MANAGER_H
#define _BUFFER_MANAGER_H

#include "Util.h"
#include "Vertex.h"

namespace EngineSpace
{
	class BufferManager
	{
	public:
		BufferManager();
		~BufferManager();

		static void AddToVertexIndexList(std::vector<Vertex_CPT>::iterator vBegin
										, std::vector<Vertex_CPT>::iterator vEnd
										, std::vector<UINT>::iterator iBegin
										, std::vector<UINT>::iterator iEnd);

		static void BuildGeometryBuffer(ID3D11Device* device);
		static void IASetBuffers(ID3D11DeviceContext* deviceContext);
		
		static const UINT GetIndexCount()
		{
			return (UINT)indexList.size();
		}

		static ID3D11Buffer* VertexBuffer() {
			return m_vertexBuffer;
		}

		static  ID3D11Buffer* IndexBuffer() {
			return m_indexBuffer;
		}

		static void FreeBuffers();

	private:
		static ID3D11Buffer* m_vertexBuffer;
		static ID3D11Buffer* m_indexBuffer;
		static std::vector<Vertex_CPT> vertexList;
		static std::vector<UINT> indexList;
	};
	
};
#endif // !_BUFFER_MANAGER_H

