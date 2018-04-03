#include "../Include/Core.h"
#include "../Include/PrimitiveGeometry.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR pCmdLine, int nCmdShow)
{
	EngineSpace::Core* engineObj = new EngineSpace::Core(L"NewBegining",hInstance);

	if (!engineObj)
		return 0;

	//Initialize and run Engine
	engineObj->Init();
	engineObj->Run();

	engineObj->ShutDown();
	delete engineObj;
	engineObj = 0;

	return 0;

}