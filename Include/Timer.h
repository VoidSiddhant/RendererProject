#ifndef _TIMER_H
#define _TIMER_H

#include"Util.h"
#include<sstream>

namespace EngineSpace
{
	class Timer
	{
	public:
		Timer();
		~Timer();
		void Tick();

		//Accesor Methods
		float GetDeltaTime() const {
			return deltaTime;
		}
		float GetTimeElapsed() const {
			return totalTime;
		}
	private:
		float deltaTime;
		float totalTime;
		_int64 currCounts,prevCounts;
		float secPerCount;
		int frameCount;
		float fps,fpsTimeElapsed;
	};
}

#endif // !_TIMER_H
