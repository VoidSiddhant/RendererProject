#include "Core.h"
#include "PrimitiveGeometry.h"

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
	Application* app = new Application(L"BoxDemo", hInstance);

	app->Init();
	app->Run();
	app->ShutDown();

	delete app;
	return 0;

}