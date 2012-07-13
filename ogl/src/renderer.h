#ifndef _RENDERER_H
#define _RENDERER_H
#include <Windows.h>
#include <gl/glew.h>
#include "camera.h"
#include "matrix_stack.h"
#include "scene_graph_node.h"

class Renderer {
public:
	Renderer();
	Renderer(HWND hWnd);
	virtual ~Renderer();
	void Enable(HWND hWnd);
	void Disable(HWND hWnd);
	void Render();
private:
	HDC m_hDC;
	HGLRC m_hRC;
	bool m_bInitialized;
	Camera m_camera;
	std::shared_ptr<ISGNode> m_sceneGraphNode;

};


#endif