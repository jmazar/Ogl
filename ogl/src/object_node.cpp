#include "object_node.h"
#include "obj_loader.h"
#include "glm/gtc/swizzle.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "camera.h"
#define _USE_MATH_DEFINES
#include <math.h>

GLuint LoadTexture( const char * filename, int width, int height )
{
		GLuint texture;
		unsigned char * data;
		FILE * file;
		
		//The following code will read in our RAW file
		file = fopen( filename, "rb" );
		if ( file == NULL ) return 0;
		data = (unsigned char *)malloc( width * height * 3 );
		fread( data, width * height * 3, 1, file );
		fclose( file );
		
		glGenTextures( 1, &texture ); //generate the texture with the loaded data
		glBindTexture( GL_TEXTURE_2D, texture ); //bind the texture to it’s array

		//set texture environment parameters
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
		
		//And if you go and use extensions, you can use Anisotropic filtering textures which are of an
		//even better quality, but this will do for now.
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		//Here we are setting the parameter to repeat the texture instead of clamping the texture
		//to the edge of our shape. 
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		
		//Generate the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		free( data ); //free the texture
		
		return texture; //return whether it was successfull
}

void ObjectNode::Draw(float in_delta) {
	glUseProgram(m_program);

	glUniform1i(glGetUniformLocation(m_program, "Texture"), 0);

	Camera camera;
	glm::vec3 eyeLocation(0.0f, 0.0f, 45.0f);
	camera.SetCameraTranslation(eyeLocation);

	//Setting uniforms
	glm::mat4 projectionMatrix = glm::perspective(60.0f, 640.0f / 480.0f, 0.1f, 100.f);
	glm::mat4 viewMatrix = camera.GetViewMatrix();
	glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), in_delta, glm::vec3(1.0f, 1.0f, 0.0f));
	glm::mat4 translateMatrix = glm::translate(rotateMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 modelMatrix = glm::scale(translateMatrix, glm::vec3(0.2f));
	glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
	glm::mat4 modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;

	glUniform4fv(glGetUniformLocation(m_program, "vEyeLocation"), 1, glm::value_ptr(camera.GetEyePosVec()));
	glUniformMatrix4fv(glGetUniformLocation(m_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(m_program, "mvMatrix"), 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(m_program, "mvpMatrix"), 1, GL_FALSE, glm::value_ptr(modelViewProjectionMatrix));


	glm::vec3 vEyeLight(0.0f, 100.0f, 0.0f);
	glm::vec4 vDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	glUniform3fv(glGetUniformLocation(m_program, "vLightPosition"), 1, glm::value_ptr(vEyeLight));
	glUniform4fv(glGetUniformLocation(m_program, "diffuseColor"), 1, glm::value_ptr(vDiffuseColor));

	glDrawRangeElements(GL_TRIANGLES, 0, m_indices.size() - 1, m_indices.size(), GL_UNSIGNED_SHORT, 0);

}

void ObjectNode::LoadObj(std::string in_meshLocation) {
	load_obj(in_meshLocation, m_vertices, m_normals, m_indices);

	glm::vec3 normalizedVert;
	float theta, phi;
	for(auto iterator = m_vertices.begin(); iterator != m_vertices.end(); iterator++) {
		normalizedVert = glm::swizzle<glm::X, glm::Y, glm::Z>(*iterator);
		normalizedVert = glm::normalize(normalizedVert);

		theta = acosf(normalizedVert.y);
		phi = atan2f(normalizedVert.x, normalizedVert.z);

		glm::vec2 uvs;
		uvs.x = phi / M_PI_2;
		uvs.y = theta / (2.0f * M_PI);
		uvs.x = (uvs.x > 0.5)?(1.F-uvs.x):(uvs.x);
		uvs.y = (uvs.y > 0.5)?(1.F-uvs.y):(uvs.y);
		uvs.y *= 2.0f;
		m_texCoords.push_back(uvs);
	}

	GLuint vao, vbo, ibo, nbo, tbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec4), m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &nbo);
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3), m_normals.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, m_texCoords.size() * sizeof(glm::vec2), m_texCoords.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);


	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLushort), m_indices.data(), GL_STATIC_DRAW);

	GLuint texture = LoadTexture("src\\textures\\kickbutt.raw", 256, 256);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void ObjectNode::LoadShaders(
std::string in_vertexShaderLocation, 
std::string in_fragmentShaderLocation) {
	m_vertexShader.CreateShaderFromFile(in_vertexShaderLocation);
	m_fragmentShader.CreateShaderFromFile(in_fragmentShaderLocation);

	m_program = glCreateProgram();

	m_vertexShader.AttachToProgram(m_program);
	m_fragmentShader.AttachToProgram(m_program);

	glBindAttribLocation(m_program, 0, "in_vPosition");
	glBindAttribLocation(m_program, 1, "in_vNormal");
	glBindAttribLocation(m_program, 2, "in_vTexCoord");

	glLinkProgram(m_program);
}

