#ifndef OBJ_LOADER
#define OBJ_LOADER

#include <string>
#include <vector>
#include <gl/glew.h>
#include "vmath\vmath.h"

void load_obj(
      std::string const & fileName, 
      std::vector<Vector3f> & verticies, 
      std::vector<GLushort> & faces); 

#endif