#include "shader_node.h"
#include "fragment_shader.h"
#include "vertex_shader.h"
#include "scene_graph.h"

ShaderNode::ShaderNode() {
}

ShaderNode::~ShaderNode() {
}

void ShaderNode::Draw(SceneGraph const & in_sceneGraph) {
	in_sceneGraph.SetProgram(m_program);
}

void ShaderNode::LoadShaders(std::string in_vertexShaderLocation,
									std::string in_fragmentShaderLocation) {
	m_vertexShader.CreateShaderFromFile(in_vertexShaderLocation);
	m_fragmentShader.CreateShaderFromFile(in_fragmentShaderLocation);

	m_program = glCreateProgram();

	m_vertexShader.AttachToProgram(m_program);
	m_fragmentShader.AttachToProgram(m_program);

	glBindAttribLocation(m_program, 0, "in_vPosition");
	glBindAttribLocation(m_program, 1, "in_vNormal");
	glBindAttribLocation(m_program, 2, "in_vTexCoord");

	glLinkProgram(m_program);
}
