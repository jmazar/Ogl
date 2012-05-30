#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <gl/glew.h>

class Shader {
public:
	Shader();
	Shader(std::string const & fileName);
	virtual ~Shader();

	void LoadShaderFromFile(std::string const & fileName);
	void CompileShader(GLuint shaderType);
	void AttachToProgram(GLuint program);
		
private:
	Shader(Shader const & shader);
	Shader & operator=(Shader const & rhs);

  std::string m_shaderSource;
  GLuint      m_shader;
  GLuint      m_program;
};

#endif