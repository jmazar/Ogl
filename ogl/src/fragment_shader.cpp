#include "fragment_shader.h"

FragmentShader::FragmentShader() :
  Shader() {
}

FragmentShader::FragmentShader(std::string const & fileName) :
  Shader() {
    CreateShaderFromFile(fileName);
}

FragmentShader::~FragmentShader() {
}

void FragmentShader::CreateShaderFromFile(std::string const & fileName) {
  LoadShaderSource(fileName);
  m_shader = glCreateShader(GL_FRAGMENT_SHADER);
  CompileShader();
}