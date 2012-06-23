#include <Windows.h>
#include <gl/glew.h>
#include <stdio.h>
#include "vertex_shader.h"
#include "fragment_shader.h"
#include "obj_loader.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/swizzle.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

#include "camera.h"
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

GLuint LoadTexture( const char * filename, int width, int height )
{
		GLuint texture;
		unsigned char * data;
		FILE * file;
		
		//The following code will read in our RAW file
		file = fopen( filename, "rb" );
		if ( file == NULL ) return 0;
		data = (unsigned char *)malloc( width * height * 3 );
		fread( data, width * height * 3, 1, file );
		fclose( file );
		
		glGenTextures( 1, &texture ); //generate the texture with the loaded data
		glBindTexture( GL_TEXTURE_2D, texture ); //bind the texture to it’s array

		//set texture environment parameters
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
		
		//And if you go and use extensions, you can use Anisotropic filtering textures which are of an
		//even better quality, but this will do for now.
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		//Here we are setting the parameter to repeat the texture instead of clamping the texture
		//to the edge of our shape. 
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		
		//Generate the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		free( data ); //free the texture
		
		return texture; //return whether it was successfull
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
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<GLushort> indices;

	load_obj("src\\models\\teapot2.mesh", vertices, normals, indices);

	glm::vec3 normalizedVert;
	float theta, phi;
	for(auto iterator = vertices.begin(); iterator != vertices.end(); iterator++) {
		normalizedVert = glm::swizzle<glm::X, glm::Y, glm::Z>(*iterator);
		normalizedVert = glm::normalize(normalizedVert);

		theta = acosf(normalizedVert.y);
		phi = atan2f(normalizedVert.x, normalizedVert.z);

		glm::vec2 uvs;
		uvs.x = phi / M_PI_2;
		uvs.y = theta / (2.0f * M_PI);
		uvs.x = (uvs.x > 0.5)?(1.F-uvs.x):(uvs.x);
		uvs.y = (uvs.y > 0.5)?(1.F-uvs.y):(uvs.y);
		uvs.y *= 2.0f;
		texCoords.push_back(uvs);
	}

	//Init


	GLuint vao, vbo, ibo, nbo, tbo;

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

	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), texCoords.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);


	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);


	GLuint texture = LoadTexture("src\\textures\\kickbutt.raw", 256, 256);


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
	glBindAttribLocation(program, 2, "in_vTexCoord");

	
	glLinkProgram(program);
	
	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	bool quit = false;
	theta = 0.0f;

	glEnable(GL_DEPTH_TEST);


	Camera camera;

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

			glUniform1i(glGetUniformLocation(program, "Texture"), 0);

			glm::vec3 eyeLocation(camera_x, camera_y, camera_z);
			camera.SetCameraTranslation(eyeLocation);

			//Setting uniforms
			glm::mat4 projectionMatrix = glm::perspective(60.0f, 640.0f / 480.0f, 0.1f, 100.f);
			glm::mat4 viewMatrix = camera.GetViewMatrix();
			glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), theta, glm::vec3(1.0f, 1.0f, 0.0f));
			glm::mat4 translateMatrix = glm::translate(rotateMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
			glm::mat4 modelMatrix = glm::scale(translateMatrix, glm::vec3(0.2f));
			glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
			glm::mat4 modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;

			glUniform4fv(glGetUniformLocation(program, "vEyeLocation"), 1, glm::value_ptr(camera.GetEyePosVec()));
			glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
			glUniformMatrix4fv(glGetUniformLocation(program, "mvMatrix"), 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
			glUniformMatrix4fv(glGetUniformLocation(program, "mvpMatrix"), 1, GL_FALSE, glm::value_ptr(modelViewProjectionMatrix));


			glm::vec3 vEyeLight(0.0f, 100.0f, 0.0f);
			glm::vec4 vDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
			glUniform3fv(glGetUniformLocation(program, "vLightPosition"), 1, glm::value_ptr(vEyeLight));
			glUniform4fv(glGetUniformLocation(program, "diffuseColor"), 1, glm::value_ptr(vDiffuseColor));

			glDrawRangeElements(GL_TRIANGLES, 0, indices.size() - 1, indices.size(), GL_UNSIGNED_SHORT, 0);

			renderer.Render();
			
			theta += 0.01;
		}
	}

	renderer.Disable(hWnd);

	DestroyWindow( hWnd );
	return msg.wParam;
}