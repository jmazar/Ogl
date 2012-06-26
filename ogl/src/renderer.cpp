#include "renderer.h"

Renderer::Renderer() :
m_hDC(0),
m_hRC(0),
m_bInitialized(false) {
}

Renderer::Renderer(HWND hWnd) :
m_hDC(0),
m_hRC(0),
m_bInitialized(false) {
			Enable(hWnd);
}

Renderer::~Renderer() {
}

void Renderer::Enable(HWND hWnd) {
	if(true == m_bInitialized)
		return;

	PIXELFORMATDESCRIPTOR pfd;
	int format;
	
	// get the device context (DC)
	m_hDC = GetDC( hWnd );
	
	// set the pixel format for the DC
	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	format = ChoosePixelFormat( m_hDC, &pfd );
	SetPixelFormat( m_hDC, format, &pfd );
	
	// create and enable the render context (RC)
	m_hRC = wglCreateContext( m_hDC );
	wglMakeCurrent( m_hDC, m_hRC );
	glewInit();

	glEnable(GL_DEPTH_TEST);

	m_bInitialized = true;

}

void Renderer::Disable(HWND hWnd) {
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( m_hRC );
	ReleaseDC( hWnd, m_hDC );
}

void Renderer::Render() {
	SwapBuffers( m_hDC);
}