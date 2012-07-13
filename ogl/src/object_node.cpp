#include "object_node.h"
#include "obj_loader.h"
#include "glm/gtc/swizzle.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "camera.h"
#define _USE_MATH_DEFINES
#include <math.h>

void ObjectNode::Draw(float in_delta, Camera const & in_camera) {
	glUseProgram(m_program);

	//Setting uniforms
	glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), in_delta, glm::vec3(1.0f, 1.0f, 0.0f));
	glm::mat4 translateMatrix = glm::translate(rotateMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 modelMatrix = glm::scale(translateMatrix, glm::vec3(1.0f));

	MatrixStack::Instance()->Push(modelMatrix);

	glm::mat4 modelViewProjectionMatrix = glm::mat4(1.0f);

	std::vector<glm::mat4> const stack = MatrixStack::Instance()->GetStack();
	for(int i = 0; i < stack.size(); i ++) {
		modelViewProjectionMatrix = modelViewProjectionMatrix * stack[i];
	}

	glUniform4fv(glGetUniformLocation(m_program, "vEyeLocation"), 1, glm::value_ptr(in_camera.GetEyePosVec()));
	glUniformMatrix4fv(glGetUniformLocation(m_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(m_program, "mvpMatrix"), 1, GL_FALSE, glm::value_ptr(modelViewProjectionMatrix));


	glm::vec3 vEyeLight(0.0f, 100.0f, 0.0f);
	glm::vec4 vDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	glUniform3fv(glGetUniformLocation(m_program, "vLightPosition"), 1, glm::value_ptr(vEyeLight));
	glUniform4fv(glGetUniformLocation(m_program, "diffuseColor"), 1, glm::value_ptr(vDiffuseColor));

	glDrawRangeElements(GL_TRIANGLES, 0, m_indices.size() - 1, m_indices.size(), GL_UNSIGNED_SHORT, 0);

	MatrixStack::Instance()->Pop();
}

void ObjectNode::LoadObj(std::string in_meshLocation) {
	load_obj(in_meshLocation, m_vertices, m_normals, m_indices);

	GLuint vao, vbo, ibo, nbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec4), m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &nbo);
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3), m_normals.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLushort), m_indices.data(), GL_STATIC_DRAW);

}

void ObjectNode::LoadShaders(
std::string in_vertexShaderLocation, 
std::string in_fragmentShaderLocation) {
}

