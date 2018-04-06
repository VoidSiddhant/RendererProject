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
		void Update();
		//Message Handler for this Application
		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
		virtual ~Core();
		//Startup Attachments
		virtual void Start() = 0;
		//Update Attachment
		virtual void Update(float dt) = 0;

		//Accessor methods
		HWND GetHWND()  {
			return m_hwnd;
		}

		HINSTANCE GetAppInstance() const {
			return m_hInstance;
		}


	private :
		//Init Methods		
		void InitWindow();
		void InitGraphics();

		//Variables
		HWND m_hwnd;
		HINSTANCE m_hInstance;
		bool exitAppCondition;
		LPCWSTR m_title;
	};
}
//Highlighted text are linked/resolved

#endif
