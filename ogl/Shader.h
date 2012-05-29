#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader {
public:
	Shader();
	Shader(std::string const & fileName);
	virtual ~Shader();

	void LoadShaderFromFile(std::string const & fileName);
	void CompileShader(GLuint shaderType);
	void AttachToProgram(GLuint program);
	void BindAttributeLocation(GLuint program, GLuint index, std::string const & location);
		
private:
	Shader(Shader const & shader);
	Shade & operator=(Shader const & rhs);


};

#endif