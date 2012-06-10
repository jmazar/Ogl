#include <Windows.h>
#include <gl/glew.h>
#include <stdio.h>
#include "vertex_shader.h"
#include "fragment_shader.h"
#include "obj_loader.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
	glewInit();


  //Loading an obj.
  std::vector<glm::vec4> vertices;
  std::vector<glm::vec3> normals;
  std::vector<GLushort> indices;

  load_obj("src\\models\\teapot2.mesh", vertices, normals, indices);

	//Init

	GLuint vao, vbo, ibo, nbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &nbo);
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
  glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);


  //Shader stuff

  GLuint program;
  FragmentShader fragmentShader;
  VertexShader vertexShader;

  vertexShader.CreateShaderFromFile("src\\shaders\\vertex.glsl");
  
  fragmentShader.CreateShaderFromFile("src\\shaders\\fragment.glsl");

  program = glCreateProgram();

  vertexShader.AttachToProgram(program);
  fragmentShader.AttachToProgram(program);

  glBindAttribLocation(program, 0, "in_vPosition");
  glBindAttribLocation(program, 1, "in_vNormal");

  
  glLinkProgram(program);
  
  glUseProgram(program);


	bool quit = false;
	float theta = 0.0f;

  glEnable(GL_DEPTH_TEST);

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

      //Setting uniforms
      glm::mat4 projectionMatrix = glm::perspective(60.0f, 640.0f / 480.0f, 0.1f, 100.f);
      glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -25.0f));
      glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), theta, glm::vec3(1.0f, 0.0f, 0.0f));
      glm::mat4 translateMatrix = glm::translate(rotateMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
      glm::mat4 modelMatrix = glm::scale(translateMatrix, glm::vec3(0.2f));
      glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
      glm::mat4 modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;

      glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
      glUniformMatrix4fv(glGetUniformLocation(program, "mvMatrix"), 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
      glUniformMatrix4fv(glGetUniformLocation(program, "mvpMatrix"), 1, GL_FALSE, glm::value_ptr(modelViewProjectionMatrix));


      glm::vec3 vEyeLight(-100.0f, 100.0f, 100.0f);
      glm::vec4 vDiffuseColor(0.0f, 0.0f, 1.0f, 1.0f);
      glUniform3fv(glGetUniformLocation(program, "vLightPosition"), 1, glm::value_ptr(vEyeLight));
      glUniform4fv(glGetUniformLocation(program, "diffuseColor"), 1, glm::value_ptr(vDiffuseColor));

      glDrawRangeElements(GL_TRIANGLES, 0, indices.size() - 1, indices.size(), GL_UNSIGNED_SHORT, 0);

			SwapBuffers( hDC );
      
      theta += 0.01;
		}
	}

	DisableOpenGL( hWnd, hDC, hRC );

	DestroyWindow( hWnd );
	return msg.wParam;
}