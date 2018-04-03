#ifndef _INPUT_H
#define _INPUT_H

#include"Util.h"

namespace EngineSpace
{
	class Input
	{
	public:
		Input();
		~Input();

		//Engine Methods for setting virtual keys
		void SetKeyDown(UINT virtualKeyCode);
		void SetKeyUp(UINT virtualKeyCode);
		
		//User Methods for checking pressed/unpressed keys
		bool GetKeyDown(UINT keyCode);
		bool GetKeyUp(UINT keyCode);

	private:
		bool keyState[256];
		
	};
}

#endif // !_INPUT_H
