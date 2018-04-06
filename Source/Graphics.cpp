#define _CRT_SECURE_NO_WARNINGS
#include "Graphics.h"
#include "Core.h"
#include "BufferManager.h"
#include "Camera.h"


namespace EngineSpace
{
	Graphics::Graphics()
	{
		logFile = std::fopen("EngineStartupLog.txt", "w");
		std::fputs("Graphics Init\n", logFile);
		std::fclose(logFile);

		lp_d3dDevice = 0;
		lp_d3dContext = 0;
		renderTargetView = 0;
		depthStencilView = 0;
		swapChain = 0;
	}

	Graphics::~Graphics()
	{
		BufferManager::FreeBuffers();

		ReleaseCOM(m_fxWorldViewProj)
		ReleaseCOM(m_tech)
		ReleaseCOM(m_effect)
				 
				 
		ReleaseCOM(swapChain)
		ReleaseCOM(renderTargetView)
		ReleaseCOM(depthStencilView)
		ReleaseCOM(m_inputLayout)
				
		ReleaseCOM(lp_d3dDevice)
		ReleaseCOM(lp_d3dContext)
				  
	}

	void Graphics::Init()
	{
		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL fl = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;
		//Create device and context interfaces using the D3D11CreateDevice
		//lp_d3dContext is the immediate context , there is also a deffered context which is required/used in case of multithreaded
		//operation
		HRESULT hr = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, D3D11_CREATE_DEVICE_DEBUG,&fl,1, D3D11_SDK_VERSION,
										&lp_d3dDevice, &featureLevel, &lp_d3dContext);

		const char* dname = "Graphics Context";
		lp_d3dContext->SetPrivateData(WKPDID_D3DDebugObjectName,sizeof(dname) -1,(void*)dname);

