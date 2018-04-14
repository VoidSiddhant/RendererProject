
#include "Core.h"
#include "PrimitiveGeometry.h"
#include "RenderStates.h"

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
			//EngineSpace::GameObject box = EngineSpace::Shape::Box();
			EngineSpace::GameObject hill = EngineSpace::Shape::CreateHills(100,100,1000,1000);
			EngineSpace::RenderStateManager::AddToRenderObjectList(&hill);
		}

		void Update(float dt)
		{
			if (EngineSpace::gp_InputH->GetKeyDown(VK_RIGHT))
			{
				EngineSpace::gp_MainCameraH->Translate(XMFLOAT3(5.0f, 0.0f, 0.0f));
			}
		}

		virtual ~Application()
		{

		}

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR pCmdLine, int nCmdShow)
{
	EngineSpace::gp_CoreH.reset(new Application(L"BoxDemo", hInstance));
	
	EngineSpace::gp_MainCameraH.reset(new EngineSpace::Camera(XMFLOAT3(0.0f, 0.0f, -100.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f)));
	EngineSpace::gp_CoreH->Init();
	EngineSpace::gp_CoreH->Run();

	EngineSpace::gp_CoreH->ShutDown();

	 EngineSpace::gp_CoreH.reset();
	return 0;

}