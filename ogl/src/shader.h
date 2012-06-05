#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <gl/glew.h>

class Shader {
public:
	Shader();
	virtual ~Shader();

	void CreateShaderFromFile(std::string const & fileName);
	void AttachToProgram(GLuint program);
  void DetachFromProgram(GLuint program);
		
protected:
  void CompileShader();
  void LoadShaderSource(std::string const & fileName);

  std::string m_shaderSource;
  GLuint      m_shader;

private:
	virtual GLuint CreateShader() = 0;
	Shader(Shader const & shader);
	Shader & operator=(Shader const & rhs);

};


#endif