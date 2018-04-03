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
		m_graphics = 0;
		m_input = 0;
		m_camera = 0;
		gp_Core = this;
		m_title = windowTitle;
		m_hInstance = hInstance;
	
	}

	void Core::Init()
	{
		this->InitWindow();
		this->InitGraphics();

		m_input = new Input();
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
		wc.lpszClassName = L"NewBegining";


		RegisterClass(&wc);

		m_hwnd = CreateWindow(L"NewBegining", m_title, WS_OVERLAPPEDWINDOW, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, m_hInstance, NULL);
		if (!m_hwnd)
		{
			MessageBox(m_hwnd, L"Window Could Not Be Created", L"Error!!!", MB_OK);
		}
		ShowWindow(m_hwnd, SW_SHOW);
		UpdateWindow(m_hwnd);
	}

	void Core::InitGraphics()
	{
		m_graphics = new Graphics();
		m_graphics->Init();
	}

	int Core::Run()
	{
		MSG msg;

		//Initialise the msg structure
		ZeroMemory(&msg, sizeof(MSG));
		m_timer = new Timer();
		m_camera = new Camera(XMFLOAT3{ 0.0f,0.0f,-5.0f }, XMFLOAT3{ 0.0f,0.0f,0.0f }, XMFLOAT3{ 0.0f,1.0f,0.0f });
		//Shape Demo
		EngineSpace::GameObject boxObject = EngineSpace::PrimitiveGeometry::CreateBox();
		//Set Default render input layout and shaders
		m_graphics->BuildFX();
		m_graphics->CreateInputLayout();

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
				//m_timer->FPS();
				m_timer->Tick();
				this->UpdateFrame();
			}
		}
		
		return (int)msg.wParam;
	}

	void Core::UpdateFrame()
	{
		// Check for User Input
		if(m_input->GetKeyDown(VK_ESCAPE))
		{
			MessageBox(m_hwnd, L"Hello", L"Caption", MB_OK);
			exitAppCondition = true;
		}
		m_camera->Update();
		// Update all the draw calls
		m_graphics->Draw();
	}

	void Core::ShutDown()
	{
		// Remove Window Handler
		DestroyWindow(m_hwnd);

		// Remove the App instance
		UnregisterClass(L"NewBegining", m_hInstance);
		m_hInstance = NULL;

		//Release Pointer handler to the engine object
		gp_Core = NULL;
	}

	LRESULT CALLBACK Core::MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_KEYDOWN:
			m_input->SetKeyDown(wParam);
			break;
		case WM_KEYUP:
			m_input->SetKeyUp(wParam);
			break;
		default :
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
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
			return EngineSpace::gp_Core->MessageHandler(hwnd, msg, wParam, lParam);
		}
	}
}
