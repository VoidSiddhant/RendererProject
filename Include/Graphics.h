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

		ID3D11Device* GetDevice() const {
			return lp_d3dDevice;
		}

		ID3D11DeviceContext* GetDeviceContext() const {
			return lp_d3dContext;
		}

	public:
		ID3D11Device * lp_d3dDevice;
		ID3D11DeviceContext* lp_d3dContext;
		IDXGISwapChain* swapChain;
		ID3D11RenderTargetView* renderTargetView;
		ID3D11DepthStencilView* depthStencilView;
	};

}

#endif // !_GRAPHICS_H
