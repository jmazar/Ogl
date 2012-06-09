#ifndef OBJ_LOADER
#define OBJ_LOADER

#include <string>
#include <vector>
#include <gl/glew.h>
#include "glm/glm.hpp"

void load_obj(
      std::string const & fileName, 
      std::vector<glm::vec4> & vertices, 
      std::vector<glm::vec3> & normals, 
      std::vector<GLushort> & indices); 

#endif