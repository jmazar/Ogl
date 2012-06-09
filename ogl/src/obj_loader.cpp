#include "obj_loader.h"

#include <fstream>
#include <iostream>
#include <sstream>


void load_obj(
    std::string const & fileName, 
    std::vector<glm::vec4> & vertices, 
    std::vector<glm::vec3> & normals, 
    std::vector<GLushort> & indices) {
  
  std::ifstream in(fileName, std::ios::in);
  if (!in) { std::cerr << "Cannot open " << fileName << std::endl; exit(1); }
 
  std::string line;
  while (getline(in, line)) {
    if (line.substr(0,2) == "v ") {
      std::istringstream s(line.substr(2));
      glm::vec4 v; 
      s >> v.x;
      s >> v.y;
      s >> v.z;
      v.w = 1.0f;
      vertices.push_back(v);
    }  else if (line.substr(0,2) == "f ") {
      std::istringstream s(line.substr(2));
      GLushort a,b,c;
      s >> a; 
      s >> b; 
      s >> c;
      a--; 
      b--; 
      c--;
      indices.push_back(a); 
      indices.push_back(b); 
      indices.push_back(c);
    } else if(line.substr(0, 3) == "vn ") {
      std::istringstream s(line.substr(3));
      glm::vec3 v; 
      s >> v.x;
      s >> v.y;
      s >> v.z;
      normals.push_back(v);
    }
  }
}