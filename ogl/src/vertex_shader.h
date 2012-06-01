#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H

#include "shader.h"

class VertexShader : public Shader {
public:
  VertexShader();
  VertexShader(std::string const & fileName);
  ~VertexShader();
	void CreateShaderFromFile(std::string const & fileName);
};

#endif