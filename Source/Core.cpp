#define _CRT_SECURE_NO_WARNINGS
#include"Core.h"
#include"Input.h"

#include"Camera.h"
#include "PrimitiveGeometry.h"
#include"GameObject.h"

#include"Timer.h"
#include"Graphics.h"
namespace EngineSpace
{
	//Constructor
	Core::Core(LPCWSTR windowTitle, HINSTANCE hInstance)
	{
	
		gp_RendererH = 0;
		gp_InputH = 0;
		gp_MainCameraH = 0;
//		gp_CoreH = this;
		m_title = windowTitle;
		m_hInstance = hInstance;
	
	}

	//TODO : Smart Pointer for camera
	void Core::Init()
	{
		this->InitWindow();
		this->InitGraphics();

		gp_InputH.reset(new Input());

		//Start Timer
		gp_MainTimerH.reset(new Timer());
		gp_MainCameraH->UpdateView();
		gp_MainCameraH->UpdateProjection();

		//Call Derived Start
		Start();
	}

	void Core::InitWindow()
	{
		WNDCLASS wc;
		ZeroMemory(&wc, sizeof(WNDCLASS));
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.hInstance = m_hInstance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.lpfnWndProc = WndProc;
		wc.hbrBackground = HBRUSH(COLOR_WINDOW);
		wc.hIcon = LoadIcon(0, IDI_APPLICATION);
		wc.lpszMenuName = 0;
		wc.lpszClassName = m_title;


		RegisterClass(&wc);

		m_hwnd = CreateWindow(m_title, m_title, WS_OVERLAPPEDWINDOW, 0, 0, SG_UTIL_SCREEN_WIDTH, SG_UTIL_SCREEN_HEIGHT, 0, 0, m_hInstance, NULL);
		if (!m_hwnd)
		{
			MessageBox(m_hwnd, L"Window Could Not Be Created", L"Error!!!", MB_OK);
		}
		ShowWindow(m_hwnd, SW_SHOW);
		UpdateWindow(m_hwnd);
	}

	void Core::InitGraphics()
	{
		gp_RendererH.reset(new Graphics());
		gp_RendererH->Init();
	}

	int Core::Run()
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

		while (!exitAppCondition)
		{
			if (PeekMessage(&msg, m_hwnd, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (msg.message == WM_QUIT)
			{
				exitAppCondition = true;
			}

			else
			{
	
				gp_MainTimerH->Tick();
				Update();
			}
		}
		
		return (int)msg.wParam;
	}


	void Core::Update()
	{
		if (gp_InputH->GetKeyDown(VK_ESCAPE))
		{
			MessageBox(m_hwnd, L"Hello", L"Caption", MB_OK);
			exitAppCondition = true;
		}
		Update(gp_MainTimerH->GetDeltaTime());

		gp_MainCameraH->UpdateProjection();
		gp_MainCameraH->UpdateView();
		gp_RendererH->Draw();
	}

	void Core::ShutDown()
	{


		DestroyWindow(m_hwnd);

		UnregisterClass(m_title, m_hInstance);
		m_hInstance = NULL;

		//Other Engine Objects
		gp_RendererH.reset();
		 gp_MainTimerH.reset();
		 gp_MainCameraH.reset();
		 gp_InputH.reset();

	}

	LRESULT CALLBACK Core::MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
	
		switch (msg)
		{
		case WM_KEYDOWN:
			gp_InputH->SetKeyDown((UINT)wParam);
			break;
		case WM_KEYUP:
			gp_InputH->SetKeyUp((UINT)wParam);
			break;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	//Destructor
	Core::~Core()
	{

	}

}

//Windows Procedure Function definition , redirect msg to the engine's message handler function
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
			// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return EngineSpace::gp_CoreH->MessageHandler(hwnd, msg, wParam, lParam);
		}
	}
}
