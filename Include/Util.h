#ifndef _UTIL_H
#define _UTIL_H

#include<iostream>
#include<string>
#include<vector>
#include <d3d11.h>
#include "../FX11/d3dx11effect.h"

#pragma comment(lib,"Effects11d.lib")
#pragma comment(lib,"d3d11.lib")
#include<DirectXMath.h>

#define WIN32_LEAN_AND_MEAN
#include<windows.h>

using namespace DirectX;

namespace EngineSpace
{

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 800
#endif // !SCREEN_WIDTH

#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 640
#endif // !SCREEN_HEIGHT

# define MATHF_PI	3.14159265358979323846f  /* pi */
	
	class Core;

	_declspec(selectany) extern EngineSpace::Core* gp_Core = 0;
}
#endif // !_UTIL_H
