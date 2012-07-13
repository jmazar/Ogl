#ifndef _SCENE_GRAPH_H
#define _SCENE_GRAPH_H

#include "camera.h"
#include "scene_graph_node.h"

class SceneGraph {
public:
	SceneGraph();
	GLuint GetProgram();
	void SetProgram(GLuint const & in_program);
	Camera & GetCamera();
	void SetCamera(Camera const & in_camera);
	void AddSceneGraphNode(std::shared_ptr<ISGNode> in_node);
private:
	SceneGraph( SceneGraph const & );
	SceneGraph & const operator=( SceneGraph const & );
	std::shared_ptr<ISGNode> m_root;
	GLuint m_program;
	Camera m_camera;
};

#endif