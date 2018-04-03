#include"Input.h"

namespace EngineSpace
{
	Input::Input()
	{
		//Try ZeroMemory Method instead of looping
		//Set 0 to all the key states which indicates unpressed
		for (int i = 0; i < 256; i++)
		{
			keyState[i] = false;
		}
	}

	Input::~Input()
	{

	}
	void Input::SetKeyDown(UINT virtualKeyCode)
	{
		keyState[virtualKeyCode] = true;
	}
	void Input::SetKeyUp(UINT virtualKeyCode)
	{
		keyState[virtualKeyCode] = false;
	}
	bool Input::GetKeyDown(UINT keyCode)
	{
		return keyState[keyCode];
	}
	bool Input::GetKeyUp(UINT keyCode)
	{
		return keyState[keyCode];
	}
}