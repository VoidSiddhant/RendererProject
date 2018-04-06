#ifndef _UTIL_H
#define _UTIL_H

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <d3d11.h>
#include "../FX11/d3dx11effect.h"

#pragma comment(lib,"Effects11d.lib")
#pragma comment(lib,"d3d11.lib")
#include<DirectXMath.h>

#define WIN32_LEAN_AND_MEAN
#include<windows.h>

#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }



namespace EngineSpace
{

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 800
#endif // !SCREEN_WIDTH

#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 640
#endif // !SCREEN_HEIGHT

# define MATHF_PI	3.14159265358979323846f  /* pi */
	
	_declspec(selectany) std::FILE* logFile;

	class Core;
	class Camera;
	class Input;
	class Graphics;
	class Timer;

	
	//TODO : Smart Pointers 
	_declspec(selectany) extern Input* gp_InputH ;
	_declspec(selectany) extern Graphics* gp_RendererH ;
	_declspec(selectany) extern Timer* gp_MainTimerH ;
	_declspec(selectany) extern Camera* gp_MainCameraH ;
	_declspec(selectany) extern Core* gp_CoreH;
}
#endif // !_UTIL_H