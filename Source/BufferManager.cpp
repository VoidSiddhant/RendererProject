#include "BufferManager.h"
#include "Core.h"
#include "Graphics.h"

namespace EngineSpace
{
	std::vector<UINT> BufferManager::indexList = {};
	std::vector<Vertex_CPT> BufferManager::vertexList = {};
	ID3D11Buffer* BufferManager::m_indexBuffer = 0;
	ID3D11Buffer* BufferManager::m_vertexBuffer = 0;

	BufferManager::BufferManager()
	{
		
	}


	BufferManager::~BufferManager()
	{

	}

	void BufferManager::AddToVertexIndexList(std::vector<Vertex_CPT>::iterator vBegin , std::vector<Vertex_CPT>::iterator vEnd, std::vector<UINT>::iterator iBegin, std::vector<UINT>::iterator iEnd)
	{
		vertexList.insert(vertexList.end(), vBegin, vEnd);
		indexList.insert(indexList.end(), iBegin, iEnd);

		//Change this call
		BufferManager::BuildGeometryBuffer(gp_RendererH->GetDevice());
	}

	void BufferManager::BuildGeometryBuffer(ID3D11Device* device)
	{
		D3D11_BUFFER_DESC vDesc;
		vDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vDesc.ByteWidth = sizeof(Vertex_CPT) *8;
		vDesc.CPUAccessFlags = 0;
		vDesc.MiscFlags = 0;
		vDesc.StructureByteStride = 0;
		vDesc.Usage = D3D11_USAGE_IMMUTABLE;
		
		D3D11_SUBRESOURCE_DATA vBufferData;
		vBufferData.pSysMem = &vertexList[0];
		vBufferData.SysMemPitch = NULL;
		vBufferData.SysMemSlicePitch = NULL;

		//Create Vertex Buffer
		device->CreateBuffer(&vDesc, &vBufferData, &m_vertexBuffer);

		D3D11_BUFFER_DESC iDesc;
		iDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		iDesc.ByteWidth = sizeof(UINT) * 36;
		iDesc.CPUAccessFlags = 0;
		iDesc.MiscFlags = 0;
		iDesc.StructureByteStride = 0;
		iDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA iBufferData;
		iBufferData.pSysMem = &indexList[0];
		iBufferData.SysMemPitch = NULL;
		iBufferData.SysMemSlicePitch = NULL;

		//Create Index Buffer
		device->CreateBuffer(&iDesc, &iBufferData, &m_indexBuffer);

	}

	void BufferManager::IASetBuffers(ID3D11DeviceContext* deviceContext)
	{
		UINT stride = sizeof(Vertex_CPT);
		UINT offset = 0;
		deviceContext->IASetVertexBuffers(0,1,&m_vertexBuffer,&stride,&offset);
		deviceContext->IASetIndexBuffer(m_indexBuffer,DXGI_FORMAT_R32_UINT,0);
	}

	void BufferManager::FreeBuffers()
	{
		ReleaseCOM(m_vertexBuffer);
		ReleaseCOM(m_indexBuffer);
	}
};

