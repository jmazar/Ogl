#ifndef _OBJECT_NODE_H
#define _OBJECT_NODE_H

#include "scene_graph_node.h"
#include "vertex_shader.h"
#include "fragment_shader.h"
#include "glm/gtc/matrix_transform.hpp"

class ObjectNode : public ISGNode {
public:
	virtual void Draw(float in_delta);
	void LoadObj(std::string in_meshLocation);
	void LoadShaders(std::string in_vertexShaderLocation,
									std::string in_fragmentShaderLocation);
private:
	GLuint m_program;
	FragmentShader m_fragmentShader;
	VertexShader m_vertexShader;
	std::vector<glm::vec4> m_vertices;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec2> m_texCoords;
	std::vector<GLushort> m_indices;
};

#endif