#include "shader.h"
#include <fstream>

Shader::Shader() :
  m_shader(0) {
}

Shader::Shader(std::string const & fileName) :
  m_shader(0) {
    LoadShaderFromFile(fileName);
}

Shader::~Shader() {
  glDetachShader(m_program, m_shader);
  glDeleteShader(m_shader);
}

void Shader::LoadShaderFromFile(std::string const & fileName) {
  std::ifstream file;
  file.open(fileName);
  if(!file.good()) {
    printf("Error opening file!\n");
    return;
  }

  m_shaderSource.assign((std::istreambuf_iterator<char>(file)), 
    std::istreambuf_iterator<char>());

  file.close();
}

void Shader::CompileShader(GLenum shaderType) {
  m_shader = glCreateShader(shaderType);

  char const * source = m_shaderSource.c_str();

  glShaderSource(m_shader, 1, (const GLchar**)&source, 0);

  glCompileShader(m_shader);

  GLint isCompiled;

  glGetShaderiv(m_shader, GL_COMPILE_STATUS, &isCompiled);
  if(0 == isCompiled) {
    printf("Failed to compile shader!\n");
  }
}

void Shader::AttachToProgram(GLuint program) {
  m_program = program;
  glAttachShader(program, m_shader);
}