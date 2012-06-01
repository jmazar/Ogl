#ifndef FRAGMENT_SHADER_H
#define FRAGMENT_SHADER_H

#include "shader.h"

class FragmentShader : public Shader {
public:
  FragmentShader();
  FragmentShader(std::string const & fileName);
  ~FragmentShader();
	void CreateShaderFromFile(std::string const & fileName);
};


#endif