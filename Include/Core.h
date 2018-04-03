#ifndef _CORE_H
#define _CORE_H

#include"Util.h"

//Windows Procedure Function Prototype
LRESULT CALLBACK WndProc(HWND,UINT, WPARAM, LPARAM);
namespace EngineSpace
{
	//Prototyping classes
	class Graphics;
	class Timer;
	class Camera;
	class Input;
	

	class Core
	{

	public:
		Core(LPCWSTR windowTitle, HINSTANCE hInstance);
		void Init();
		int Run();
		void ShutDown();
		void UpdateFrame();

		//Accessor methods
		HWND GetHWND()  {
			return m_hwnd;
		}

		HINSTANCE GetAppInstance() const {
			return m_hInstance;
		}

		Graphics* GetGraphics() const {
			return m_graphics;
		}
		
		Camera* GetCamera() const {
			return m_camera;
		}

		//Message Handler for this Application
		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
		~Core();

	private :
		//Methods
		
		void InitWindow();
		void InitGraphics();

	
		//Variables
		HWND m_hwnd;
		HINSTANCE m_hInstance;
		bool exitAppCondition;
		Graphics* m_graphics;
		Camera* m_camera;
		Input* m_input;
		LPCWSTR m_title;
		Timer* m_timer;
	};
}
//Highlighted text are linked/resolved

#endif
