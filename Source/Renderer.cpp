#include "Renderer.h"
#include "BufferManager.h"
#include "RenderStates.h"

namespace EngineSpace
{
	Renderer::Renderer()
	{
	}


	Renderer::~Renderer()
	{
	}

	void Renderer::Draw()
	{
		//FAULT HERE...................********************zzzzzzzzzzzzzzzzzzzzzzzzzz.....................................
		DirectX::XMMATRIX worldViewProj = DirectX::XMMatrixIdentity() * gp_MainCameraH->GetXM_View() * gp_MainCameraH->GetXM_Projection();
		//..............................................................zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz..............
		//Set Effect Variable
		//Get WorldViewProj buffer from the shaders constant buffers
		RenderStateManager::GetEffectVariable("gWorldViewProj")->SetMatrix(reinterpret_cast<float*>(&worldViewProj));


		D3DX11_TECHNIQUE_DESC techDesc;
		RenderStateManager::GetEffectTechnique()->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; p++)
		{
			RenderStateManager::GetEffectTechnique()->GetPassByIndex(0)->Apply(0, gp_RendererH->GetDeviceContext());

			//Geometery Index Count Change this
			gp_RendererH->GetDeviceContext()->DrawIndexed(BufferManager::GetIndexCount(), 0, 0);
		}
	}

};

