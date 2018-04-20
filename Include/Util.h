#ifndef _UTIL_H
#define _UTIL_H

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <memory>
#include <d3d11.h>
#include "../FX11/d3dx11effect.h"

#pragma comment(lib,"Effects11d.lib")
#pragma comment(lib,"d3d11.lib")
#include<DirectXMath.h>

#define WIN32_LEAN_AND_MEAN
#include<windows.h>

#include "Graphics.h"
#include "Core.h" 
#include "Timer.h"
#include "Input.h"
#include "Camera.h"

namespace EngineSpace
{

#ifndef SG_UTIL_SCREEN_WIDTH
#define SG_UTIL_SCREEN_WIDTH 800
#endif // !SCREEN_WIDTH

#ifndef SG_UTIL_SCREEN_HEIGHT
#define SG_UTIL_SCREEN_HEIGHT 640
#endif // !SCREEN_HEIGHT

//Safe Release
#define SG_UTIL_MEM_FREE(x) {if(x) { delete x; x = 0;}}
#define SG_UTIL_MEM_ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }

//Height Funtion
#define SG_UTIL_Math_RFGetHeight(x,z)	0.3f*( z*sinf(0.1f*x) + x*cosf(0.1f*z) )
#define SG_UTIL_MATH_RF_PI	3.14159265358979323846f  /* pi */

	class Core;
	class Camera;
	class Input;
	class Graphics;
	class Timer;
	
	_declspec(selectany) extern std::unique_ptr<Input> gp_InputH ;
	_declspec(selectany) extern std::unique_ptr<Graphics> gp_RendererH ;
	_declspec(selectany) extern std::unique_ptr<Timer> gp_MainTimerH ;
	_declspec(selectany) extern std::unique_ptr<Camera> gp_MainCameraH ;
	_declspec(selectany) extern std::unique_ptr<Core> gp_CoreH;



}
#endif // !_UTIL_H