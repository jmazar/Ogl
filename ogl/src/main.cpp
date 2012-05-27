#include <Windows.h>
#include <gl/gl.h>
#include <gl/GLU.h>
#include <stdio.h>

char const g_szClassName[] = "ogl";

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
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

void EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC * hRC)
{
	PIXELFORMATDESCRIPTOR pfd;
	int format;
	
	// get the device context (DC)
	*hDC = GetDC( hWnd );
	
	// set the pixel format for the DC
	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	format = ChoosePixelFormat( *hDC, &pfd );
	SetPixelFormat( *hDC, format, &pfd );
	
	// create and enable the render context (RC)
	*hRC = wglCreateContext( *hDC );
	wglMakeCurrent( *hDC, *hRC );
	
}

void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( hRC );
	ReleaseDC( hWnd, hDC );
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

	HDC hDC;
	HGLRC hRC;

	EnableOpenGL( hWnd, &hDC, &hRC);

	bool quit = false;
	float theta = 0.0f;
	
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
			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f);
			glClear( GL_COLOR_BUFFER_BIT );

			glPushMatrix();
			glRotatef( theta, 0.0f, 0.0f, 1.0f );
			glBegin( GL_TRIANGLES );
			glColor3f( 1.0f, 0.0f, 0.0f ); 
			glVertex2f( 0.0f, 1.0f );
			glColor3f( 0.0f, 1.0f, 0.0f ); 
			glVertex2f( 0.87f, -0.5f );
			glColor3f( 0.0f, 0.0f, 1.0f ); 
			glVertex2f( -0.87f, -0.5f );
			glEnd();
			glPopMatrix();

			SwapBuffers( hDC );

			//theta += 1.0f;
		}
	}

	DisableOpenGL( hWnd, hDC, hRC );

	DestroyWindow( hWnd );
	return msg.wParam;
}