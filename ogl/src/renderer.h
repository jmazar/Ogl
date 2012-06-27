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
	void AddCamera(Camera const & in_camera);
	void AddSceneGraphNode(std::shared_ptr<ISGNode> in_node);
private:
	HDC m_hDC;
	HGLRC m_hRC;
	bool m_bInitialized;
	std::vector<Camera> m_cameras;
	unsigned int m_cameraToUse;
	glm::mat4 m_projectionMatrix;
	std::shared_ptr<ISGNode> m_sceneGraphNode;

};


#endif