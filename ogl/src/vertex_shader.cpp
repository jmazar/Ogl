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

void VertexShader::CreateShaderFromFile(std::string const & fileName) {
  LoadShaderSource(fileName);
  m_shader = glCreateShader(GL_VERTEX_SHADER);
  CompileShader();
}