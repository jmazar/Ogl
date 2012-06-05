#include "vertex_shader.h"

VertexShader::VertexShader() :
  Shader() {
}

VertexShader::VertexShader(std::string const & fileName) :
  Shader() {
    CreateShaderFromFile(fileName);
}

VertexShader::~VertexShader() {
}

GLuint VertexShader::CreateShader() {
  return glCreateShader(GL_VERTEX_SHADER);
}