		const char* dname2 = "Graphics Device";
		lp_d3dDevice->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(dname2) -1, (void*)dname2);

		if (FAILED(hr))
		{
			MessageBox(gp_CoreH->GetHWND(), L"Device Creation Failed", L"Error", MB_OK);
		}

		if (featureLevel != D3D_FEATURE_LEVEL_11_0)
		{
			MessageBox(gp_CoreH->GetHWND(), L"Feature level DirectX 11 not supported", NULL, MB_OK);
		}

		//Now we can use the newly acquired interface to do bunch of Direct3D stuff
		//Check for multisample quality support(Anti-Aliasing)
		UINT aaCheck = 0;
		lp_d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 8, &aaCheck);
		//TODO - Print the Value in a file............................................................TODO

		//Create Swap Chain.............................................................................................
		//Fill out Swap Chain Desc Structure
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		swapChainDesc.BufferCount = 1;
		
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;
		swapChainDesc.BufferDesc.Width = SCREEN_WIDTH;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_CENTERED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.Flags = 0;
		swapChainDesc.OutputWindow = gp_CoreH->GetHWND();
		swapChainDesc.SampleDesc.Count = 8;
		swapChainDesc.SampleDesc.Quality = aaCheck-1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Windowed = true;

		//Swap Chain interface (IDXGISwapChain) is created through an IDXGIFactory instance.
		//We need to acquire the IDXGIFactory instance for this device , this is done by proceeding through the
		//following series of COM queries.
		IDXGIDevice* dxgiDevice = 0;
		lp_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
		
		IDXGIAdapter* dxgiAdapter = 0;
		dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);

		IDXGIFactory* dxgiFactory = 0;
		dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

		//Now create the swap chain
	
		dxgiFactory->CreateSwapChain(lp_d3dDevice, &swapChainDesc, &swapChain);

		//Release all the acquired COM interface , not needed anymore
		dxgiDevice->Release();
		dxgiAdapter->Release();
		dxgiFactory->Release();

		//In Direct3D we dont bind a resource to a pipeline stage directly , instead we must create a resource view to
		//that resource and bind the view to the pipeline stage.In order to bind the back buffer (resource) to our Output
		//Merger Stage (pipeline) , we create a render target view (resource view) to the back buffer.

		ID3D11Texture2D* backBuffer;
		//Obtain pointer to the swap chains back buffer
		swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
		 hr = lp_d3dDevice->CreateRenderTargetView(backBuffer, 0, &renderTargetView);
		if (FAILED(hr))
		{
			MessageBox(gp_CoreH->GetHWND(), L"Failed to create Render target view", L"OOOOPS", MB_OK);
		}
		backBuffer->Release();

		//We now need to create the depth/stencil buffer , which is just a 2D texture that stores the depth information
		//To create a texture , we need to fill out a D3D11_TEXTURE2D_DESC structure describing the texture to create
		// and then call the ID3D11Device::CreateTexture2D method.
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.Height = SCREEN_HEIGHT;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.MiscFlags = 0;
		depthStencilDesc.SampleDesc.Count = 8;
		depthStencilDesc.SampleDesc.Quality = aaCheck-1;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.Width = SCREEN_WIDTH;
		//Create the Depth/Stencil Buffer
		ID3D11Texture2D* depthStencilBuffer;
		lp_d3dDevice->CreateTexture2D(&depthStencilDesc, 0, &depthStencilBuffer);

		//Create Depth/Stencil Resource View
	
		lp_d3dDevice->CreateDepthStencilView(depthStencilBuffer, 0, &depthStencilView);

		//Bind the RenderTargetView and DepthStencilView to the Output Merger Stage of the pipeline , which completes the
		//final step of binding resource views to the pipeline
		lp_d3dContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

		//Set the viewport
		D3D11_VIEWPORT vp;
		vp.TopLeftX = 0.0f;
		vp.TopLeftY = 0.0f;
		vp.Width = static_cast<float>(SCREEN_WIDTH);
		vp.Height = static_cast<float>(SCREEN_HEIGHT);
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;

		lp_d3dContext->RSSetViewports(1, &vp);
	}

	void Graphics::BuildFX()
	{
		UINT shaderFlags = 0;
#if defined(DEBUG) ||defined(_DEBUG)
		shaderFlags = D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif
	
		HRESULT hr = D3DX11CreateEffectFromFile(L"x64/Debug/Color.cso", shaderFlags, lp_d3dDevice, &m_effect);

		m_tech = m_effect->GetTechniqueByName("ColorTech");
		
		m_fxWorldViewProj = m_effect->GetVariableByName("gWorldViewProj")->AsMatrix();
		
	}

	void Graphics::CreateInputLayout()
	{
		//Set Input Element structure Description (vertex structure used for rendering)
		D3D11_INPUT_ELEMENT_DESC inputDesc[] = 
		{
			{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
			{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}
		};

		//Get Pass Description for InputSignature
		D3DX11_PASS_DESC passDesc;
		m_tech->GetPassByIndex(0)->GetDesc(&passDesc);
		lp_d3dDevice->CreateInputLayout(inputDesc, 2, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &m_inputLayout);

	}

	void Graphics::SetInputLayout(const ID3D11InputLayout* input)
	{
		lp_d3dContext->IASetInputLayout(const_cast<ID3D11InputLayout*>(input));
	}

	void Graphics::Draw()
	{
		float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		//Clear the back buffer
		lp_d3dContext->ClearRenderTargetView(renderTargetView,(const float*) color);
		//Clear the depth buffer and stencil buffer
		lp_d3dContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		
		//Draw Calls here.............................
		
		//Set Index and Vertex Buffers
		if(BufferManager::GetIndexCount() != 0)
			BufferManager::IASetBuffers(lp_d3dContext);

		//Set input layout
		lp_d3dContext->IASetInputLayout(m_inputLayout);
		//Set Primitive Topology
		lp_d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		//Draw
		DirectX::XMMATRIX worldViewProj = DirectX::XMMatrixIdentity() * gp_MainCameraH->GetXM_View() * gp_MainCameraH->GetXM_Projection();
		//Set Effect Variable
		m_fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

		D3DX11_TECHNIQUE_DESC techDesc;
		m_tech->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; p++)
		{
			m_tech->GetPassByIndex(0)->Apply(0, lp_d3dContext);
		
			//Geometery Index Count
			lp_d3dContext->DrawIndexed(BufferManager::GetIndexCount(), 0,0);
		}
		
		//Swap the Back and front buffers
		swapChain->Present(0, 0);
	}
}