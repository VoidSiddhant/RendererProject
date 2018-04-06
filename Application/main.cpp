#include "Core.h"
#include "Camera.h"
#include "PrimitiveGeometry.h"
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
			EngineSpace::GameObject boxObject = EngineSpace::PrimitiveGeometry::CreateBox();
		}

		void Update(float dt)
		{
			
		}

		virtual ~Application()
		{

		}

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR pCmdLine, int nCmdShow)
{
	EngineSpace::gp_CoreH = new Application(L"BoxDemo", hInstance);

	EngineSpace::gp_MainCameraH = new EngineSpace::Camera(XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));
	EngineSpace::gp_CoreH->Init();
	EngineSpace::gp_CoreH->Run();
	EngineSpace::gp_CoreH->ShutDown();

	delete EngineSpace::gp_CoreH;
	return 0;

}