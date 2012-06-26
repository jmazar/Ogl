#include <Windows.h>
#include <gl/glew.h>
#include <stdio.h>
#include "object_node.h"

#include "renderer.h"

char const g_szClassName[] = "ogl";

float camera_x = 0.0f;
float camera_y = 0.0f;
float camera_z = 45.0f;

void HandleKeys(HWND in_hWnd, WPARAM in_wParam) {
	switch(in_wParam)
	{
	case 'B':
		MessageBox(in_hWnd, "Butts", "b", MB_OK);
		break;
	case 'J':
		camera_z++;
		break;
	case 'K':
		camera_z--;
		break;
	case VK_LEFT:
		camera_x--;
		break;
	case VK_RIGHT:
		camera_x++;
		break;
	case VK_UP:
		camera_y++;
		break;
	case VK_DOWN:
		camera_y--;
		break;

	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
		switch(msg)
		{
		case WM_KEYDOWN:
			HandleKeys(hwnd, wParam);
			break;
		case WM_CLOSE:
				PostQuitMessage(0);
		break;
		case WM_DESTROY:
				PostQuitMessage(0);
		break;
		default:
				return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		return 0;
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow) {
	WNDCLASSEX windowsClass;
	HWND hWnd;
	MSG msg;

	//Registering the windows class
	windowsClass.cbSize        = sizeof(WNDCLASSEX);
	windowsClass.style         = 0;
	windowsClass.lpfnWndProc   = WndProc;
	windowsClass.cbClsExtra    = 0;
	windowsClass.cbWndExtra    = 0;
	windowsClass.hInstance     = hInstance;
	windowsClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	windowsClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	windowsClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	windowsClass.lpszMenuName  = NULL;
	windowsClass.lpszClassName = g_szClassName;
	windowsClass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);


	if(!RegisterClassEx(&windowsClass)) {
		MessageBox(NULL, "Window registration failed.", "Window Error",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"ogl",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
		NULL, NULL, hInstance, NULL);

	if(NULL == hWnd) {
		MessageBox(NULL, "Window creation failed!", "Window Error",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	Renderer renderer;
	renderer.Enable(hWnd);


	//Loading an obj.


	//Init






	bool quit = false;
	float theta = 0.0f;


	ObjectNode object;
	object.LoadObj("src\\models\\teapot2.mesh");
	object.LoadShaders("src\\shaders\\vertex.glsl", "src\\shaders\\fragment.glsl");


	while( !quit ) {
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) {
			if( WM_QUIT == msg.message ) {
				quit = true;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			glClearColor( 1.0f, 1.0f, 1.0f, 1.0f);
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			object.Draw(theta);

			renderer.Render();
			
			theta += 0.01;
		}
	}

	renderer.Disable(hWnd);

	DestroyWindow( hWnd );
	return msg.wParam;
}