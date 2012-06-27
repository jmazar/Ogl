#include "renderer.h"

Renderer::Renderer() :
m_hDC(0),
m_hRC(0),
m_bInitialized(false),
m_cameraToUse(0) {
}

Renderer::Renderer(HWND hWnd) :
m_hDC(0),
m_hRC(0),
m_bInitialized(false),
m_cameraToUse(0) {
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

	m_projectionMatrix = glm::perspective(60.0f, 640.0f / 480.0f, 0.1f, 100.f);

	m_bInitialized = true;

}

void Renderer::AddSceneGraphNode(std::shared_ptr<ISGNode> in_node) {
	m_sceneGraphNode = in_node;
}

void Renderer::AddCamera(Camera const & in_camera) {
	m_cameras.push_back(in_camera);
}
void Renderer::Disable(HWND hWnd) {
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( m_hRC );
	ReleaseDC( hWnd, m_hDC );
}

void Renderer::Render() {
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	std::shared_ptr<MatrixStack> matrixStack = MatrixStack::Instance();
	matrixStack->Push(m_projectionMatrix);
	matrixStack->Push(m_cameras[m_cameraToUse].GetViewMatrix());

	m_sceneGraphNode->Draw(0.0f, m_cameras[m_cameraToUse]);

	matrixStack->Pop();
	matrixStack->Pop();

	SwapBuffers( m_hDC);
}