#include"Timer.h"
#include "Core.h"

namespace EngineSpace
{

	Timer::Timer()
	{
		totalTime = 0;
		fpsTimeElapsed = 0;
		frameCount = 0;
		fps = 100.0f;
		currCounts = 0;
		prevCounts = 0;
		//Query the frequency of the performance counter
		_int64 countsPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		QueryPerformanceCounter((LARGE_INTEGER*)&prevCounts);
		secPerCount = 1.0f / countsPerSec;
	}

	Timer::~Timer()
	{
		
	}


	void Timer::Tick()
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currCounts);
		deltaTime = (currCounts - prevCounts) * secPerCount;
		prevCounts = currCounts;
		
		//Make sure that delta time does not become negative
		if (deltaTime < 0.0f)
		{
			deltaTime = 0.0f;
		}

		frameCount++;
		fpsTimeElapsed += deltaTime;
		if (fpsTimeElapsed >= 1.0f)
		{
			fps = frameCount;
			fpsTimeElapsed = 0.0f;
			frameCount = 0;
		}
		
		//Calculate Total time
		totalTime += deltaTime;
		std::wostringstream woss;
		woss << L"FPS " << fps;
	
		SetWindowText(gp_Core->GetHWND(),woss.str().c_str());
	}
}