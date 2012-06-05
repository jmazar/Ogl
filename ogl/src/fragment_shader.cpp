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

GLuint FragmentShader::CreateShader() {
	return glCreateShader(GL_FRAGMENT_SHADER);
}