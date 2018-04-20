#define _CUSTOM_INPUT_LAYOUT
#include "Core.h"
#include "PrimitiveGeometry.h"
#include "RenderStateManager.h"


using namespace DirectX;
class Application : public EngineSpace::Core
{
	public:
	
		Application(LPCWSTR windowTitle, HINSTANCE hInstance) : Core(windowTitle,hInstance)
		{
			
		}

		void Start()
		{
		
			//Shape Demo
			EngineSpace::GameObject box = EngineSpace::Shape::Box();
//			box.SetPosition(XMFLOAT3(5.0f, 0.0f, 0.0f));
			//EngineSpace::GameObject hill = EngineSpace::Shape::CreateHills(100,100,1000,1000);
			EngineSpace::RenderStateManager::AddToRenderObjectList(&box);
		}

		void Update(float dt)
		{

			// Fault here Input class is faulty 
			if (EngineSpace::gp_InputH->GetKeyUp(VK_RIGHT))
			{
				EngineSpace::gp_MainCameraH->SetPosition(XMFLOAT3(50.0f, 0.0f, 0.0f));
				EngineSpace::gp_MainCameraH->UpdateView();
			}
		}

		virtual ~Application()
		{

		}

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR pCmdLine, int nCmdShow)
{
	// Prevents multiple instances of this process
	HANDLE hMutex;
	CoInitialize(NULL);
	hMutex = CreateMutex(NULL, FALSE, L"BoxDemo");
	// if mutex creation fails then handle already exist , display error msg and exit
	if (hMutex == NULL || (GetLastError() == ERROR_ALREADY_EXISTS))
	{
		CloseHandle(hMutex);
		MessageBox(NULL, L"An instance of the application is already running in the background, please close the instance first"
				,L"Error", MB_ICONWARNING | MB_OK);

		return 1;
	}

	EngineSpace::gp_CoreH.reset(new Application(L"BoxDemo", hInstance));
	
	EngineSpace::gp_MainCameraH.reset(new EngineSpace::Camera(XMFLOAT3(0.0f, 0.0f, -5.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f)));
	EngineSpace::gp_CoreH->Init();
	EngineSpace::gp_CoreH->Run();

	EngineSpace::gp_CoreH->ShutDown();

	 EngineSpace::gp_CoreH.reset();
	
	 CloseHandle(hMutex);
	 CoUninitialize();

	 return 0;

}