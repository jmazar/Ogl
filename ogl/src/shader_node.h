#ifndef _SHADER_NODE_H
#define _SHADER_NODE_H

#include "scene_graph_node.h"

class FragmentShader;
class VertexShader;

class ShaderNode : public ISGNode {
public:
	ShaderNode();
	~ShaderNode();
	virtual void Draw(SceneGraph const & in_sceneGraph);
	void LoadShaders(std::string in_vertexShaderLocation,
									std::string in_fragmentShaderLocation);
private:
	ShaderNode( ShaderNode const & );
	ShaderNode const & operator=( ShaderNode const & );
	FragmentShader m_fragmentShader;
	VertexShader m_vertexShader;
	GLuint m_program;
};

#endif