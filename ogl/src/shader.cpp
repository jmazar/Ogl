#include "shader.h"
#include <fstream>
#include <iostream>

Shader::Shader() :
  m_shader(0) {
}

Shader::~Shader() {
  glDeleteShader(m_shader);
}

void Shader::CreateShaderFromFile(std::string const & fileName) {
  LoadShaderSource(fileName);
  m_shader = CreateShader();
  CompileShader();
}

void Shader::LoadShaderSource(std::string const & fileName) {
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

void Shader::CompileShader() {
  char const * source = m_shaderSource.c_str();

  glShaderSource(m_shader, 1, (const GLchar**)&source, 0);

  glCompileShader(m_shader);

  GLint isCompiled;

  glGetShaderiv(m_shader, GL_COMPILE_STATUS, &isCompiled);
  if(0 == isCompiled) {
    printf("Failed to compile shader!\n");
    GLint blen = 0;	
    GLsizei slen = 0;

    glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH , &blen);       
    if (blen > 1)
    {
     GLchar* compiler_log = (GLchar*)malloc(blen);
     glGetInfoLogARB(m_shader, blen, &slen, compiler_log);
     std::cerr << "compiler_log:\n" << compiler_log;
     free (compiler_log);
    }
  }
}

void Shader::AttachToProgram(GLuint program) {
  glAttachShader(program, m_shader);
}

void Shader::DetachFromProgram(GLuint program) {
  glDetachShader(program, m_shader);
}