#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "Util.h"


//Graphics Stub................................
namespace EngineSpace
{
	class Graphics
	{
	public:
		Graphics();
		~Graphics();
		void Init();
		void Draw();
		
		void BuildFX();
		void CreateInputLayout();
		void SetInputLayout(const ID3D11InputLayout* input);

		ID3D11Device* GetDevice() const {
			return lp_d3dDevice;
		}

		ID3D11DeviceContext* GetDeviceContext() const {
			return lp_d3dContext;
		}

	public:
		ID3D11Device * lp_d3dDevice;
		ID3D11DeviceContext* lp_d3dContext;
		ID3D11RenderTargetView* renderTargetView;
		ID3D11DepthStencilView* depthStencilView;
		IDXGISwapChain* swapChain;

		//Effect
		LPD3D11EFFECT m_effect;
		ID3DX11EffectTechnique* m_tech;
		ID3DX11EffectMatrixVariable* m_fxWorldViewProj;
		ID3D11InputLayout* m_inputLayout;
		
	};

}

#endif // !_GRAPHICS_H
