#ifndef OBJ_LOADER
#define OBJ_LOADER

#include <string>
#include <vector>
#include <gl/glew.h>
#include "Eigen\Dense"

void load_obj(
      std::string const & fileName, 
      std::vector<Eigen::Vector3f> & vertices, 
      std::vector<GLushort> & indices); 

#endif